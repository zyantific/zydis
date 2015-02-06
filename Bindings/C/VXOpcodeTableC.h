/**************************************************************************************************

  Verteron Disassembler Engine
  Version 1.0

  Remarks         : Freeware, Copyright must be included

  Original Author : Florian Bernd
  Modifications   : athre0z

  Last change     : 04. February 2015

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

**************************************************************************************************/

/* NOTE: fully ported to C */

#ifndef _VDE_VXOPCODETABLEC_H_
#define _VDE_VXOPCODETABLEC_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @brief   Values that represent an instruction mnemonic.
 */
typedef enum _VXInstructionMnemonic /* : uint16_t */
{
    /* 000 */ MNEM_INVALID,
    /* 001 */ MNEM_AAA,
    /* 002 */ MNEM_AAD,
    /* 003 */ MNEM_AAM,
    /* 004 */ MNEM_AAS,
    /* 005 */ MNEM_ADC,
    /* 006 */ MNEM_ADD,
    /* 007 */ MNEM_ADDPD,
    /* 008 */ MNEM_ADDPS,
    /* 009 */ MNEM_ADDSD,
    /* 00A */ MNEM_ADDSS,
    /* 00B */ MNEM_ADDSUBPD,
    /* 00C */ MNEM_ADDSUBPS,
    /* 00D */ MNEM_AESDEC,
    /* 00E */ MNEM_AESDECLAST,
    /* 00F */ MNEM_AESENC,
    /* 010 */ MNEM_AESENCLAST,
    /* 011 */ MNEM_AESIMC,
    /* 012 */ MNEM_AESKEYGENASSIST,
    /* 013 */ MNEM_AND,
    /* 014 */ MNEM_ANDNPD,
    /* 015 */ MNEM_ANDNPS,
    /* 016 */ MNEM_ANDPD,
    /* 017 */ MNEM_ANDPS,
    /* 018 */ MNEM_ARPL,
    /* 019 */ MNEM_BLENDPD,
    /* 01A */ MNEM_BLENDPS,
    /* 01B */ MNEM_BLENDVPD,
    /* 01C */ MNEM_BLENDVPS,
    /* 01D */ MNEM_BOUND,
    /* 01E */ MNEM_BSF,
    /* 01F */ MNEM_BSR,
    /* 020 */ MNEM_BSWAP,
    /* 021 */ MNEM_BT,
    /* 022 */ MNEM_BTC,
    /* 023 */ MNEM_BTR,
    /* 024 */ MNEM_BTS,
    /* 025 */ MNEM_CALL,
    /* 026 */ MNEM_CBW,
    /* 027 */ MNEM_CDQ,
    /* 028 */ MNEM_CDQE,
    /* 029 */ MNEM_CLC,
    /* 02A */ MNEM_CLD,
    /* 02B */ MNEM_CLFLUSH,
    /* 02C */ MNEM_CLGI,
    /* 02D */ MNEM_CLI,
    /* 02E */ MNEM_CLTS,
    /* 02F */ MNEM_CMC,
    /* 030 */ MNEM_CMOVA,
    /* 031 */ MNEM_CMOVAE,
    /* 032 */ MNEM_CMOVB,
    /* 033 */ MNEM_CMOVBE,
    /* 034 */ MNEM_CMOVE,
    /* 035 */ MNEM_CMOVG,
    /* 036 */ MNEM_CMOVGE,
    /* 037 */ MNEM_CMOVL,
    /* 038 */ MNEM_CMOVLE,
    /* 039 */ MNEM_CMOVNE,
    /* 03A */ MNEM_CMOVNO,
    /* 03B */ MNEM_CMOVNP,
    /* 03C */ MNEM_CMOVNS,
    /* 03D */ MNEM_CMOVO,
    /* 03E */ MNEM_CMOVP,
    /* 03F */ MNEM_CMOVS,
    /* 040 */ MNEM_CMP,
    /* 041 */ MNEM_CMPPD,
    /* 042 */ MNEM_CMPPS,
    /* 043 */ MNEM_CMPSB,
    /* 044 */ MNEM_CMPSD,
    /* 045 */ MNEM_CMPSQ,
    /* 046 */ MNEM_CMPSS,
    /* 047 */ MNEM_CMPSW,
    /* 048 */ MNEM_CMPXCHG,
    /* 049 */ MNEM_CMPXCHG16B,
    /* 04A */ MNEM_CMPXCHG8B,
    /* 04B */ MNEM_COMISD,
    /* 04C */ MNEM_COMISS,
    /* 04D */ MNEM_CPUID,
    /* 04E */ MNEM_CQO,
    /* 04F */ MNEM_CRC32,
    /* 050 */ MNEM_CVTDQ2PD,
    /* 051 */ MNEM_CVTDQ2PS,
    /* 052 */ MNEM_CVTPD2DQ,
    /* 053 */ MNEM_CVTPD2PI,
    /* 054 */ MNEM_CVTPD2PS,
    /* 055 */ MNEM_CVTPI2PD,
    /* 056 */ MNEM_CVTPI2PS,
    /* 057 */ MNEM_CVTPS2DQ,
    /* 058 */ MNEM_CVTPS2PD,
    /* 059 */ MNEM_CVTPS2PI,
    /* 05A */ MNEM_CVTSD2SI,
    /* 05B */ MNEM_CVTSD2SS,
    /* 05C */ MNEM_CVTSI2SD,
    /* 05D */ MNEM_CVTSI2SS,
    /* 05E */ MNEM_CVTSS2SD,
    /* 05F */ MNEM_CVTSS2SI,
    /* 060 */ MNEM_CVTTPD2DQ,
    /* 061 */ MNEM_CVTTPD2PI,
    /* 062 */ MNEM_CVTTPS2DQ,
    /* 063 */ MNEM_CVTTPS2PI,
    /* 064 */ MNEM_CVTTSD2SI,
    /* 065 */ MNEM_CVTTSS2SI,
    /* 066 */ MNEM_CWD,
    /* 067 */ MNEM_CWDE,
    /* 068 */ MNEM_DAA,
    /* 069 */ MNEM_DAS,
    /* 06A */ MNEM_DEC,
    /* 06B */ MNEM_DIV,
    /* 06C */ MNEM_DIVPD,
    /* 06D */ MNEM_DIVPS,
    /* 06E */ MNEM_DIVSD,
    /* 06F */ MNEM_DIVSS,
    /* 070 */ MNEM_DPPD,
    /* 071 */ MNEM_DPPS,
    /* 072 */ MNEM_EMMS,
    /* 073 */ MNEM_ENTER,
    /* 074 */ MNEM_EXTRACTPS,
    /* 075 */ MNEM_F2XM1,
    /* 076 */ MNEM_FABS,
    /* 077 */ MNEM_FADD,
    /* 078 */ MNEM_FADDP,
    /* 079 */ MNEM_FBLD,
    /* 07A */ MNEM_FBSTP,
    /* 07B */ MNEM_FCHS,
    /* 07C */ MNEM_FCLEX,
    /* 07D */ MNEM_FCMOVB,
    /* 07E */ MNEM_FCMOVBE,
    /* 07F */ MNEM_FCMOVE,
    /* 080 */ MNEM_FCMOVNB,
    /* 081 */ MNEM_FCMOVNBE,
    /* 082 */ MNEM_FCMOVNE,
    /* 083 */ MNEM_FCMOVNU,
    /* 084 */ MNEM_FCMOVU,
    /* 085 */ MNEM_FCOM,
    /* 086 */ MNEM_FCOM2,
    /* 087 */ MNEM_FCOMI,
    /* 088 */ MNEM_FCOMIP,
    /* 089 */ MNEM_FCOMP,
    /* 08A */ MNEM_FCOMP3,
    /* 08B */ MNEM_FCOMP5,
    /* 08C */ MNEM_FCOMPP,
    /* 08D */ MNEM_FCOS,
    /* 08E */ MNEM_FDECSTP,
    /* 08F */ MNEM_FDIV,
    /* 090 */ MNEM_FDIVP,
    /* 091 */ MNEM_FDIVR,
    /* 092 */ MNEM_FDIVRP,
    /* 093 */ MNEM_FEMMS,
    /* 094 */ MNEM_FFREE,
    /* 095 */ MNEM_FFREEP,
    /* 096 */ MNEM_FIADD,
    /* 097 */ MNEM_FICOM,
    /* 098 */ MNEM_FICOMP,
    /* 099 */ MNEM_FIDIV,
    /* 09A */ MNEM_FIDIVR,
    /* 09B */ MNEM_FILD,
    /* 09C */ MNEM_FIMUL,
    /* 09D */ MNEM_FINCSTP,
    /* 09E */ MNEM_FIST,
    /* 09F */ MNEM_FISTP,
    /* 0A0 */ MNEM_FISTTP,
    /* 0A1 */ MNEM_FISUB,
    /* 0A2 */ MNEM_FISUBR,
    /* 0A3 */ MNEM_FLD,
    /* 0A4 */ MNEM_FLD1,
    /* 0A5 */ MNEM_FLDCW,
    /* 0A6 */ MNEM_FLDENV,
    /* 0A7 */ MNEM_FLDL2E,
    /* 0A8 */ MNEM_FLDL2T,
    /* 0A9 */ MNEM_FLDLG2,
    /* 0AA */ MNEM_FLDLN2,
    /* 0AB */ MNEM_FLDPI,
    /* 0AC */ MNEM_FLDZ,
    /* 0AD */ MNEM_FMUL,
    /* 0AE */ MNEM_FMULP,
    /* 0AF */ MNEM_FNDISI,
    /* 0B0 */ MNEM_FNENI,
    /* 0B1 */ MNEM_FNINIT,
    /* 0B2 */ MNEM_FNOP,
    /* 0B3 */ MNEM_FNSAVE,
    /* 0B4 */ MNEM_FNSETPM,
    /* 0B5 */ MNEM_FNSTCW,
    /* 0B6 */ MNEM_FNSTENV,
    /* 0B7 */ MNEM_FNSTSW,
    /* 0B8 */ MNEM_FPATAN,
    /* 0B9 */ MNEM_FPREM,
    /* 0BA */ MNEM_FPREM1,
    /* 0BB */ MNEM_FPTAN,
    /* 0BC */ MNEM_FRNDINT,
    /* 0BD */ MNEM_FRSTOR,
    /* 0BE */ MNEM_FRSTPM,
    /* 0BF */ MNEM_FSCALE,
    /* 0C0 */ MNEM_FSIN,
    /* 0C1 */ MNEM_FSINCOS,
    /* 0C2 */ MNEM_FSQRT,
    /* 0C3 */ MNEM_FST,
    /* 0C4 */ MNEM_FSTP,
    /* 0C5 */ MNEM_FSTP1,
    /* 0C6 */ MNEM_FSTP8,
    /* 0C7 */ MNEM_FSTP9,
    /* 0C8 */ MNEM_FSUB,
    /* 0C9 */ MNEM_FSUBP,
    /* 0CA */ MNEM_FSUBR,
    /* 0CB */ MNEM_FSUBRP,
    /* 0CC */ MNEM_FTST,
    /* 0CD */ MNEM_FUCOM,
    /* 0CE */ MNEM_FUCOMI,
    /* 0CF */ MNEM_FUCOMIP,
    /* 0D0 */ MNEM_FUCOMP,
    /* 0D1 */ MNEM_FUCOMPP,
    /* 0D2 */ MNEM_FXAM,
    /* 0D3 */ MNEM_FXCH,
    /* 0D4 */ MNEM_FXCH4,
    /* 0D5 */ MNEM_FXCH7,
    /* 0D6 */ MNEM_FXRSTOR,
    /* 0D7 */ MNEM_FXSAVE,
    /* 0D8 */ MNEM_FXTRACT,
    /* 0D9 */ MNEM_FYL2X,
    /* 0DA */ MNEM_FYL2XP1,
    /* 0DB */ MNEM_GETSEC,
    /* 0DC */ MNEM_HADDPD,
    /* 0DD */ MNEM_HADDPS,
    /* 0DE */ MNEM_HLT,
    /* 0DF */ MNEM_HSUBPD,
    /* 0E0 */ MNEM_HSUBPS,
    /* 0E1 */ MNEM_IDIV,
    /* 0E2 */ MNEM_IMUL,
    /* 0E3 */ MNEM_IN,
    /* 0E4 */ MNEM_INC,
    /* 0E5 */ MNEM_INSB,
    /* 0E6 */ MNEM_INSD,
    /* 0E7 */ MNEM_INSERTPS,
    /* 0E8 */ MNEM_INSW,
    /* 0E9 */ MNEM_INT,
    /* 0EA */ MNEM_INT1,
    /* 0EB */ MNEM_INT3,
    /* 0EC */ MNEM_INTO,
    /* 0ED */ MNEM_INVD,
    /* 0EE */ MNEM_INVEPT,
    /* 0EF */ MNEM_INVLPG,
    /* 0F0 */ MNEM_INVLPGA,
    /* 0F1 */ MNEM_INVVPID,
    /* 0F2 */ MNEM_IRETD,
    /* 0F3 */ MNEM_IRETQ,
    /* 0F4 */ MNEM_IRETW,
    /* 0F5 */ MNEM_JA,
    /* 0F6 */ MNEM_JB,
    /* 0F7 */ MNEM_JBE,
    /* 0F8 */ MNEM_JCXZ,
    /* 0F9 */ MNEM_JE,
    /* 0FA */ MNEM_JECXZ,
    /* 0FB */ MNEM_JG,
    /* 0FC */ MNEM_JGE,
    /* 0FD */ MNEM_JL,
    /* 0FE */ MNEM_JLE,
    /* 0FF */ MNEM_JMP,
    /* 100 */ MNEM_JNB,
    /* 101 */ MNEM_JNE,
    /* 102 */ MNEM_JNO,
    /* 103 */ MNEM_JNP,
    /* 104 */ MNEM_JNS,
    /* 105 */ MNEM_JO,
    /* 106 */ MNEM_JP,
    /* 107 */ MNEM_JRCXZ,
    /* 108 */ MNEM_JS,
    /* 109 */ MNEM_LAHF,
    /* 10A */ MNEM_LAR,
    /* 10B */ MNEM_LDDQU,
    /* 10C */ MNEM_LDMXCSR,
    /* 10D */ MNEM_LDS,
    /* 10E */ MNEM_LEA,
    /* 10F */ MNEM_LEAVE,
    /* 110 */ MNEM_LES,
    /* 111 */ MNEM_LFENCE,
    /* 112 */ MNEM_LFS,
    /* 113 */ MNEM_LGDT,
    /* 114 */ MNEM_LGS,
    /* 115 */ MNEM_LIDT,
    /* 116 */ MNEM_LLDT,
    /* 117 */ MNEM_LMSW,
    /* 118 */ MNEM_LOCK,
    /* 119 */ MNEM_LODSB,
    /* 11A */ MNEM_LODSD,
    /* 11B */ MNEM_LODSQ,
    /* 11C */ MNEM_LODSW,
    /* 11D */ MNEM_LOOP,
    /* 11E */ MNEM_LOOPE,
    /* 11F */ MNEM_LOOPNE,
    /* 120 */ MNEM_LSL,
    /* 121 */ MNEM_LSS,
    /* 122 */ MNEM_LTR,
    /* 123 */ MNEM_MASKMOVDQU,
    /* 124 */ MNEM_MASKMOVQ,
    /* 125 */ MNEM_MAXPD,
    /* 126 */ MNEM_MAXPS,
    /* 127 */ MNEM_MAXSD,
    /* 128 */ MNEM_MAXSS,
    /* 129 */ MNEM_MFENCE,
    /* 12A */ MNEM_MINPD,
    /* 12B */ MNEM_MINPS,
    /* 12C */ MNEM_MINSD,
    /* 12D */ MNEM_MINSS,
    /* 12E */ MNEM_MONITOR,
    /* 12F */ MNEM_MONTMUL,
    /* 130 */ MNEM_MOV,
    /* 131 */ MNEM_MOVAPD,
    /* 132 */ MNEM_MOVAPS,
    /* 133 */ MNEM_MOVBE,
    /* 134 */ MNEM_MOVD,
    /* 135 */ MNEM_MOVDDUP,
    /* 136 */ MNEM_MOVDQ2Q,
    /* 137 */ MNEM_MOVDQA,
    /* 138 */ MNEM_MOVDQU,
    /* 139 */ MNEM_MOVHLPS,
    /* 13A */ MNEM_MOVHPD,
    /* 13B */ MNEM_MOVHPS,
    /* 13C */ MNEM_MOVLHPS,
    /* 13D */ MNEM_MOVLPD,
    /* 13E */ MNEM_MOVLPS,
    /* 13F */ MNEM_MOVMSKPD,
    /* 140 */ MNEM_MOVMSKPS,
    /* 141 */ MNEM_MOVNTDQ,
    /* 142 */ MNEM_MOVNTDQA,
    /* 143 */ MNEM_MOVNTI,
    /* 144 */ MNEM_MOVNTPD,
    /* 145 */ MNEM_MOVNTPS,
    /* 146 */ MNEM_MOVNTQ,
    /* 147 */ MNEM_MOVQ,
    /* 148 */ MNEM_MOVQ2DQ,
    /* 149 */ MNEM_MOVSB,
    /* 14A */ MNEM_MOVSD,
    /* 14B */ MNEM_MOVSHDUP,
    /* 14C */ MNEM_MOVSLDUP,
    /* 14D */ MNEM_MOVSQ,
    /* 14E */ MNEM_MOVSS,
    /* 14F */ MNEM_MOVSW,
    /* 150 */ MNEM_MOVSX,
    /* 151 */ MNEM_MOVSXD,
    /* 152 */ MNEM_MOVUPD,
    /* 153 */ MNEM_MOVUPS,
    /* 154 */ MNEM_MOVZX,
    /* 155 */ MNEM_MPSADBW,
    /* 156 */ MNEM_MUL,
    /* 157 */ MNEM_MULPD,
    /* 158 */ MNEM_MULPS,
    /* 159 */ MNEM_MULSD,
    /* 15A */ MNEM_MULSS,
    /* 15B */ MNEM_MWAIT,
    /* 15C */ MNEM_NEG,
    /* 15D */ MNEM_NOP,
    /* 15E */ MNEM_NOT,
    /* 15F */ MNEM_OR,
    /* 160 */ MNEM_ORPD,
    /* 161 */ MNEM_ORPS,
    /* 162 */ MNEM_OUT,
    /* 163 */ MNEM_OUTSB,
    /* 164 */ MNEM_OUTSD,
    /* 165 */ MNEM_OUTSW,
    /* 166 */ MNEM_PABSB,
    /* 167 */ MNEM_PABSD,
    /* 168 */ MNEM_PABSW,
    /* 169 */ MNEM_PACKSSDW,
    /* 16A */ MNEM_PACKSSWB,
    /* 16B */ MNEM_PACKUSDW,
    /* 16C */ MNEM_PACKUSWB,
    /* 16D */ MNEM_PADDB,
    /* 16E */ MNEM_PADDD,
    /* 16F */ MNEM_PADDQ,
    /* 170 */ MNEM_PADDSB,
    /* 171 */ MNEM_PADDSW,
    /* 172 */ MNEM_PADDUSB,
    /* 173 */ MNEM_PADDUSW,
    /* 174 */ MNEM_PADDW,
    /* 175 */ MNEM_PALIGNR,
    /* 176 */ MNEM_PAND,
    /* 177 */ MNEM_PANDN,
    /* 178 */ MNEM_PAUSE,
    /* 179 */ MNEM_PAVGB,
    /* 17A */ MNEM_PAVGUSB,
    /* 17B */ MNEM_PAVGW,
    /* 17C */ MNEM_PBLENDVB,
    /* 17D */ MNEM_PBLENDW,
    /* 17E */ MNEM_PCLMULQDQ,
    /* 17F */ MNEM_PCMPEQB,
    /* 180 */ MNEM_PCMPEQD,
    /* 181 */ MNEM_PCMPEQQ,
    /* 182 */ MNEM_PCMPEQW,
    /* 183 */ MNEM_PCMPESTRI,
    /* 184 */ MNEM_PCMPESTRM,
    /* 185 */ MNEM_PCMPGTB,
    /* 186 */ MNEM_PCMPGTD,
    /* 187 */ MNEM_PCMPGTQ,
    /* 188 */ MNEM_PCMPGTW,
    /* 189 */ MNEM_PCMPISTRI,
    /* 18A */ MNEM_PCMPISTRM,
    /* 18B */ MNEM_PEXTRB,
    /* 18C */ MNEM_PEXTRD,
    /* 18D */ MNEM_PEXTRQ,
    /* 18E */ MNEM_PEXTRW,
    /* 18F */ MNEM_PF2ID,
    /* 190 */ MNEM_PF2IW,
    /* 191 */ MNEM_PFACC,
    /* 192 */ MNEM_PFADD,
    /* 193 */ MNEM_PFCMPEQ,
    /* 194 */ MNEM_PFCMPGE,
    /* 195 */ MNEM_PFCMPGT,
    /* 196 */ MNEM_PFMAX,
    /* 197 */ MNEM_PFMIN,
    /* 198 */ MNEM_PFMUL,
    /* 199 */ MNEM_PFNACC,
    /* 19A */ MNEM_PFPNACC,
    /* 19B */ MNEM_PFRCP,
    /* 19C */ MNEM_PFRCPIT1,
    /* 19D */ MNEM_PFRCPIT2,
    /* 19E */ MNEM_PFRSQIT1,
    /* 19F */ MNEM_PFRSQRT,
    /* 1A0 */ MNEM_PFSUB,
    /* 1A1 */ MNEM_PFSUBR,
    /* 1A2 */ MNEM_PHADDD,
    /* 1A3 */ MNEM_PHADDSW,
    /* 1A4 */ MNEM_PHADDW,
    /* 1A5 */ MNEM_PHMINPOSUW,
    /* 1A6 */ MNEM_PHSUBD,
    /* 1A7 */ MNEM_PHSUBSW,
    /* 1A8 */ MNEM_PHSUBW,
    /* 1A9 */ MNEM_PI2FD,
    /* 1AA */ MNEM_PI2FW,
    /* 1AB */ MNEM_PINSRB,
    /* 1AC */ MNEM_PINSRD,
    /* 1AD */ MNEM_PINSRQ,
    /* 1AE */ MNEM_PINSRW,
    /* 1AF */ MNEM_PMADDUBSW,
    /* 1B0 */ MNEM_PMADDWD,
    /* 1B1 */ MNEM_PMAXSB,
    /* 1B2 */ MNEM_PMAXSD,
    /* 1B3 */ MNEM_PMAXSW,
    /* 1B4 */ MNEM_PMAXUB,
    /* 1B5 */ MNEM_PMAXUD,
    /* 1B6 */ MNEM_PMAXUW,
    /* 1B7 */ MNEM_PMINSB,
    /* 1B8 */ MNEM_PMINSD,
    /* 1B9 */ MNEM_PMINSW,
    /* 1BA */ MNEM_PMINUB,
    /* 1BB */ MNEM_PMINUD,
    /* 1BC */ MNEM_PMINUW,
    /* 1BD */ MNEM_PMOVMSKB,
    /* 1BE */ MNEM_PMOVSXBD,
    /* 1BF */ MNEM_PMOVSXBQ,
    /* 1C0 */ MNEM_PMOVSXBW,
    /* 1C1 */ MNEM_PMOVSXDQ,
    /* 1C2 */ MNEM_PMOVSXWD,
    /* 1C3 */ MNEM_PMOVSXWQ,
    /* 1C4 */ MNEM_PMOVZXBD,
    /* 1C5 */ MNEM_PMOVZXBQ,
    /* 1C6 */ MNEM_PMOVZXBW,
    /* 1C7 */ MNEM_PMOVZXDQ,
    /* 1C8 */ MNEM_PMOVZXWD,
    /* 1C9 */ MNEM_PMOVZXWQ,
    /* 1CA */ MNEM_PMULDQ,
    /* 1CB */ MNEM_PMULHRSW,
    /* 1CC */ MNEM_PMULHRW,
    /* 1CD */ MNEM_PMULHUW,
    /* 1CE */ MNEM_PMULHW,
    /* 1CF */ MNEM_PMULLD,
    /* 1D0 */ MNEM_PMULLW,
    /* 1D1 */ MNEM_PMULUDQ,
    /* 1D2 */ MNEM_POP,
    /* 1D3 */ MNEM_POPA,
    /* 1D4 */ MNEM_POPAD,
    /* 1D5 */ MNEM_POPCNT,
    /* 1D6 */ MNEM_POPFD,
    /* 1D7 */ MNEM_POPFQ,
    /* 1D8 */ MNEM_POPFW,
    /* 1D9 */ MNEM_POR,
    /* 1DA */ MNEM_PREFETCH,
    /* 1DB */ MNEM_PREFETCHNTA,
    /* 1DC */ MNEM_PREFETCHT0,
    /* 1DD */ MNEM_PREFETCHT1,
    /* 1DE */ MNEM_PREFETCHT2,
    /* 1DF */ MNEM_PSADBW,
    /* 1E0 */ MNEM_PSHUFB,
    /* 1E1 */ MNEM_PSHUFD,
    /* 1E2 */ MNEM_PSHUFHW,
    /* 1E3 */ MNEM_PSHUFLW,
    /* 1E4 */ MNEM_PSHUFW,
    /* 1E5 */ MNEM_PSIGNB,
    /* 1E6 */ MNEM_PSIGND,
    /* 1E7 */ MNEM_PSIGNW,
    /* 1E8 */ MNEM_PSLLD,
    /* 1E9 */ MNEM_PSLLDQ,
    /* 1EA */ MNEM_PSLLQ,
    /* 1EB */ MNEM_PSLLW,
    /* 1EC */ MNEM_PSRAD,
    /* 1ED */ MNEM_PSRAW,
    /* 1EE */ MNEM_PSRLD,
    /* 1EF */ MNEM_PSRLDQ,
    /* 1F0 */ MNEM_PSRLQ,
    /* 1F1 */ MNEM_PSRLW,
    /* 1F2 */ MNEM_PSUBB,
    /* 1F3 */ MNEM_PSUBD,
    /* 1F4 */ MNEM_PSUBQ,
    /* 1F5 */ MNEM_PSUBSB,
    /* 1F6 */ MNEM_PSUBSW,
    /* 1F7 */ MNEM_PSUBUSB,
    /* 1F8 */ MNEM_PSUBUSW,
    /* 1F9 */ MNEM_PSUBW,
    /* 1FA */ MNEM_PSWAPD,
    /* 1FB */ MNEM_PTEST,
    /* 1FC */ MNEM_PUNPCKHBW,
    /* 1FD */ MNEM_PUNPCKHDQ,
    /* 1FE */ MNEM_PUNPCKHQDQ,
    /* 1FF */ MNEM_PUNPCKHWD,
    /* 200 */ MNEM_PUNPCKLBW,
    /* 201 */ MNEM_PUNPCKLDQ,
    /* 202 */ MNEM_PUNPCKLQDQ,
    /* 203 */ MNEM_PUNPCKLWD,
    /* 204 */ MNEM_PUSH,
    /* 205 */ MNEM_PUSHA,
    /* 206 */ MNEM_PUSHAD,
    /* 207 */ MNEM_PUSHFD,
    /* 208 */ MNEM_PUSHFQ,
    /* 209 */ MNEM_PUSHFW,
    /* 20A */ MNEM_PXOR,
    /* 20B */ MNEM_RCL,
    /* 20C */ MNEM_RCPPS,
    /* 20D */ MNEM_RCPSS,
    /* 20E */ MNEM_RCR,
    /* 20F */ MNEM_RDMSR,
    /* 210 */ MNEM_RDPMC,
    /* 211 */ MNEM_RDRAND,
    /* 212 */ MNEM_RDTSC,
    /* 213 */ MNEM_RDTSCP,
    /* 214 */ MNEM_REP,
    /* 215 */ MNEM_REPNE,
    /* 216 */ MNEM_RET,
    /* 217 */ MNEM_RETF,
    /* 218 */ MNEM_ROL,
    /* 219 */ MNEM_ROR,
    /* 21A */ MNEM_ROUNDPD,
    /* 21B */ MNEM_ROUNDPS,
    /* 21C */ MNEM_ROUNDSD,
    /* 21D */ MNEM_ROUNDSS,
    /* 21E */ MNEM_RSM,
    /* 21F */ MNEM_RSQRTPS,
    /* 220 */ MNEM_RSQRTSS,
    /* 221 */ MNEM_SAHF,
    /* 222 */ MNEM_SALC,
    /* 223 */ MNEM_SAR,
    /* 224 */ MNEM_SBB,
    /* 225 */ MNEM_SCASB,
    /* 226 */ MNEM_SCASD,
    /* 227 */ MNEM_SCASQ,
    /* 228 */ MNEM_SCASW,
    /* 229 */ MNEM_SETA,
    /* 22A */ MNEM_SETAE,
    /* 22B */ MNEM_SETB,
    /* 22C */ MNEM_SETBE,
    /* 22D */ MNEM_SETE,
    /* 22E */ MNEM_SETG,
    /* 22F */ MNEM_SETGE,
    /* 230 */ MNEM_SETL,
    /* 231 */ MNEM_SETLE,
    /* 232 */ MNEM_SETNE,
    /* 233 */ MNEM_SETNO,
    /* 234 */ MNEM_SETNP,
    /* 235 */ MNEM_SETNS,
    /* 236 */ MNEM_SETO,
    /* 237 */ MNEM_SETP,
    /* 238 */ MNEM_SETS,
    /* 239 */ MNEM_SFENCE,
    /* 23A */ MNEM_SGDT,
    /* 23B */ MNEM_SHL,
    /* 23C */ MNEM_SHLD,
    /* 23D */ MNEM_SHR,
    /* 23E */ MNEM_SHRD,
    /* 23F */ MNEM_SHUFPD,
    /* 240 */ MNEM_SHUFPS,
    /* 241 */ MNEM_SIDT,
    /* 242 */ MNEM_SKINIT,
    /* 243 */ MNEM_SLDT,
    /* 244 */ MNEM_SMSW,
    /* 245 */ MNEM_SQRTPD,
    /* 246 */ MNEM_SQRTPS,
    /* 247 */ MNEM_SQRTSD,
    /* 248 */ MNEM_SQRTSS,
    /* 249 */ MNEM_STC,
    /* 24A */ MNEM_STD,
    /* 24B */ MNEM_STGI,
    /* 24C */ MNEM_STI,
    /* 24D */ MNEM_STMXCSR,
    /* 24E */ MNEM_STOSB,
    /* 24F */ MNEM_STOSD,
    /* 250 */ MNEM_STOSQ,
    /* 251 */ MNEM_STOSW,
    /* 252 */ MNEM_STR,
    /* 253 */ MNEM_SUB,
    /* 254 */ MNEM_SUBPD,
    /* 255 */ MNEM_SUBPS,
    /* 256 */ MNEM_SUBSD,
    /* 257 */ MNEM_SUBSS,
    /* 258 */ MNEM_SWAPGS,
    /* 259 */ MNEM_SYSCALL,
    /* 25A */ MNEM_SYSENTER,
    /* 25B */ MNEM_SYSEXIT,
    /* 25C */ MNEM_SYSRET,
    /* 25D */ MNEM_TEST,
    /* 25E */ MNEM_UCOMISD,
    /* 25F */ MNEM_UCOMISS,
    /* 260 */ MNEM_UD2,
    /* 261 */ MNEM_UNPCKHPD,
    /* 262 */ MNEM_UNPCKHPS,
    /* 263 */ MNEM_UNPCKLPD,
    /* 264 */ MNEM_UNPCKLPS,
    /* 265 */ MNEM_VADDPD,
    /* 266 */ MNEM_VADDPS,
    /* 267 */ MNEM_VADDSD,
    /* 268 */ MNEM_VADDSS,
    /* 269 */ MNEM_VADDSUBPD,
    /* 26A */ MNEM_VADDSUBPS,
    /* 26B */ MNEM_VAESDEC,
    /* 26C */ MNEM_VAESDECLAST,
    /* 26D */ MNEM_VAESENC,
    /* 26E */ MNEM_VAESENCLAST,
    /* 26F */ MNEM_VAESIMC,
    /* 270 */ MNEM_VAESKEYGENASSIST,
    /* 271 */ MNEM_VANDNPD,
    /* 272 */ MNEM_VANDNPS,
    /* 273 */ MNEM_VANDPD,
    /* 274 */ MNEM_VANDPS,
    /* 275 */ MNEM_VBLENDPD,
    /* 276 */ MNEM_VBLENDPS,
    /* 277 */ MNEM_VBLENDVPD,
    /* 278 */ MNEM_VBLENDVPS,
    /* 279 */ MNEM_VBROADCASTSD,
    /* 27A */ MNEM_VBROADCASTSS,
    /* 27B */ MNEM_VCMPPD,
    /* 27C */ MNEM_VCMPPS,
    /* 27D */ MNEM_VCMPSD,
    /* 27E */ MNEM_VCMPSS,
    /* 27F */ MNEM_VCOMISD,
    /* 280 */ MNEM_VCOMISS,
    /* 281 */ MNEM_VCVTDQ2PD,
    /* 282 */ MNEM_VCVTDQ2PS,
    /* 283 */ MNEM_VCVTPD2DQ,
    /* 284 */ MNEM_VCVTPD2PS,
    /* 285 */ MNEM_VCVTPS2DQ,
    /* 286 */ MNEM_VCVTPS2PD,
    /* 287 */ MNEM_VCVTSD2SI,
    /* 288 */ MNEM_VCVTSD2SS,
    /* 289 */ MNEM_VCVTSI2SD,
    /* 28A */ MNEM_VCVTSI2SS,
    /* 28B */ MNEM_VCVTSS2SD,
    /* 28C */ MNEM_VCVTSS2SI,
    /* 28D */ MNEM_VCVTTPD2DQ,
    /* 28E */ MNEM_VCVTTPS2DQ,
    /* 28F */ MNEM_VCVTTSD2SI,
    /* 290 */ MNEM_VCVTTSS2SI,
    /* 291 */ MNEM_VDIVPD,
    /* 292 */ MNEM_VDIVPS,
    /* 293 */ MNEM_VDIVSD,
    /* 294 */ MNEM_VDIVSS,
    /* 295 */ MNEM_VDPPD,
    /* 296 */ MNEM_VDPPS,
    /* 297 */ MNEM_VERR,
    /* 298 */ MNEM_VERW,
    /* 299 */ MNEM_VEXTRACTF128,
    /* 29A */ MNEM_VEXTRACTPS,
    /* 29B */ MNEM_VHADDPD,
    /* 29C */ MNEM_VHADDPS,
    /* 29D */ MNEM_VHSUBPD,
    /* 29E */ MNEM_VHSUBPS,
    /* 29F */ MNEM_VINSERTF128,
    /* 2A0 */ MNEM_VINSERTPS,
    /* 2A1 */ MNEM_VLDDQU,
    /* 2A2 */ MNEM_VMASKMOVDQU,
    /* 2A3 */ MNEM_VMASKMOVPD,
    /* 2A4 */ MNEM_VMASKMOVPS,
    /* 2A5 */ MNEM_VMAXPD,
    /* 2A6 */ MNEM_VMAXPS,
    /* 2A7 */ MNEM_VMAXSD,
    /* 2A8 */ MNEM_VMAXSS,
    /* 2A9 */ MNEM_VMCALL,
    /* 2AA */ MNEM_VMCLEAR,
    /* 2AB */ MNEM_VMINPD,
    /* 2AC */ MNEM_VMINPS,
    /* 2AD */ MNEM_VMINSD,
    /* 2AE */ MNEM_VMINSS,
    /* 2AF */ MNEM_VMLAUNCH,
    /* 2B0 */ MNEM_VMLOAD,
    /* 2B1 */ MNEM_VMMCALL,
    /* 2B2 */ MNEM_VMOVAPD,
    /* 2B3 */ MNEM_VMOVAPS,
    /* 2B4 */ MNEM_VMOVD,
    /* 2B5 */ MNEM_VMOVDDUP,
    /* 2B6 */ MNEM_VMOVDQA,
    /* 2B7 */ MNEM_VMOVDQU,
    /* 2B8 */ MNEM_VMOVHLPS,
    /* 2B9 */ MNEM_VMOVHPD,
    /* 2BA */ MNEM_VMOVHPS,
    /* 2BB */ MNEM_VMOVLHPS,
    /* 2BC */ MNEM_VMOVLPD,
    /* 2BD */ MNEM_VMOVLPS,
    /* 2BE */ MNEM_VMOVMSKPD,
    /* 2BF */ MNEM_VMOVMSKPS,
    /* 2C0 */ MNEM_VMOVNTDQ,
    /* 2C1 */ MNEM_VMOVNTDQA,
    /* 2C2 */ MNEM_VMOVNTPD,
    /* 2C3 */ MNEM_VMOVNTPS,
    /* 2C4 */ MNEM_VMOVQ,
    /* 2C5 */ MNEM_VMOVSD,
    /* 2C6 */ MNEM_VMOVSHDUP,
    /* 2C7 */ MNEM_VMOVSLDUP,
    /* 2C8 */ MNEM_VMOVSS,
    /* 2C9 */ MNEM_VMOVUPD,
    /* 2CA */ MNEM_VMOVUPS,
    /* 2CB */ MNEM_VMPSADBW,
    /* 2CC */ MNEM_VMPTRLD,
    /* 2CD */ MNEM_VMPTRST,
    /* 2CE */ MNEM_VMREAD,
    /* 2CF */ MNEM_VMRESUME,
    /* 2D0 */ MNEM_VMRUN,
    /* 2D1 */ MNEM_VMSAVE,
    /* 2D2 */ MNEM_VMULPD,
    /* 2D3 */ MNEM_VMULPS,
    /* 2D4 */ MNEM_VMULSD,
    /* 2D5 */ MNEM_VMULSS,
    /* 2D6 */ MNEM_VMWRITE,
    /* 2D7 */ MNEM_VMXOFF,
    /* 2D8 */ MNEM_VMXON,
    /* 2D9 */ MNEM_VORPD,
    /* 2DA */ MNEM_VORPS,
    /* 2DB */ MNEM_VPABSB,
    /* 2DC */ MNEM_VPABSD,
    /* 2DD */ MNEM_VPABSW,
    /* 2DE */ MNEM_VPACKSSDW,
    /* 2DF */ MNEM_VPACKSSWB,
    /* 2E0 */ MNEM_VPACKUSDW,
    /* 2E1 */ MNEM_VPACKUSWB,
    /* 2E2 */ MNEM_VPADDB,
    /* 2E3 */ MNEM_VPADDD,
    /* 2E4 */ MNEM_VPADDQ,
    /* 2E5 */ MNEM_VPADDSB,
    /* 2E6 */ MNEM_VPADDSW,
    /* 2E7 */ MNEM_VPADDUSB,
    /* 2E8 */ MNEM_VPADDUSW,
    /* 2E9 */ MNEM_VPADDW,
    /* 2EA */ MNEM_VPALIGNR,
    /* 2EB */ MNEM_VPAND,
    /* 2EC */ MNEM_VPANDN,
    /* 2ED */ MNEM_VPAVGB,
    /* 2EE */ MNEM_VPAVGW,
    /* 2EF */ MNEM_VPBLENDVB,
    /* 2F0 */ MNEM_VPBLENDW,
    /* 2F1 */ MNEM_VPCLMULQDQ,
    /* 2F2 */ MNEM_VPCMPEQB,
    /* 2F3 */ MNEM_VPCMPEQD,
    /* 2F4 */ MNEM_VPCMPEQQ,
    /* 2F5 */ MNEM_VPCMPEQW,
    /* 2F6 */ MNEM_VPCMPESTRI,
    /* 2F7 */ MNEM_VPCMPESTRM,
    /* 2F8 */ MNEM_VPCMPGTB,
    /* 2F9 */ MNEM_VPCMPGTD,
    /* 2FA */ MNEM_VPCMPGTQ,
    /* 2FB */ MNEM_VPCMPGTW,
    /* 2FC */ MNEM_VPCMPISTRI,
    /* 2FD */ MNEM_VPCMPISTRM,
    /* 2FE */ MNEM_VPERM2F128,
    /* 2FF */ MNEM_VPERMILPD,
    /* 300 */ MNEM_VPERMILPS,
    /* 301 */ MNEM_VPEXTRB,
    /* 302 */ MNEM_VPEXTRD,
    /* 303 */ MNEM_VPEXTRQ,
    /* 304 */ MNEM_VPEXTRW,
    /* 305 */ MNEM_VPHADDD,
    /* 306 */ MNEM_VPHADDSW,
    /* 307 */ MNEM_VPHADDW,
    /* 308 */ MNEM_VPHMINPOSUW,
    /* 309 */ MNEM_VPHSUBD,
    /* 30A */ MNEM_VPHSUBSW,
    /* 30B */ MNEM_VPHSUBW,
    /* 30C */ MNEM_VPINSRB,
    /* 30D */ MNEM_VPINSRD,
    /* 30E */ MNEM_VPINSRQ,
    /* 30F */ MNEM_VPINSRW,
    /* 310 */ MNEM_VPMADDUBSW,
    /* 311 */ MNEM_VPMADDWD,
    /* 312 */ MNEM_VPMAXSB,
    /* 313 */ MNEM_VPMAXSD,
    /* 314 */ MNEM_VPMAXSW,
    /* 315 */ MNEM_VPMAXUB,
    /* 316 */ MNEM_VPMAXUD,
    /* 317 */ MNEM_VPMAXUW,
    /* 318 */ MNEM_VPMINSB,
    /* 319 */ MNEM_VPMINSD,
    /* 31A */ MNEM_VPMINSW,
    /* 31B */ MNEM_VPMINUB,
    /* 31C */ MNEM_VPMINUD,
    /* 31D */ MNEM_VPMINUW,
    /* 31E */ MNEM_VPMOVMSKB,
    /* 31F */ MNEM_VPMOVSXBD,
    /* 320 */ MNEM_VPMOVSXBQ,
    /* 321 */ MNEM_VPMOVSXBW,
    /* 322 */ MNEM_VPMOVSXWD,
    /* 323 */ MNEM_VPMOVSXWQ,
    /* 324 */ MNEM_VPMOVZXBD,
    /* 325 */ MNEM_VPMOVZXBQ,
    /* 326 */ MNEM_VPMOVZXBW,
    /* 327 */ MNEM_VPMOVZXDQ,
    /* 328 */ MNEM_VPMOVZXWD,
    /* 329 */ MNEM_VPMOVZXWQ,
    /* 32A */ MNEM_VPMULDQ,
    /* 32B */ MNEM_VPMULHRSW,
    /* 32C */ MNEM_VPMULHUW,
    /* 32D */ MNEM_VPMULHW,
    /* 32E */ MNEM_VPMULLD,
    /* 32F */ MNEM_VPMULLW,
    /* 330 */ MNEM_VPOR,
    /* 331 */ MNEM_VPSADBW,
    /* 332 */ MNEM_VPSHUFB,
    /* 333 */ MNEM_VPSHUFD,
    /* 334 */ MNEM_VPSHUFHW,
    /* 335 */ MNEM_VPSHUFLW,
    /* 336 */ MNEM_VPSIGNB,
    /* 337 */ MNEM_VPSIGND,
    /* 338 */ MNEM_VPSIGNW,
    /* 339 */ MNEM_VPSLLD,
    /* 33A */ MNEM_VPSLLDQ,
    /* 33B */ MNEM_VPSLLQ,
    /* 33C */ MNEM_VPSLLW,
    /* 33D */ MNEM_VPSRAD,
    /* 33E */ MNEM_VPSRAW,
    /* 33F */ MNEM_VPSRLD,
    /* 340 */ MNEM_VPSRLDQ,
    /* 341 */ MNEM_VPSRLQ,
    /* 342 */ MNEM_VPSRLW,
    /* 343 */ MNEM_VPSUBB,
    /* 344 */ MNEM_VPSUBD,
    /* 345 */ MNEM_VPSUBQ,
    /* 346 */ MNEM_VPSUBSB,
    /* 347 */ MNEM_VPSUBSW,
    /* 348 */ MNEM_VPSUBUSB,
    /* 349 */ MNEM_VPSUBUSW,
    /* 34A */ MNEM_VPSUBW,
    /* 34B */ MNEM_VPTEST,
    /* 34C */ MNEM_VPUNPCKHBW,
    /* 34D */ MNEM_VPUNPCKHDQ,
    /* 34E */ MNEM_VPUNPCKHQDQ,
    /* 34F */ MNEM_VPUNPCKHWD,
    /* 350 */ MNEM_VPUNPCKLBW,
    /* 351 */ MNEM_VPUNPCKLDQ,
    /* 352 */ MNEM_VPUNPCKLQDQ,
    /* 353 */ MNEM_VPUNPCKLWD,
    /* 354 */ MNEM_VPXOR,
    /* 355 */ MNEM_VRCPPS,
    /* 356 */ MNEM_VRCPSS,
    /* 357 */ MNEM_VROUNDPD,
    /* 358 */ MNEM_VROUNDPS,
    /* 359 */ MNEM_VROUNDSD,
    /* 35A */ MNEM_VROUNDSS,
    /* 35B */ MNEM_VRSQRTPS,
    /* 35C */ MNEM_VRSQRTSS,
    /* 35D */ MNEM_VSHUFPD,
    /* 35E */ MNEM_VSHUFPS,
    /* 35F */ MNEM_VSQRTPD,
    /* 360 */ MNEM_VSQRTPS,
    /* 361 */ MNEM_VSQRTSD,
    /* 362 */ MNEM_VSQRTSS,
    /* 363 */ MNEM_VSTMXCSR,
    /* 364 */ MNEM_VSUBPD,
    /* 365 */ MNEM_VSUBPS,
    /* 366 */ MNEM_VSUBSD,
    /* 367 */ MNEM_VSUBSS,
    /* 368 */ MNEM_VTESTPD,
    /* 369 */ MNEM_VTESTPS,
    /* 36A */ MNEM_VUCOMISD,
    /* 36B */ MNEM_VUCOMISS,
    /* 36C */ MNEM_VUNPCKHPD,
    /* 36D */ MNEM_VUNPCKHPS,
    /* 36E */ MNEM_VUNPCKLPD,
    /* 36F */ MNEM_VUNPCKLPS,
    /* 370 */ MNEM_VXORPD,
    /* 371 */ MNEM_VXORPS,
    /* 372 */ MNEM_VZEROALL,
    /* 373 */ MNEM_VZEROUPPER,
    /* 374 */ MNEM_WAIT,
    /* 375 */ MNEM_WBINVD,
    /* 376 */ MNEM_WRMSR,
    /* 377 */ MNEM_XADD,
    /* 378 */ MNEM_XCHG,
    /* 379 */ MNEM_XCRYPTCBC,
    /* 37A */ MNEM_XCRYPTCFB,
    /* 37B */ MNEM_XCRYPTCTR,
    /* 37C */ MNEM_XCRYPTECB,
    /* 37D */ MNEM_XCRYPTOFB,
    /* 37E */ MNEM_XGETBV,
    /* 37F */ MNEM_XLATB,
    /* 380 */ MNEM_XOR,
    /* 381 */ MNEM_XORPD,
    /* 382 */ MNEM_XORPS,
    /* 383 */ MNEM_XRSTOR,
    /* 384 */ MNEM_XSAVE,
    /* 385 */ MNEM_XSETBV,
    /* 386 */ MNEM_XSHA1,
    /* 387 */ MNEM_XSHA256,
    /* 388 */ MNEM_XSTORE,

    MNEM_FORCE_WORD = 0x7FFF
} VXInstructionMnemonic;

/**
 * @brief   Defines an alias representing an opcode tree node. An opcode tree node is a 16 bit
 *          unsigned integer value with its first 4 bits reserved for the node type.
 */
typedef uint16_t VXOpcodeTreeNode;

/**
 * @brief   Values that represent the type of an opcode tree node.
 */
typedef enum _VXOpcodeTreeNodeType /* : uint8_t */
{
    /**
     * @brief   Reference to a concrete instruction definition.
     */
    OTNT_INSTRUCTION_DEFINITION  =  0,
    /**
     * @brief   Reference to an opcode table.
     */
    OTNT_TABLE                   =  1,
    /**
     * @brief   Reference to a modrm_mod switch table.
     */
    OTNT_MODRM_MOD               =  2,
    /**
     * @brief   Reference to a modrm_reg switch table.
     */                                                                                      
    OTNT_MODRM_REG               =  3,
    /**
     * @brief   Reference to a modrm_rm switch table.
     */
    OTNT_MODRM_RM                =  4,
    /**
     * @brief   Reference to a mandatory-prefix switch table.
     */
    OTNT_MANDATORY               =  5,
    /**
     * @brief   Reference to a x87 opcode table.
     */
    OTNT_X87                     =  6,
    /**
     * @brief   Reference to an address-size switch table.
     */
    OTNT_ADDRESS_SIZE            =  7,
    /**
     * @brief   Reference to an operand-size switch table.
     */
    OTNT_OPERAND_SIZE            =  8,
    /**
     * @brief   Reference to a cpu-mode switch table.
     */
    OTNT_MODE                    =  9,
    /**
     * @brief   Reference to a vendor switch table.
     */
    OTNT_VENDOR                  = 10,
    /**
     * @brief   Reference to a 3dnow! opcode table.
     */
    OTNT_AMD3DNOW                = 11,
    /**
     * @brief   Reference to a vex-prefix switch table.
     */
    OTNT_VEX                     = 12,
    /**
     * @brief   Reference to a vex_w switch table.
     */
    OTNT_VEXW                    = 13,
    /**
     * @brief   Reference to a vex_l switch table.
     */
    OTNT_VEXL                    = 14
} VXOpcodeTreeNodeType;

/**
 * @brief   Values that represent the type of an operand in the instruction definition.
 */
typedef enum _VXDefinedOperandType /* : uint8_t */
{
    /*
     * @brief   No operand. 
     */
    DOT_NONE,
    /*
     * @brief   Direct address. The instruction has no ModR/M byte; the address of the operand is 
     *          encoded in the instruction; no base register, index register, or scaling factor 
     *          can be applied. 
     */
    DOT_A,  
    /*
     * @brief   The reg field of the ModR/M byte selects a control register.
     */
    DOT_C,
    /*
     * @brief   The reg field of the ModR/M byte selects a debug register.
     */
    DOT_D,
    /*
     * @brief   A ModR/M byte follows the opcode and specifies the operand. The operand is either 
     *          a general-purpose register or a memory address. If it is a memory address, the 
     *          address is computed from a segment register and any of the following values: 
     *          a base register, an index register, a scaling factor, or a displacement.
     */
    DOT_E,  
    /*
     * @brief   rFLAGS register.
     */
    DOT_F,  
    /*
     * @brief   The reg field of the ModR/M byte selects a general register. 
     */
    DOT_G,
    /*
     * @brief   The r/m field of the ModR/M byte always selects a general register, regardless of 
     *          the mod field.
     */
    DOT_H,
    /*
     * @brief   Immediate data. The operand value is encoded in subsequent bytes of the 
     *          instruction. 
     */
    DOT_I,
    /*
     * @brief   Signed immediate data. The operand value is encoded in subsequent bytes of the 
     *          instruction. 
     */
    DOT_sI,
    /*
     * @brief   Constant immediate data value of 1. 
     */
    DOT_I1,
    /*
     * @brief   The instruction contains a relative offset to be added to the instruction pointer 
     *          register.
     */
    DOT_J,
    /*
     * @brief   Source operand is encoded in immediate byte (VEX only). 
     */
    DOT_L,
    /*
     * @brief   The ModR/M byte may refer only to memory: mod != 11bin. 
     */
    DOT_M, 
    /*
     * @brief   Combination of M and R.  
     */
    DOT_MR,
    /*
     * @brief   Combination of M and U. 
     */
    DOT_MU,
    /*
     * @brief   The R/M field of the ModR/M byte selects a packed quadword MMX technology register.
     */
    DOT_N, 
    /*
     * @brief   The instruction has no ModR/M byte; the offset of the operand is coded as a word, 
     *          double word or quad word (depending on address size attribute) in the instruction. 
     *          No base register, index register, or scaling factor can be applied.
     */
    DOT_O,
    /*
     * @brief   The reg field of the ModR/M byte selects a packed quadword MMX technology register.
     */
    DOT_P,
    /*
     * @brief   A ModR/M byte follows the opcode and specifies the operand. The operand is either 
     *          an MMX technology register or a memory address. If it is a memory address, the 
     *          address is computed from a segment register and any of the following values:
     *          a base register, an index register, a scaling factor, and a displacement.
     */
    DOT_Q, 
    /*
     * @brief   The mod field of the ModR/M byte may refer only to a general register.
     */
    DOT_R,  
    /*
     * @brief   The reg field of the ModR/M byte selects a segment register.
     */
    DOT_S, 
    /*
     * @brief   The R/M field of the ModR/M byte selects a 128-bit XMM register.
     */
    DOT_U,  
    /*
     * @brief   The reg field of the ModR/M byte selects a 128-bit XMM register.
     */
    DOT_V,   
    /*
     * @brief   A ModR/M byte follows the opcode and specifies the operand. The operand is either 
     *          a 128-bit XMM register or a memory address. If it is a memory address, the address 
     *          is computed from a segment register and any of the following values: 
     *          a base register, an index register, a scaling factor, and a displacement.
     */
    DOT_W, 
    /**
     * @brief   Register 0.
     */
    DOT_R0, 
    /**
     * @brief   Register 1.
     */
    DOT_R1, 
    /**
     * @brief   Register 2.
     */
    DOT_R2,    
    /**
     * @brief   Register 3.
     */
    DOT_R3, 
    /**
     * @brief   Register 4.
     */
    DOT_R4, 
    /**
     * @brief   Register 5.
     */
    DOT_R5, 
    /**
     * @brief   Register 6.
     */
    DOT_R6, 
    /**
     * @brief   Register 7.
     */
    DOT_R7,
    /**
     * @brief   AL register.
     */
    DOT_AL,  
    /**
     * @brief   CL register.
     */
    DOT_CL,  
    /**
     * @brief   DL register.
     */
    DOT_DL,
    /**
     * @brief   AX register.
     */
    DOT_AX,  
    /**
     * @brief   CX register.
     */
    DOT_CX,  
    /**
     * @brief   DX register.
     */
    DOT_DX,
    /**
     * @brief   EAX register.
     */
    DOT_EAX, 
    /**
     * @brief   ECX register.
     */
    DOT_ECX, 
    /**
     * @brief   EDX register.
     */
    DOT_EDX,
    /**
     * @brief   RAX register.
     */
    DOT_RAX, 
    /**
     * @brief   RCX register.
     */
    DOT_RCX, 
    /**
     * @brief   RDX register.
     */
    DOT_RDX,
    /**
     * @brief   ES segment register.
     */
    DOT_ES, 
    /**
     * @brief   CS segment register.
     */
    DOT_CS, 
    /**
     * @brief   SS segment register.
     */
    DOT_SS, 
    /**
     * @brief   DS segment register.
     */
    DOT_DS, 
    /**
     * @brief   FS segment register.
     */
    DOT_FS, 
    /**
     * @brief   GS segment register.
     */
    DOT_GS,
    /**
     * @brief   Floating point register 0.
     */
    DOT_ST0, 
    /**
     * @brief   Floating point register 1.
     */
    DOT_ST1, 
    /**
     * @brief   Floating point register 2.
     */
    DOT_ST2, 
    /**
     * @brief   Floating point register 3.
     */
    DOT_ST3, 
    /**
     * @brief   Floating point register 4.
     */
    DOT_ST4, 
    /**
     * @brief   Floating point register 5.
     */
    DOT_ST5, 
    /**
     * @brief   Floating point register 6.
     */
    DOT_ST6, 
    /**
     * @brief   Floating point register 7.
     */
    DOT_ST7
} VXDefinedOperandType;

/**
 * @brief   Values that represent the size of an operand in the instruction definition.
 *          Do not change the order or the values of this enum! 
 */
typedef enum _VXDefinedOperandSize /* : uint8_t */
{
    /**
     * @brief   No operand.
     */
    DOS_NA  = 0,
    /**
     * @brief   Word, dword or qword.
     */
    DOS_Z,
    /**
     * @brief   Word, dword or qword.
     */
    DOS_V,
    /**
     * @brief   Dword or qword.
     */
    DOS_Y,
    /**
     * @brief   Oword or yword.
     */
    DOS_X,
    /**
     * @brief   Dword or qword, depending on the disassembler mode.
     */
    DOS_RDQ,
    /*
     * @brief   Byte, regardless of operand-size attribute.
     */
    DOS_B,
    /*
     * @brief   Word, regardless of operand-size attribute.
     */
    DOS_W,
    /*
     * @brief   Doubleword, regardless of operand-size attribute.
     */
    DOS_D,
    /*
     * @brief   Quadword, regardless of operand-size attribute.
     */
    DOS_Q,
    /*
     * @brief   10-byte far pointer.
     */
    DOS_T,
    /**
     * @brief   TODO:
     */
    DOS_O,
    /*
     * @brief   Double-quadword, regardless of operand-size attribute.
     */
    DOS_DQ, 
    /*
     * @brief   Quad-quadword, regardless of operand-size attribute.
     */
    DOS_QQ,
    /**
     * @brief   B sized register or D sized memory operand.
     */
    DOS_BD  = (uint8_t(DOS_B) << 4) | uint8_t(DOS_D),
    /**
     * @brief   B sized register or V sized memory operand.
     */
    DOS_BV  = (uint8_t(DOS_B) << 4) | uint8_t(DOS_V),
    /**
     * @brief   W sized register or D sized memory operand.
     */
    DOS_WD  = (uint8_t(DOS_W) << 4) | uint8_t(DOS_D),
    /**
     * @brief   W sized register or V sized memory operand.
     */
    DOS_WV  = (uint8_t(DOS_W) << 4) | uint8_t(DOS_V),
    /**
     * @brief   W sized register or Y sized memory operand.
     */
    DOS_WY  = (uint8_t(DOS_W) << 4) | uint8_t(DOS_Y),
    /**
     * @brief   D sized register or Y sized memory operand.
     */
    DOS_DY  = (uint8_t(DOS_D) << 4) | uint8_t(DOS_Y),
    /**
     * @brief   W sized register or O sized memory operand.
     */
    DOS_WO  = (uint8_t(DOS_W) << 4) | uint8_t(DOS_O),
    /**
     * @brief   D sized register or O sized memory operand.
     */
    DOS_DO  = (uint8_t(DOS_D) << 4) | uint8_t(DOS_O),
    /**
     * @brief   Q sized register or O sized memory operand.
     */
    DOS_QO  = (uint8_t(DOS_Q) << 4) | uint8_t(DOS_O),
} VXDefinedOperandSize;

/**
 * @brief   Values that represent optional flags in the instruction definition.   
 *          Do not change the order or the values of this enum!            
 */
typedef enum _VXInstructionDefinitionFlags /* : uint16_t */
{
    /**
     * @brief   The instruction accepts the rex.b prefix value.
     */
    IDF_ACCEPTS_REXB                    = 0x0001,
    /**
     * @brief   The instruction accepts the rex.x prefix value.
     */
    IDF_ACCEPTS_REXX                    = 0x0002,
    /**
     * @brief   The instruction accepts the rex.r prefix value.
     */
    IDF_ACCEPTS_REXR                    = 0x0004,
    /**
     * @brief   The instruction accepts the rex.w prefix value.
     */
    IDF_ACCEPTS_REXW                    = 0x0008,
    /**
     * @brief   The instruction accepts the address size override prefix (0x67).
     */
    IDF_ACCEPTS_ADDRESS_SIZE_PREFIX     = 0x0010,
    /**
     * @brief   The instruction accepts the operand size override prefix (0x66).
     */
    IDF_ACCEPTS_OPERAND_SIZE_PREFIX     = 0x0020,
    /**
     * @brief   The instruction accepts the segment override prefix.
     */
    IDF_ACCEPTS_SEGMENT_PREFIX          = 0x0040,
    /**
     * @brief   The instruction accepts the REP prefix.
     */
    IDF_ACCEPTS_REP_PREFIX              = 0x0080,
    /**
     * @brief   The instruction accepts the vex.l prefix value.
     */
    IDF_ACCEPTS_VEXL                    = 0x0100,
    /**
     * @brief   The instruction is invalid in 64 bit mode.
     */
    IDF_INVALID_64                      = 0x0200,
    /**
     * @brief   The instructions operand size defaults to quadword in 64 bit mode.
     */
    IDF_DEFAULT_64                      = 0x0400,
    /**
     * @brief   The first operand of the instruction is accessed in write mode.
     */
    IDF_OPERAND1_WRITE                  = 0x0800,
    /**
     * @brief   The first operand of the instruction is accessed in read-write mode.
     */
    IDF_OPERAND1_READWRITE              = 0x1000,
    /**
     * @brief   The second operand of the instruction is accessed in write mode.
     */
    IDF_OPERAND2_WRITE                  = 0x2000,
    /**
     * @brief   The second operand of the instruction is accessed in read-write mode.
     */
    IDF_OPERAND2_READWRITE              = 0x4000,

    IDF_FORCE_WORD                      = 0x7FFF
} VXInstructionDefinitionFlags;

#pragma pack (push, 1)
/**
 * @brief   An operand definition.
 */
typedef struct _VXOperandDefinition
{               
    /**
     * @brief   The defined operand type.
     * @see     VXDefinedOperandType
     */
    uint8_t type;
    /**
     * @brief   The defined operand size.
     * @see     VXDefinedOperandType
     */
    uint8_t size;
} VXOperandDefinition;

/**
 * @brief   An instruction definition.
 */
typedef struct _VXInstructionDefinition
{
    /**
     * @brief   The instruction mnemonic.
     * @see     VXInstructionMnemonic
     */
    uint16_t mnemonic;
    /**
     * @brief   The operand definitions for all four possible operands.
     */
    VXOperandDefinition operand[4];
    /**
     * @brief   Additional flags for the instruction definition.
     */
    uint16_t flags;   
} VXInstructionDefinition;
#pragma pack (pop)

#ifdef __cplusplus
}
#endif

#endif // _VDE_VXOPCODETABLEC_H_