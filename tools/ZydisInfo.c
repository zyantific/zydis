/***************************************************************************************************

  Zyan Disassembler Library (Zydis)

  Original Author : Florian Bernd

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

***************************************************************************************************/

/**
 * @file
 * @brief   TODO
 */

#include <stdio.h>
#include <inttypes.h>
#include <string.h>
#include <Zydis/Zydis.h>

/* ============================================================================================== */
/* Helper functions                                                                               */
/* ============================================================================================== */

const char* ZydisFormatStatus(ZydisStatus status)
{
    static const char* strings[] =
    {
        "SUCCESS",
        "INVALID_PARAMETER",
        "INVALID_OPERATION",
        "NO_MORE_DATA",
        "DECODING_ERROR",
        "INSTRUCTION_TOO_LONG",
        "BAD_REGISTER",
        "ILLEGAL_LOCK",
        "ILLEGAL_LEGACY_PFX",
        "ILLEGAL_REX",
        "INVALID_MAP",
        "MALFORMED_EVEX",
        "MALFORMED_MVEX",
        "INVALID_MASK",
        "IMPOSSIBLE_INSTRUCTION",
        "INSUFFICIENT_BUFFER_SIZE"
    };
    ZYDIS_ASSERT(status < ZYDIS_ARRAY_SIZE(strings));
    return strings[status];
}

/* ============================================================================================== */
/* Print functions                                                                                */
/* ============================================================================================== */

void printFlags(ZydisDecodedInstruction* instruction)
{
    static const char* flagNames[] =
    {
        "CF",
        "PF",
        "AF",
        "ZF",
        "SF",
        "TF",
        "IF",
        "DF",
        "OF",
        "IOPL",
        "NT",
        "RF",
        "VM",
        "AC",
        "VIF",
        "VIP",
        "ID",
        "C0",
        "C1",
        "C2",
        "C3"
    };
    static const char* flagActions[] =
    {
        " ",
        "T",
        "M",
        "0",
        "1",
        "U"
    };

    printf("FLAGS:\n    ACTIONS: ");
    uint8_t c = 0;
    for (ZydisCPUFlag i = 0; i < ZYDIS_ARRAY_SIZE(instruction->flags); ++i)
    {
        if (instruction->flags[i].action != ZYDIS_CPUFLAG_ACTION_NONE)
        {
            ++c;
            printf("[%-4s: %s] ", flagNames[i], flagActions[instruction->flags[i].action]);
        }
        if (c == 8)
        {
            printf("\n             ");
        }
    }
    puts(c ? "" : "none");

    ZydisCPUFlagMask flags, temp;
    ZydisGetCPUFlagsByAction(instruction, ZYDIS_CPUFLAG_ACTION_TESTED, &flags);
    printf("       READ: 0x%08"PRIX32"\n", flags);
    ZydisGetCPUFlagsByAction(instruction, ZYDIS_CPUFLAG_ACTION_MODIFIED, &flags);
    ZydisGetCPUFlagsByAction(instruction, ZYDIS_CPUFLAG_ACTION_SET_0, &temp);
    flags |= temp;
    ZydisGetCPUFlagsByAction(instruction, ZYDIS_CPUFLAG_ACTION_SET_1, &temp);
    flags |= temp;
    printf("    WRITTEN: 0x%08"PRIX32"\n", flags);
    ZydisGetCPUFlagsByAction(instruction, ZYDIS_CPUFLAG_ACTION_UNDEFINED, &flags);
    printf("  UNDEFINED: 0x%08"PRIX32"\n", flags);

    puts("");
}

void printOperands(ZydisDecodedInstruction* instruction)
{
    puts("Operands:");
    fputs("##       TYPE  VISIBILITY  ACTION      ENCODING   SIZE  NELEM  ELEMSZ", stdout);
    fputs("  ELEMTYPE                        VALUE\n", stdout);
    fputs("==  =========  ==========  ======  ============   ====  =====  ======", stdout);
    fputs("  ========  ===========================\n", stdout);
    uint8_t immId = 0;
    for (uint8_t i = 0; i < instruction->operandCount; ++i)
    {
        static const char* operandTypes[] =
        {
            "UNUSED",
            "REGISTER",
            "MEMORY",
            "POINTER",
            "IMMEDIATE"
        };
        static const char* operandVisibilities[] =
        {
            "INVALID",
            "EXPLICIT",                                                                        
            "IMPLICIT",
            "HIDDEN"
        };
        static const char* operandActions[] =
        {
            "INV",
            "R",
            "W",
            "RW",
            "CR",
            "CW",
            "RCW",
            "CRW"
        };
        static const char* elementTypes[] =
        {
            "INVALID",
            "STRUCT",
            "UINT",
            "INT",
            "FLOAT16",
            "FLOAT32",
            "FLOAT64",
            "FLOAT80",
            "LONGBCD"
        };
        static const char* operandEncodings[] =
        {
            "NONE",
            "MODRM_REG",
            "MODRM_RM",
            "OPCODE",
            "NDSNDD",
            "IS4",
            "MASK",
            "DISP8",
            "DISP16",
            "DISP32",
            "DISP64",
            "DISP16_32_64",
            "DISP32_32_64",
            "DISP16_32_32",
            "UIMM8",
            "UIMM16",
            "UIMM32",
            "UIMM64",
            "UIMM16_32_64",
            "UIMM32_32_64",
            "UIMM16_32_32",
            "SIMM8",
            "SIMM16",
            "SIMM32",
            "SIMM64",
            "SIMM16_32_64",
            "SIMM32_32_64",
            "SIMM16_32_32",
            "JIMM8",
            "JIMM16",
            "JIMM32",
            "JIMM64",
            "JIMM16_32_64",
            "JIMM32_32_64",
            "JIMM16_32_32"
        };
        printf("%2d  %9s  %10s  %6s  %12s  %5d   %4d  %6d  %8s", 
            i,
            operandTypes[instruction->operands[i].type],
            operandVisibilities[instruction->operands[i].visibility],
            operandActions[instruction->operands[i].action],
            operandEncodings[instruction->operands[i].encoding],
            instruction->operands[i].size,
            instruction->operands[i].elementCount,
            instruction->operands[i].elementSize, 
            elementTypes[instruction->operands[i].elementType]);
        switch (instruction->operands[i].type)
        {
        case ZYDIS_OPERAND_TYPE_REGISTER:
            printf("  %27s", ZydisRegisterGetString(instruction->operands[i].reg));
            break;
        case ZYDIS_OPERAND_TYPE_MEMORY:
            printf("  SEG   =%20s\n", ZydisRegisterGetString(instruction->operands[i].mem.segment));
            printf("  %84s =%20s\n", 
                "BASE ", ZydisRegisterGetString(instruction->operands[i].mem.base));
            printf("  %84s =%20s\n", 
                "INDEX", ZydisRegisterGetString(instruction->operands[i].mem.index));
            printf("  %84s =%20d\n", "SCALE", instruction->operands[i].mem.scale);
            printf("  %84s =  0x%016"PRIX64, 
                "DISP ", instruction->operands[i].mem.disp.value);
            break;
        case ZYDIS_OPERAND_TYPE_POINTER:
            break;
        case ZYDIS_OPERAND_TYPE_IMMEDIATE:
            if (instruction->operands[i].imm.isSigned)
            {
                printf("  (%s %s %2d) 0x%016"PRIX64, 
                    instruction->operands[i].imm.isSigned ? "S" : "U", 
                    instruction->operands[i].imm.isRelative ? "R" : "_", 
                    instruction->raw.imm[immId].size,
                    instruction->operands[i].imm.value.s);
            } else
            {
                printf("  SIGN  =%20s\n", instruction->operands[i].imm.isSigned ? "Y" : "N");
                printf("  %84s =%20s\n", 
                    "REL  ", instruction->operands[i].imm.isRelative ? "Y" : "N");
                printf("  %84s =                  %2d\n", 
                    "SIZE ", instruction->raw.imm[immId].size);
                printf("  %84s =  0x%016"PRIX64, 
                    "VALUE", instruction->operands[i].imm.value.u);
            }
            ++immId;
            break;
        default:
            ZYDIS_UNREACHABLE;
        }
        puts("");
    }
    fputs("==  =========  ==========  ======  ============   ====  =====  ======", stdout);
    fputs("  ========  ===========================\n", stdout);    
}

void printInstruction(ZydisDecodedInstruction* instruction)
{
    ZydisFormatter formatter;
    ZydisFormatterInitEx(&formatter, ZYDIS_FORMATTER_STYLE_INTEL,
        ZYDIS_FMTFLAG_FORCE_SEGMENTS | ZYDIS_FMTFLAG_FORCE_OPERANDSIZE,
        ZYDIS_FORMATTER_ADDR_ABSOLUTE, ZYDIS_FORMATTER_DISP_DEFAULT, ZYDIS_FORMATTER_IMM_DEFAULT);
    char buffer[256];
    ZydisFormatterFormatInstruction(&formatter, instruction, &buffer[0], sizeof(buffer));  
    printf("Mnemonic   : %s\n", ZydisMnemonicGetString(instruction->mnemonic));
    printf("Disassembly: %s\n\n", &buffer[0]);
    
    printOperands(instruction);
    
    if (ZydisRegisterGetClass(
        instruction->operands[instruction->operandCount - 1].reg) == ZYDIS_REGCLASS_FLAGS)
    {
        puts("");
        printFlags(instruction);
    }
}

/* ============================================================================================== */
/* Entry point                                                                                    */
/* ============================================================================================== */

#include <../src/SharedData.h>

int main(int argc, char** argv)
{
    printf("%"PRId64"\n", (uint64_t)sizeof(ZydisInstructionDefinitionDEFAULT));
    printf("%"PRId64"\n", (uint64_t)sizeof(ZydisInstructionDefinitionEVEX));
    printf("%"PRId64"\n", (uint64_t)sizeof(ZydisOperandDefinition));

    if (argc < 3)
    {
        fputs("Usage: ZydisInfo -[16|32|64] [hexbytes]\n", stderr);
        return ZYDIS_STATUS_INVALID_PARAMETER;
    }

    ZydisDecoder decoder;
    if (!strcmp(argv[1], "-16"))
    {
        ZydisDecoderInit(&decoder, ZYDIS_MACHINE_MODE_LONG_COMPAT_16, ZYDIS_ADDRESS_WIDTH_16);   
    } else
    if (!strcmp(argv[1], "-32"))
    {
        ZydisDecoderInit(&decoder, ZYDIS_MACHINE_MODE_LONG_COMPAT_32, ZYDIS_ADDRESS_WIDTH_32);   
    } else
    if (!strcmp(argv[1], "-64"))
    {
        ZydisDecoderInit(&decoder, ZYDIS_MACHINE_MODE_LONG_64, ZYDIS_ADDRESS_WIDTH_64);   
    } else
    {
        fputs("Usage: ZydisInfo -[16|32|64] [hexbytes]\n", stderr);
        return ZYDIS_STATUS_INVALID_PARAMETER;
    }

    uint8_t data[ZYDIS_MAX_INSTRUCTION_LENGTH] =
    {
        0x48, 0xC1, 0xC0, 0x04//0x0F, 0x01, 0xC3//0x48, 0x00, 0xC0//0x48, 0x8B, 0x04, 0x05, 0x00, 0x00, 0x00, 0x00//0xC4, 0xE3, 0x89, 0x48, 0x8C, 0x98, 0x00, 0x01, 0x00, 0x00, 0x38//0x62, 0xF1, 0x6C, 0x5F, 0xC2, 0x54, 0x98, 0x40, 0x0F
    };

    ZydisDecodedInstruction instruction;
    ZydisStatus status = 
        ZydisDecoderDecodeBuffer(&decoder, &data, ZYDIS_MAX_INSTRUCTION_LENGTH, 0, &instruction);
    if (!ZYDIS_SUCCESS(status))
    {
        if (status >= ZYDIS_STATUS_USER)
        {
            fprintf(stderr, 
                "Could not decode instruction: User defined status code 0x%"PRIx32, status);     
        } else
        {
            fprintf(stderr, "Could not decode instruction: %s", ZydisFormatStatus(status));
        }
        return status;
    }

    printInstruction(&instruction);
    
    getchar();

    return ZYDIS_STATUS_SUCCESS;
}

/* ============================================================================================== */
