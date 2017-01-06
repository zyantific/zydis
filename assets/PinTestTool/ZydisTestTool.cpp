/**
 *
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "pin.H"
#include "xed-interface.h"

#include <iostream>
#include <iomanip>
#include <fstream>
#include <set>
#include <Zydis/Zydis.h> 

/* ========================================================================== */
/* TLS struct                                                                 */
/* ========================================================================== */

struct ThreadData
{
    CONTEXT ctx;
    ZydisInstructionDecoder decoder;

    ThreadData()
    {
        ZydisDecoderInitInstructionDecoderEx(
            &decoder, ZYDIS_DISASSEMBLER_MODE_64BIT, NULL, 0
        ); 
    }
};

/* ========================================================================== */
/* Global variables                                                           */
/* ========================================================================== */

TLS_KEY tls_key;
std::ostream* out = &cerr;

PIN_LOCK unique_iforms_lock;
std::set<xed_iform_enum_t> unique_iforms;

/* ========================================================================== */
/* Tables                                                                     */
/* ========================================================================== */

struct RegMapping
{
    REG           pin;
    ZydisRegister zy;
};

RegMapping reg_mapping[] = {
    // 64-bit GP register
    {REG_RAX, ZYDIS_REGISTER_RAX},
    {REG_RBX, ZYDIS_REGISTER_RBX},
    {REG_RCX, ZYDIS_REGISTER_RCX},
    {REG_RDX, ZYDIS_REGISTER_RDX},
    {REG_RSP, ZYDIS_REGISTER_RSP},
    {REG_RBP, ZYDIS_REGISTER_RBP},
    {REG_RSI, ZYDIS_REGISTER_RSI},
    {REG_RDI, ZYDIS_REGISTER_RDI},
    {REG_R8,  ZYDIS_REGISTER_R8 },
    {REG_R9,  ZYDIS_REGISTER_R9 },
    {REG_R10, ZYDIS_REGISTER_R10},
    {REG_R11, ZYDIS_REGISTER_R11},
    {REG_R12, ZYDIS_REGISTER_R12},
    {REG_R13, ZYDIS_REGISTER_R13},
    {REG_R14, ZYDIS_REGISTER_R14},
    {REG_R15, ZYDIS_REGISTER_R15},

    // Segment registers
    {REG_SEG_ES, ZYDIS_REGISTER_ES},
    {REG_SEG_SS, ZYDIS_REGISTER_SS},
    {REG_SEG_SS, ZYDIS_REGISTER_SS},
    {REG_SEG_CS, ZYDIS_REGISTER_CS},
    {REG_SEG_DS, ZYDIS_REGISTER_DS},
    {REG_SEG_FS, ZYDIS_REGISTER_FS},
    {REG_SEG_GS, ZYDIS_REGISTER_GS},
    
    // Mask registers
    {REG_K0, ZYDIS_REGISTER_K0},
    {REG_K1, ZYDIS_REGISTER_K1},
    {REG_K2, ZYDIS_REGISTER_K2},
    {REG_K3, ZYDIS_REGISTER_K3},
    {REG_K4, ZYDIS_REGISTER_K4},
    {REG_K5, ZYDIS_REGISTER_K5},
    {REG_K6, ZYDIS_REGISTER_K6},
    {REG_K7, ZYDIS_REGISTER_K7},

    // TODO: XMM, YMM, ZMM, ST, TR

    // Special registers
    {REG_MXCSR, ZYDIS_REGISTER_MXCSR},
};

/* ========================================================================== */
/* Command line switches                                                      */
/* ========================================================================== */

KNOB<string> knob_out_file(
    KNOB_MODE_WRITEONCE, "pintool", "o", "", "Output file name"
);

KNOB<bool> know_unique_iform(
    KNOB_MODE_WRITEONCE, "pintool", "unique_iform", "0", 
    "Only instrument one instruction per iform"
);

KNOB<bool> omit_op_checks(
    KNOB_MODE_WRITEONCE, "pintool", "omit_op_checks", "0",
    "Skip verification of operand write assumptions"
);

KNOB<bool> omit_flag_checks(
    KNOB_MODE_WRITEONCE, "pintool", "omit_flag_checks", "1",
    "Skip verification of flag write assumptions"
);

/* ========================================================================== */
/* Instrumentation callbacks                                                  */
/* ========================================================================== */

VOID PIN_FAST_ANALYSIS_CALL pre_ins_cb(THREADID tid, const CONTEXT* ctx) 
{
    ThreadData *tls = static_cast<ThreadData*>(PIN_GetThreadData(tls_key, tid));
    PIN_SaveContext(ctx, &tls->ctx);
}

VOID PIN_FAST_ANALYSIS_CALL post_ins_cb(THREADID tid, const CONTEXT* post_ctx) 
{
    ThreadData *tls = static_cast<ThreadData*>(PIN_GetThreadData(tls_key, tid));

    // Get IPs.
    ADDRINT pre_ip = PIN_GetContextReg(&tls->ctx, REG_INST_PTR);
    ADDRINT post_ip = PIN_GetContextReg(post_ctx, REG_INST_PTR);
    
    // If the IP didn't change, we're probably dealing with a rep.
    // Skip instruction until last execution where fallthrough kicks in.
    ADDRINT ip_diff = post_ip - pre_ip;
    if (!ip_diff) return;

    // Disassemble previously executed instruction.
    ZydisMemoryInput input;
    ZydisInputInitMemoryInput(&input, (void*)pre_ip, 15);
    ZydisDecoderSetInput(&tls->decoder, (ZydisCustomInput*)&input);

    ZydisInstructionInfo insn_info;
    ZydisStatus decode_status = ZydisDecoderDecodeNextInstruction(
        &tls->decoder, &insn_info
    );

    // Can we decode it?
    if (!ZYDIS_SUCCESS(decode_status)) {
        *out << "Decoding failure" << endl;
        goto error;
    }

    // Does the length look like what we expected?
    if (insn_info.length != ip_diff) {
        *out << "Instruction length mismatch (expected "
             << dec << ip_diff << ", got " << (int)insn_info.length 
             << ')' << endl;
        goto error;
    }

    // Analyze operand effects.
    if (!omit_op_checks) {
        for (const RegMapping* map = reg_mapping
            ; map < reg_mapping + sizeof reg_mapping / sizeof reg_mapping[0]
            ; ++map) {

            ADDRINT pre_reg_val = PIN_GetContextReg(&tls->ctx, map->pin);
            ADDRINT post_reg_val = PIN_GetContextReg(post_ctx, map->pin);

            // Did the instruction touch this register?
            if (pre_reg_val != post_reg_val) {
                *out << "Reg value changed (" 
                     << ZydisRegisterGetString(map->zy) 
                     << ")!" << endl;
            }
        }
    }

    // Analyze flag effects.
    if (!omit_flag_checks) {
        ADDRINT prev_flags = PIN_GetContextReg(&tls->ctx, REG_GFLAGS);
        ADDRINT new_flags = PIN_GetContextReg(post_ctx, REG_GFLAGS);
        ADDRINT changed_flags = prev_flags ^ new_flags;
        if (changed_flags) {
            // TODO: implement once flag infos are available.
        }
    }

    return;

error:
    // Always print raw bytes on error.
    *out << "Raw bytes: ";
    for (size_t i = 0; i < 15; ++i) {
        *out << setfill('0') << setw(2) << hex 
             << (int)((uint8_t*)pre_ip)[i] << ' ';
    }
    *out << endl;
}

VOID instruction(INS ins, VOID *v)
{
    if (!INS_HasFallThrough(ins)) return;

    xed_decoded_inst_t* xed = INS_XedDec(ins);
    xed_iform_enum_t iform = xed_decoded_inst_get_iform_enum(xed);

    if (know_unique_iform.Value()) {
        PIN_GetLock(&unique_iforms_lock, 0);
        if (unique_iforms.find(iform) != unique_iforms.end()) {
            PIN_ReleaseLock(&unique_iforms_lock);
            return;
        }
        unique_iforms.insert(iform);
        *out << iform << endl;
        PIN_ReleaseLock(&unique_iforms_lock);
    }
    
    INS_InsertCall(
        ins, IPOINT_BEFORE, (AFUNPTR)&pre_ins_cb, 
        IARG_FAST_ANALYSIS_CALL, IARG_THREAD_ID, IARG_CONST_CONTEXT,
        IARG_END
    );
    INS_InsertCall(
        ins, IPOINT_AFTER, (AFUNPTR)&post_ins_cb, 
        IARG_FAST_ANALYSIS_CALL, IARG_THREAD_ID, IARG_CONST_CONTEXT, 
        IARG_END
    );
}

VOID thread_start(THREADID tid, CONTEXT *ctx, INT32 flags, VOID* v)
{
    ThreadData* tls = new ThreadData;
    PIN_SetThreadData(tls_key, tls, tid);
}

int main(int argc, char *argv[])
{
    if (PIN_Init(argc, argv)) {
        cerr << KNOB_BASE::StringKnobSummary() << endl;
        return 1;
    }
    
    // Open output file.
    string file_name = knob_out_file.Value();
    if (!file_name.empty()) {
        out = new std::ofstream(file_name.c_str());
    }

    // Init TLS.
    tls_key = PIN_CreateThreadDataKey(0);
    PIN_InitLock(&unique_iforms_lock);

    // Register hooks.
    PIN_AddThreadStartFunction(&thread_start, NULL);
    INS_AddInstrumentFunction(&instruction, NULL);

    // Start the program, never returns.
    PIN_StartProgram();
    
    return 0;
}

/* ========================================================================== */
