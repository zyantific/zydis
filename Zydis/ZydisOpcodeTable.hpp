/***************************************************************************************************

  Zyan Disassembler Engine
  Version 1.0

  Remarks         : Freeware, Copyright must be included

  Original Author : Florian Bernd
  Modifications   : Joel Höner

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
 * @brief The opcode table definition, mostly internal stuff.
 */

#ifndef _ZYDIS_OPCODETABLE_HPP_
#define _ZYDIS_OPCODETABLE_HPP_

#include <stdint.h>
#include <cassert>

#ifdef IN
#undef IN
#endif

#ifdef OUT
#undef OUT
#endif

namespace Zydis
{

/**
 * @brief   Values that represent an instruction mnemonic.
 */
enum class InstructionMnemonic : uint16_t
{
    /* 000 */ INVALID,
    /* 001 */ AAA,
    /* 002 */ AAD,
    /* 003 */ AAM,
    /* 004 */ AAS,
    /* 005 */ ADC,
    /* 006 */ ADD,
    /* 007 */ ADDPD,
    /* 008 */ ADDPS,
    /* 009 */ ADDSD,
    /* 00A */ ADDSS,
    /* 00B */ ADDSUBPD,
    /* 00C */ ADDSUBPS,
    /* 00D */ AESDEC,
    /* 00E */ AESDECLAST,
    /* 00F */ AESENC,
    /* 010 */ AESENCLAST,
    /* 011 */ AESIMC,
    /* 012 */ AESKEYGENASSIST,
    /* 013 */ AND,
    /* 014 */ ANDNPD,
    /* 015 */ ANDNPS,
    /* 016 */ ANDPD,
    /* 017 */ ANDPS,
    /* 018 */ ARPL,
    /* 019 */ BLENDPD,
    /* 01A */ BLENDPS,
    /* 01B */ BLENDVPD,
    /* 01C */ BLENDVPS,
    /* 01D */ BOUND,
    /* 01E */ BSF,
    /* 01F */ BSR,
    /* 020 */ BSWAP,
    /* 021 */ BT,
    /* 022 */ BTC,
    /* 023 */ BTR,
    /* 024 */ BTS,
    /* 025 */ CALL,
    /* 026 */ CBW,
    /* 027 */ CDQ,
    /* 028 */ CDQE,
    /* 029 */ CLC,
    /* 02A */ CLD,
    /* 02B */ CLFLUSH,
    /* 02C */ CLGI,
    /* 02D */ CLI,
    /* 02E */ CLTS,
    /* 02F */ CMC,
    /* 030 */ CMOVA,
    /* 031 */ CMOVAE,
    /* 032 */ CMOVB,
    /* 033 */ CMOVBE,
    /* 034 */ CMOVE,
    /* 035 */ CMOVG,
    /* 036 */ CMOVGE,
    /* 037 */ CMOVL,
    /* 038 */ CMOVLE,
    /* 039 */ CMOVNE,
    /* 03A */ CMOVNO,
    /* 03B */ CMOVNP,
    /* 03C */ CMOVNS,
    /* 03D */ CMOVO,
    /* 03E */ CMOVP,
    /* 03F */ CMOVS,
    /* 040 */ CMP,
    /* 041 */ CMPPD,
    /* 042 */ CMPPS,
    /* 043 */ CMPSB,
    /* 044 */ CMPSD,
    /* 045 */ CMPSQ,
    /* 046 */ CMPSS,
    /* 047 */ CMPSW,
    /* 048 */ CMPXCHG,
    /* 049 */ CMPXCHG16B,
    /* 04A */ CMPXCHG8B,
    /* 04B */ COMISD,
    /* 04C */ COMISS,
    /* 04D */ CPUID,
    /* 04E */ CQO,
    /* 04F */ CRC32,
    /* 050 */ CVTDQ2PD,
    /* 051 */ CVTDQ2PS,
    /* 052 */ CVTPD2DQ,
    /* 053 */ CVTPD2PI,
    /* 054 */ CVTPD2PS,
    /* 055 */ CVTPI2PD,
    /* 056 */ CVTPI2PS,
    /* 057 */ CVTPS2DQ,
    /* 058 */ CVTPS2PD,
    /* 059 */ CVTPS2PI,
    /* 05A */ CVTSD2SI,
    /* 05B */ CVTSD2SS,
    /* 05C */ CVTSI2SD,
    /* 05D */ CVTSI2SS,
    /* 05E */ CVTSS2SD,
    /* 05F */ CVTSS2SI,
    /* 060 */ CVTTPD2DQ,
    /* 061 */ CVTTPD2PI,
    /* 062 */ CVTTPS2DQ,
    /* 063 */ CVTTPS2PI,
    /* 064 */ CVTTSD2SI,
    /* 065 */ CVTTSS2SI,
    /* 066 */ CWD,
    /* 067 */ CWDE,
    /* 068 */ DAA,
    /* 069 */ DAS,
    /* 06A */ DEC,
    /* 06B */ DIV,
    /* 06C */ DIVPD,
    /* 06D */ DIVPS,
    /* 06E */ DIVSD,
    /* 06F */ DIVSS,
    /* 070 */ DPPD,
    /* 071 */ DPPS,
    /* 072 */ EMMS,
    /* 073 */ ENTER,
    /* 074 */ EXTRACTPS,
    /* 075 */ F2XM1,
    /* 076 */ FABS,
    /* 077 */ FADD,
    /* 078 */ FADDP,
    /* 079 */ FBLD,
    /* 07A */ FBSTP,
    /* 07B */ FCHS,
    /* 07C */ FCLEX,
    /* 07D */ FCMOVB,
    /* 07E */ FCMOVBE,
    /* 07F */ FCMOVE,
    /* 080 */ FCMOVNB,
    /* 081 */ FCMOVNBE,
    /* 082 */ FCMOVNE,
    /* 083 */ FCMOVNU,
    /* 084 */ FCMOVU,
    /* 085 */ FCOM,
    /* 086 */ FCOM2,
    /* 087 */ FCOMI,
    /* 088 */ FCOMIP,
    /* 089 */ FCOMP,
    /* 08A */ FCOMP3,
    /* 08B */ FCOMP5,
    /* 08C */ FCOMPP,
    /* 08D */ FCOS,
    /* 08E */ FDECSTP,
    /* 08F */ FDIV,
    /* 090 */ FDIVP,
    /* 091 */ FDIVR,
    /* 092 */ FDIVRP,
    /* 093 */ FEMMS,
    /* 094 */ FFREE,
    /* 095 */ FFREEP,
    /* 096 */ FIADD,
    /* 097 */ FICOM,
    /* 098 */ FICOMP,
    /* 099 */ FIDIV,
    /* 09A */ FIDIVR,
    /* 09B */ FILD,
    /* 09C */ FIMUL,
    /* 09D */ FINCSTP,
    /* 09E */ FIST,
    /* 09F */ FISTP,
    /* 0A0 */ FISTTP,
    /* 0A1 */ FISUB,
    /* 0A2 */ FISUBR,
    /* 0A3 */ FLD,
    /* 0A4 */ FLD1,
    /* 0A5 */ FLDCW,
    /* 0A6 */ FLDENV,
    /* 0A7 */ FLDL2E,
    /* 0A8 */ FLDL2T,
    /* 0A9 */ FLDLG2,
    /* 0AA */ FLDLN2,
    /* 0AB */ FLDPI,
    /* 0AC */ FLDZ,
    /* 0AD */ FMUL,
    /* 0AE */ FMULP,
    /* 0AF */ FNDISI,
    /* 0B0 */ FNENI,
    /* 0B1 */ FNINIT,
    /* 0B2 */ FNOP,
    /* 0B3 */ FNSAVE,
    /* 0B4 */ FNSETPM,
    /* 0B5 */ FNSTCW,
    /* 0B6 */ FNSTENV,
    /* 0B7 */ FNSTSW,
    /* 0B8 */ FPATAN,
    /* 0B9 */ FPREM,
    /* 0BA */ FPREM1,
    /* 0BB */ FPTAN,
    /* 0BC */ FRNDINT,
    /* 0BD */ FRSTOR,
    /* 0BE */ FRSTPM,
    /* 0BF */ FSCALE,
    /* 0C0 */ FSIN,
    /* 0C1 */ FSINCOS,
    /* 0C2 */ FSQRT,
    /* 0C3 */ FST,
    /* 0C4 */ FSTP,
    /* 0C5 */ FSTP1,
    /* 0C6 */ FSTP8,
    /* 0C7 */ FSTP9,
    /* 0C8 */ FSUB,
    /* 0C9 */ FSUBP,
    /* 0CA */ FSUBR,
    /* 0CB */ FSUBRP,
    /* 0CC */ FTST,
    /* 0CD */ FUCOM,
    /* 0CE */ FUCOMI,
    /* 0CF */ FUCOMIP,
    /* 0D0 */ FUCOMP,
    /* 0D1 */ FUCOMPP,
    /* 0D2 */ FXAM,
    /* 0D3 */ FXCH,
    /* 0D4 */ FXCH4,
    /* 0D5 */ FXCH7,
    /* 0D6 */ FXRSTOR,
    /* 0D7 */ FXSAVE,
    /* 0D8 */ FXTRACT,
    /* 0D9 */ FYL2X,
    /* 0DA */ FYL2XP1,
    /* 0DB */ GETSEC,
    /* 0DC */ HADDPD,
    /* 0DD */ HADDPS,
    /* 0DE */ HLT,
    /* 0DF */ HSUBPD,
    /* 0E0 */ HSUBPS,
    /* 0E1 */ IDIV,
    /* 0E2 */ IMUL,
    /* 0E3 */ IN,
    /* 0E4 */ INC,
    /* 0E5 */ INSB,
    /* 0E6 */ INSD,
    /* 0E7 */ INSERTPS,
    /* 0E8 */ INSW,
    /* 0E9 */ INT,
    /* 0EA */ INT1,
    /* 0EB */ INT3,
    /* 0EC */ INTO,
    /* 0ED */ INVD,
    /* 0EE */ INVEPT,
    /* 0EF */ INVLPG,
    /* 0F0 */ INVLPGA,
    /* 0F1 */ INVVPID,
    /* 0F2 */ IRETD,
    /* 0F3 */ IRETQ,
    /* 0F4 */ IRETW,
    /* 0F5 */ JA,
    /* 0F6 */ JB,
    /* 0F7 */ JBE,
    /* 0F8 */ JCXZ,
    /* 0F9 */ JE,
    /* 0FA */ JECXZ,
    /* 0FB */ JG,
    /* 0FC */ JGE,
    /* 0FD */ JL,
    /* 0FE */ JLE,
    /* 0FF */ JMP,
    /* 100 */ JNB,
    /* 101 */ JNE,
    /* 102 */ JNO,
    /* 103 */ JNP,
    /* 104 */ JNS,
    /* 105 */ JO,
    /* 106 */ JP,
    /* 107 */ JRCXZ,
    /* 108 */ JS,
    /* 109 */ LAHF,
    /* 10A */ LAR,
    /* 10B */ LDDQU,
    /* 10C */ LDMXCSR,
    /* 10D */ LDS,
    /* 10E */ LEA,
    /* 10F */ LEAVE,
    /* 110 */ LES,
    /* 111 */ LFENCE,
    /* 112 */ LFS,
    /* 113 */ LGDT,
    /* 114 */ LGS,
    /* 115 */ LIDT,
    /* 116 */ LLDT,
    /* 117 */ LMSW,
    /* 118 */ LOCK,
    /* 119 */ LODSB,
    /* 11A */ LODSD,
    /* 11B */ LODSQ,
    /* 11C */ LODSW,
    /* 11D */ LOOP,
    /* 11E */ LOOPE,
    /* 11F */ LOOPNE,
    /* 120 */ LSL,
    /* 121 */ LSS,
    /* 122 */ LTR,
    /* 123 */ MASKMOVDQU,
    /* 124 */ MASKMOVQ,
    /* 125 */ MAXPD,
    /* 126 */ MAXPS,
    /* 127 */ MAXSD,
    /* 128 */ MAXSS,
    /* 129 */ MFENCE,
    /* 12A */ MINPD,
    /* 12B */ MINPS,
    /* 12C */ MINSD,
    /* 12D */ MINSS,
    /* 12E */ MONITOR,
    /* 12F */ MONTMUL,
    /* 130 */ MOV,
    /* 131 */ MOVAPD,
    /* 132 */ MOVAPS,
    /* 133 */ MOVBE,
    /* 134 */ MOVD,
    /* 135 */ MOVDDUP,
    /* 136 */ MOVDQ2Q,
    /* 137 */ MOVDQA,
    /* 138 */ MOVDQU,
    /* 139 */ MOVHLPS,
    /* 13A */ MOVHPD,
    /* 13B */ MOVHPS,
    /* 13C */ MOVLHPS,
    /* 13D */ MOVLPD,
    /* 13E */ MOVLPS,
    /* 13F */ MOVMSKPD,
    /* 140 */ MOVMSKPS,
    /* 141 */ MOVNTDQ,
    /* 142 */ MOVNTDQA,
    /* 143 */ MOVNTI,
    /* 144 */ MOVNTPD,
    /* 145 */ MOVNTPS,
    /* 146 */ MOVNTQ,
    /* 147 */ MOVQ,
    /* 148 */ MOVQ2DQ,
    /* 149 */ MOVSB,
    /* 14A */ MOVSD,
    /* 14B */ MOVSHDUP,
    /* 14C */ MOVSLDUP,
    /* 14D */ MOVSQ,
    /* 14E */ MOVSS,
    /* 14F */ MOVSW,
    /* 150 */ MOVSX,
    /* 151 */ MOVSXD,
    /* 152 */ MOVUPD,
    /* 153 */ MOVUPS,
    /* 154 */ MOVZX,
    /* 155 */ MPSADBW,
    /* 156 */ MUL,
    /* 157 */ MULPD,
    /* 158 */ MULPS,
    /* 159 */ MULSD,
    /* 15A */ MULSS,
    /* 15B */ MWAIT,
    /* 15C */ NEG,
    /* 15D */ NOP,
    /* 15E */ NOT,
    /* 15F */ OR,
    /* 160 */ ORPD,
    /* 161 */ ORPS,
    /* 162 */ OUT,
    /* 163 */ OUTSB,
    /* 164 */ OUTSD,
    /* 165 */ OUTSW,
    /* 166 */ PABSB,
    /* 167 */ PABSD,
    /* 168 */ PABSW,
    /* 169 */ PACKSSDW,
    /* 16A */ PACKSSWB,
    /* 16B */ PACKUSDW,
    /* 16C */ PACKUSWB,
    /* 16D */ PADDB,
    /* 16E */ PADDD,
    /* 16F */ PADDQ,
    /* 170 */ PADDSB,
    /* 171 */ PADDSW,
    /* 172 */ PADDUSB,
    /* 173 */ PADDUSW,
    /* 174 */ PADDW,
    /* 175 */ PALIGNR,
    /* 176 */ PAND,
    /* 177 */ PANDN,
    /* 178 */ PAUSE,
    /* 179 */ PAVGB,
    /* 17A */ PAVGUSB,
    /* 17B */ PAVGW,
    /* 17C */ PBLENDVB,
    /* 17D */ PBLENDW,
    /* 17E */ PCLMULQDQ,
    /* 17F */ PCMPEQB,
    /* 180 */ PCMPEQD,
    /* 181 */ PCMPEQQ,
    /* 182 */ PCMPEQW,
    /* 183 */ PCMPESTRI,
    /* 184 */ PCMPESTRM,
    /* 185 */ PCMPGTB,
    /* 186 */ PCMPGTD,
    /* 187 */ PCMPGTQ,
    /* 188 */ PCMPGTW,
    /* 189 */ PCMPISTRI,
    /* 18A */ PCMPISTRM,
    /* 18B */ PEXTRB,
    /* 18C */ PEXTRD,
    /* 18D */ PEXTRQ,
    /* 18E */ PEXTRW,
    /* 18F */ PF2ID,
    /* 190 */ PF2IW,
    /* 191 */ PFACC,
    /* 192 */ PFADD,
    /* 193 */ PFCMPEQ,
    /* 194 */ PFCMPGE,
    /* 195 */ PFCMPGT,
    /* 196 */ PFMAX,
    /* 197 */ PFMIN,
    /* 198 */ PFMUL,
    /* 199 */ PFNACC,
    /* 19A */ PFPNACC,
    /* 19B */ PFRCP,
    /* 19C */ PFRCPIT1,
    /* 19D */ PFRCPIT2,
    /* 19E */ PFRSQIT1,
    /* 19F */ PFRSQRT,
    /* 1A0 */ PFSUB,
    /* 1A1 */ PFSUBR,
    /* 1A2 */ PHADDD,
    /* 1A3 */ PHADDSW,
    /* 1A4 */ PHADDW,
    /* 1A5 */ PHMINPOSUW,
    /* 1A6 */ PHSUBD,
    /* 1A7 */ PHSUBSW,
    /* 1A8 */ PHSUBW,
    /* 1A9 */ PI2FD,
    /* 1AA */ PI2FW,
    /* 1AB */ PINSRB,
    /* 1AC */ PINSRD,
    /* 1AD */ PINSRQ,
    /* 1AE */ PINSRW,
    /* 1AF */ PMADDUBSW,
    /* 1B0 */ PMADDWD,
    /* 1B1 */ PMAXSB,
    /* 1B2 */ PMAXSD,
    /* 1B3 */ PMAXSW,
    /* 1B4 */ PMAXUB,
    /* 1B5 */ PMAXUD,
    /* 1B6 */ PMAXUW,
    /* 1B7 */ PMINSB,
    /* 1B8 */ PMINSD,
    /* 1B9 */ PMINSW,
    /* 1BA */ PMINUB,
    /* 1BB */ PMINUD,
    /* 1BC */ PMINUW,
    /* 1BD */ PMOVMSKB,
    /* 1BE */ PMOVSXBD,
    /* 1BF */ PMOVSXBQ,
    /* 1C0 */ PMOVSXBW,
    /* 1C1 */ PMOVSXDQ,
    /* 1C2 */ PMOVSXWD,
    /* 1C3 */ PMOVSXWQ,
    /* 1C4 */ PMOVZXBD,
    /* 1C5 */ PMOVZXBQ,
    /* 1C6 */ PMOVZXBW,
    /* 1C7 */ PMOVZXDQ,
    /* 1C8 */ PMOVZXWD,
    /* 1C9 */ PMOVZXWQ,
    /* 1CA */ PMULDQ,
    /* 1CB */ PMULHRSW,
    /* 1CC */ PMULHRW,
    /* 1CD */ PMULHUW,
    /* 1CE */ PMULHW,
    /* 1CF */ PMULLD,
    /* 1D0 */ PMULLW,
    /* 1D1 */ PMULUDQ,
    /* 1D2 */ POP,
    /* 1D3 */ POPA,
    /* 1D4 */ POPAD,
    /* 1D5 */ POPCNT,
    /* 1D6 */ POPFD,
    /* 1D7 */ POPFQ,
    /* 1D8 */ POPFW,
    /* 1D9 */ POR,
    /* 1DA */ PREFETCH,
    /* 1DB */ PREFETCHNTA,
    /* 1DC */ PREFETCHT0,
    /* 1DD */ PREFETCHT1,
    /* 1DE */ PREFETCHT2,
    /* 1DF */ PSADBW,
    /* 1E0 */ PSHUFB,
    /* 1E1 */ PSHUFD,
    /* 1E2 */ PSHUFHW,
    /* 1E3 */ PSHUFLW,
    /* 1E4 */ PSHUFW,
    /* 1E5 */ PSIGNB,
    /* 1E6 */ PSIGND,
    /* 1E7 */ PSIGNW,
    /* 1E8 */ PSLLD,
    /* 1E9 */ PSLLDQ,
    /* 1EA */ PSLLQ,
    /* 1EB */ PSLLW,
    /* 1EC */ PSRAD,
    /* 1ED */ PSRAW,
    /* 1EE */ PSRLD,
    /* 1EF */ PSRLDQ,
    /* 1F0 */ PSRLQ,
    /* 1F1 */ PSRLW,
    /* 1F2 */ PSUBB,
    /* 1F3 */ PSUBD,
    /* 1F4 */ PSUBQ,
    /* 1F5 */ PSUBSB,
    /* 1F6 */ PSUBSW,
    /* 1F7 */ PSUBUSB,
    /* 1F8 */ PSUBUSW,
    /* 1F9 */ PSUBW,
    /* 1FA */ PSWAPD,
    /* 1FB */ PTEST,
    /* 1FC */ PUNPCKHBW,
    /* 1FD */ PUNPCKHDQ,
    /* 1FE */ PUNPCKHQDQ,
    /* 1FF */ PUNPCKHWD,
    /* 200 */ PUNPCKLBW,
    /* 201 */ PUNPCKLDQ,
    /* 202 */ PUNPCKLQDQ,
    /* 203 */ PUNPCKLWD,
    /* 204 */ PUSH,
    /* 205 */ PUSHA,
    /* 206 */ PUSHAD,
    /* 207 */ PUSHFD,
    /* 208 */ PUSHFQ,
    /* 209 */ PUSHFW,
    /* 20A */ PXOR,
    /* 20B */ RCL,
    /* 20C */ RCPPS,
    /* 20D */ RCPSS,
    /* 20E */ RCR,
    /* 20F */ RDMSR,
    /* 210 */ RDPMC,
    /* 211 */ RDRAND,
    /* 212 */ RDTSC,
    /* 213 */ RDTSCP,
    /* 214 */ REP,
    /* 215 */ REPNE,
    /* 216 */ RET,
    /* 217 */ RETF,
    /* 218 */ ROL,
    /* 219 */ ROR,
    /* 21A */ ROUNDPD,
    /* 21B */ ROUNDPS,
    /* 21C */ ROUNDSD,
    /* 21D */ ROUNDSS,
    /* 21E */ RSM,
    /* 21F */ RSQRTPS,
    /* 220 */ RSQRTSS,
    /* 221 */ SAHF,
    /* 222 */ SALC,
    /* 223 */ SAR,
    /* 224 */ SBB,
    /* 225 */ SCASB,
    /* 226 */ SCASD,
    /* 227 */ SCASQ,
    /* 228 */ SCASW,
    /* 229 */ SETA,
    /* 22A */ SETAE,
    /* 22B */ SETB,
    /* 22C */ SETBE,
    /* 22D */ SETE,
    /* 22E */ SETG,
    /* 22F */ SETGE,
    /* 230 */ SETL,
    /* 231 */ SETLE,
    /* 232 */ SETNE,
    /* 233 */ SETNO,
    /* 234 */ SETNP,
    /* 235 */ SETNS,
    /* 236 */ SETO,
    /* 237 */ SETP,
    /* 238 */ SETS,
    /* 239 */ SFENCE,
    /* 23A */ SGDT,
    /* 23B */ SHL,
    /* 23C */ SHLD,
    /* 23D */ SHR,
    /* 23E */ SHRD,
    /* 23F */ SHUFPD,
    /* 240 */ SHUFPS,
    /* 241 */ SIDT,
    /* 242 */ SKINIT,
    /* 243 */ SLDT,
    /* 244 */ SMSW,
    /* 245 */ SQRTPD,
    /* 246 */ SQRTPS,
    /* 247 */ SQRTSD,
    /* 248 */ SQRTSS,
    /* 249 */ STC,
    /* 24A */ STD,
    /* 24B */ STGI,
    /* 24C */ STI,
    /* 24D */ STMXCSR,
    /* 24E */ STOSB,
    /* 24F */ STOSD,
    /* 250 */ STOSQ,
    /* 251 */ STOSW,
    /* 252 */ STR,
    /* 253 */ SUB,
    /* 254 */ SUBPD,
    /* 255 */ SUBPS,
    /* 256 */ SUBSD,
    /* 257 */ SUBSS,
    /* 258 */ SWAPGS,
    /* 259 */ SYSCALL,
    /* 25A */ SYSENTER,
    /* 25B */ SYSEXIT,
    /* 25C */ SYSRET,
    /* 25D */ TEST,
    /* 25E */ UCOMISD,
    /* 25F */ UCOMISS,
    /* 260 */ UD2,
    /* 261 */ UNPCKHPD,
    /* 262 */ UNPCKHPS,
    /* 263 */ UNPCKLPD,
    /* 264 */ UNPCKLPS,
    /* 265 */ VADDPD,
    /* 266 */ VADDPS,
    /* 267 */ VADDSD,
    /* 268 */ VADDSS,
    /* 269 */ VADDSUBPD,
    /* 26A */ VADDSUBPS,
    /* 26B */ VAESDEC,
    /* 26C */ VAESDECLAST,
    /* 26D */ VAESENC,
    /* 26E */ VAESENCLAST,
    /* 26F */ VAESIMC,
    /* 270 */ VAESKEYGENASSIST,
    /* 271 */ VANDNPD,
    /* 272 */ VANDNPS,
    /* 273 */ VANDPD,
    /* 274 */ VANDPS,
    /* 275 */ VBLENDPD,
    /* 276 */ VBLENDPS,
    /* 277 */ VBLENDVPD,
    /* 278 */ VBLENDVPS,
    /* 279 */ VBROADCASTSD,
    /* 27A */ VBROADCASTSS,
    /* 27B */ VCMPPD,
    /* 27C */ VCMPPS,
    /* 27D */ VCMPSD,
    /* 27E */ VCMPSS,
    /* 27F */ VCOMISD,
    /* 280 */ VCOMISS,
    /* 281 */ VCVTDQ2PD,
    /* 282 */ VCVTDQ2PS,
    /* 283 */ VCVTPD2DQ,
    /* 284 */ VCVTPD2PS,
    /* 285 */ VCVTPS2DQ,
    /* 286 */ VCVTPS2PD,
    /* 287 */ VCVTSD2SI,
    /* 288 */ VCVTSD2SS,
    /* 289 */ VCVTSI2SD,
    /* 28A */ VCVTSI2SS,
    /* 28B */ VCVTSS2SD,
    /* 28C */ VCVTSS2SI,
    /* 28D */ VCVTTPD2DQ,
    /* 28E */ VCVTTPS2DQ,
    /* 28F */ VCVTTSD2SI,
    /* 290 */ VCVTTSS2SI,
    /* 291 */ VDIVPD,
    /* 292 */ VDIVPS,
    /* 293 */ VDIVSD,
    /* 294 */ VDIVSS,
    /* 295 */ VDPPD,
    /* 296 */ VDPPS,
    /* 297 */ VERR,
    /* 298 */ VERW,
    /* 299 */ VEXTRACTF128,
    /* 29A */ VEXTRACTPS,
    /* 29B */ VHADDPD,
    /* 29C */ VHADDPS,
    /* 29D */ VHSUBPD,
    /* 29E */ VHSUBPS,
    /* 29F */ VINSERTF128,
    /* 2A0 */ VINSERTPS,
    /* 2A1 */ VLDDQU,
    /* 2A2 */ VMASKMOVDQU,
    /* 2A3 */ VMASKMOVPD,
    /* 2A4 */ VMASKMOVPS,
    /* 2A5 */ VMAXPD,
    /* 2A6 */ VMAXPS,
    /* 2A7 */ VMAXSD,
    /* 2A8 */ VMAXSS,
    /* 2A9 */ VMCALL,
    /* 2AA */ VMCLEAR,
    /* 2AB */ VMINPD,
    /* 2AC */ VMINPS,
    /* 2AD */ VMINSD,
    /* 2AE */ VMINSS,
    /* 2AF */ VMLAUNCH,
    /* 2B0 */ VMLOAD,
    /* 2B1 */ VMMCALL,
    /* 2B2 */ VMOVAPD,
    /* 2B3 */ VMOVAPS,
    /* 2B4 */ VMOVD,
    /* 2B5 */ VMOVDDUP,
    /* 2B6 */ VMOVDQA,
    /* 2B7 */ VMOVDQU,
    /* 2B8 */ VMOVHLPS,
    /* 2B9 */ VMOVHPD,
    /* 2BA */ VMOVHPS,
    /* 2BB */ VMOVLHPS,
    /* 2BC */ VMOVLPD,
    /* 2BD */ VMOVLPS,
    /* 2BE */ VMOVMSKPD,
    /* 2BF */ VMOVMSKPS,
    /* 2C0 */ VMOVNTDQ,
    /* 2C1 */ VMOVNTDQA,
    /* 2C2 */ VMOVNTPD,
    /* 2C3 */ VMOVNTPS,
    /* 2C4 */ VMOVQ,
    /* 2C5 */ VMOVSD,
    /* 2C6 */ VMOVSHDUP,
    /* 2C7 */ VMOVSLDUP,
    /* 2C8 */ VMOVSS,
    /* 2C9 */ VMOVUPD,
    /* 2CA */ VMOVUPS,
    /* 2CB */ VMPSADBW,
    /* 2CC */ VMPTRLD,
    /* 2CD */ VMPTRST,
    /* 2CE */ VMREAD,
    /* 2CF */ VMRESUME,
    /* 2D0 */ VMRUN,
    /* 2D1 */ VMSAVE,
    /* 2D2 */ VMULPD,
    /* 2D3 */ VMULPS,
    /* 2D4 */ VMULSD,
    /* 2D5 */ VMULSS,
    /* 2D6 */ VMWRITE,
    /* 2D7 */ VMXOFF,
    /* 2D8 */ VMXON,
    /* 2D9 */ VORPD,
    /* 2DA */ VORPS,
    /* 2DB */ VPABSB,
    /* 2DC */ VPABSD,
    /* 2DD */ VPABSW,
    /* 2DE */ VPACKSSDW,
    /* 2DF */ VPACKSSWB,
    /* 2E0 */ VPACKUSDW,
    /* 2E1 */ VPACKUSWB,
    /* 2E2 */ VPADDB,
    /* 2E3 */ VPADDD,
    /* 2E4 */ VPADDQ,
    /* 2E5 */ VPADDSB,
    /* 2E6 */ VPADDSW,
    /* 2E7 */ VPADDUSB,
    /* 2E8 */ VPADDUSW,
    /* 2E9 */ VPADDW,
    /* 2EA */ VPALIGNR,
    /* 2EB */ VPAND,
    /* 2EC */ VPANDN,
    /* 2ED */ VPAVGB,
    /* 2EE */ VPAVGW,
    /* 2EF */ VPBLENDVB,
    /* 2F0 */ VPBLENDW,
    /* 2F1 */ VPCLMULQDQ,
    /* 2F2 */ VPCMPEQB,
    /* 2F3 */ VPCMPEQD,
    /* 2F4 */ VPCMPEQQ,
    /* 2F5 */ VPCMPEQW,
    /* 2F6 */ VPCMPESTRI,
    /* 2F7 */ VPCMPESTRM,
    /* 2F8 */ VPCMPGTB,
    /* 2F9 */ VPCMPGTD,
    /* 2FA */ VPCMPGTQ,
    /* 2FB */ VPCMPGTW,
    /* 2FC */ VPCMPISTRI,
    /* 2FD */ VPCMPISTRM,
    /* 2FE */ VPERM2F128,
    /* 2FF */ VPERMILPD,
    /* 300 */ VPERMILPS,
    /* 301 */ VPEXTRB,
    /* 302 */ VPEXTRD,
    /* 303 */ VPEXTRQ,
    /* 304 */ VPEXTRW,
    /* 305 */ VPHADDD,
    /* 306 */ VPHADDSW,
    /* 307 */ VPHADDW,
    /* 308 */ VPHMINPOSUW,
    /* 309 */ VPHSUBD,
    /* 30A */ VPHSUBSW,
    /* 30B */ VPHSUBW,
    /* 30C */ VPINSRB,
    /* 30D */ VPINSRD,
    /* 30E */ VPINSRQ,
    /* 30F */ VPINSRW,
    /* 310 */ VPMADDUBSW,
    /* 311 */ VPMADDWD,
    /* 312 */ VPMAXSB,
    /* 313 */ VPMAXSD,
    /* 314 */ VPMAXSW,
    /* 315 */ VPMAXUB,
    /* 316 */ VPMAXUD,
    /* 317 */ VPMAXUW,
    /* 318 */ VPMINSB,
    /* 319 */ VPMINSD,
    /* 31A */ VPMINSW,
    /* 31B */ VPMINUB,
    /* 31C */ VPMINUD,
    /* 31D */ VPMINUW,
    /* 31E */ VPMOVMSKB,
    /* 31F */ VPMOVSXBD,
    /* 320 */ VPMOVSXBQ,
    /* 321 */ VPMOVSXBW,
    /* 322 */ VPMOVSXWD,
    /* 323 */ VPMOVSXWQ,
    /* 324 */ VPMOVZXBD,
    /* 325 */ VPMOVZXBQ,
    /* 326 */ VPMOVZXBW,
    /* 327 */ VPMOVZXDQ,
    /* 328 */ VPMOVZXWD,
    /* 329 */ VPMOVZXWQ,
    /* 32A */ VPMULDQ,
    /* 32B */ VPMULHRSW,
    /* 32C */ VPMULHUW,
    /* 32D */ VPMULHW,
    /* 32E */ VPMULLD,
    /* 32F */ VPMULLW,
    /* 330 */ VPOR,
    /* 331 */ VPSADBW,
    /* 332 */ VPSHUFB,
    /* 333 */ VPSHUFD,
    /* 334 */ VPSHUFHW,
    /* 335 */ VPSHUFLW,
    /* 336 */ VPSIGNB,
    /* 337 */ VPSIGND,
    /* 338 */ VPSIGNW,
    /* 339 */ VPSLLD,
    /* 33A */ VPSLLDQ,
    /* 33B */ VPSLLQ,
    /* 33C */ VPSLLW,
    /* 33D */ VPSRAD,
    /* 33E */ VPSRAW,
    /* 33F */ VPSRLD,
    /* 340 */ VPSRLDQ,
    /* 341 */ VPSRLQ,
    /* 342 */ VPSRLW,
    /* 343 */ VPSUBB,
    /* 344 */ VPSUBD,
    /* 345 */ VPSUBQ,
    /* 346 */ VPSUBSB,
    /* 347 */ VPSUBSW,
    /* 348 */ VPSUBUSB,
    /* 349 */ VPSUBUSW,
    /* 34A */ VPSUBW,
    /* 34B */ VPTEST,
    /* 34C */ VPUNPCKHBW,
    /* 34D */ VPUNPCKHDQ,
    /* 34E */ VPUNPCKHQDQ,
    /* 34F */ VPUNPCKHWD,
    /* 350 */ VPUNPCKLBW,
    /* 351 */ VPUNPCKLDQ,
    /* 352 */ VPUNPCKLQDQ,
    /* 353 */ VPUNPCKLWD,
    /* 354 */ VPXOR,
    /* 355 */ VRCPPS,
    /* 356 */ VRCPSS,
    /* 357 */ VROUNDPD,
    /* 358 */ VROUNDPS,
    /* 359 */ VROUNDSD,
    /* 35A */ VROUNDSS,
    /* 35B */ VRSQRTPS,
    /* 35C */ VRSQRTSS,
    /* 35D */ VSHUFPD,
    /* 35E */ VSHUFPS,
    /* 35F */ VSQRTPD,
    /* 360 */ VSQRTPS,
    /* 361 */ VSQRTSD,
    /* 362 */ VSQRTSS,
    /* 363 */ VSTMXCSR,
    /* 364 */ VSUBPD,
    /* 365 */ VSUBPS,
    /* 366 */ VSUBSD,
    /* 367 */ VSUBSS,
    /* 368 */ VTESTPD,
    /* 369 */ VTESTPS,
    /* 36A */ VUCOMISD,
    /* 36B */ VUCOMISS,
    /* 36C */ VUNPCKHPD,
    /* 36D */ VUNPCKHPS,
    /* 36E */ VUNPCKLPD,
    /* 36F */ VUNPCKLPS,
    /* 370 */ VXORPD,
    /* 371 */ VXORPS,
    /* 372 */ VZEROALL,
    /* 373 */ VZEROUPPER,
    /* 374 */ WAIT,
    /* 375 */ WBINVD,
    /* 376 */ WRMSR,
    /* 377 */ XADD,
    /* 378 */ XCHG,
    /* 379 */ XCRYPTCBC,
    /* 37A */ XCRYPTCFB,
    /* 37B */ XCRYPTCTR,
    /* 37C */ XCRYPTECB,
    /* 37D */ XCRYPTOFB,
    /* 37E */ XGETBV,
    /* 37F */ XLATB,
    /* 380 */ XOR,
    /* 381 */ XORPD,
    /* 382 */ XORPS,
    /* 383 */ XRSTOR,
    /* 384 */ XSAVE,
    /* 385 */ XSETBV,
    /* 386 */ XSHA1,
    /* 387 */ XSHA256,
    /* 388 */ XSTORE,
};

/**
 * @brief   Defines an alias representing an opcode tree node. An opcode tree node is a 16 bit
 *          unsigned integer value with its first 4 bits reserved for the node type.
 */
typedef uint16_t OpcodeTreeNode;

/**
 * @brief   Values that represent the type of an opcode tree node.
 */
enum class OpcodeTreeNodeType : uint8_t
{
    /**
     * @brief   Reference to a concrete instruction definition.
     */
    INSTRUCTION_DEFINITION  =  0,
    /**
     * @brief   Reference to an opcode table.
     */
    TABLE                   =  1,
    /**
     * @brief   Reference to a modrm_mod switch table.
     */
    MODRM_MOD               =  2,
    /**
     * @brief   Reference to a modrm_reg switch table.
     */                                                                                      
    MODRM_REG               =  3,
    /**
     * @brief   Reference to a modrm_rm switch table.
     */
    MODRM_RM                =  4,
    /**
     * @brief   Reference to a mandatory-prefix switch table.
     */
    MANDATORY               =  5,
    /**
     * @brief   Reference to a x87 opcode table.
     */
    X87                     =  6,
    /**
     * @brief   Reference to an address-size switch table.
     */
    ADDRESS_SIZE            =  7,
    /**
     * @brief   Reference to an operand-size switch table.
     */
    OPERAND_SIZE            =  8,
    /**
     * @brief   Reference to a cpu-mode switch table.
     */
    MODE                    =  9,
    /**
     * @brief   Reference to a vendor switch table.
     */
    VENDOR                  = 10,
    /**
     * @brief   Reference to a 3dnow! opcode table.
     */
    AMD3DNOW                = 11,
    /**
     * @brief   Reference to a vex-prefix switch table.
     */
    VEX                     = 12,
    /**
     * @brief   Reference to a vex_w switch table.
     */
    VEXW                    = 13,
    /**
     * @brief   Reference to a vex_l switch table.
     */
    VEXL                    = 14
};

/**
 * @brief   Values that represent the type of an operand in the instruction definition.
 */
enum class DefinedOperandType : uint8_t
{
    /*
     * @brief   No operand. 
     */
    NONE,
    /*
     * @brief   Direct address. The instruction has no ModR/M byte; the address of the operand is 
     *          encoded in the instruction; no base register, index register, or scaling factor 
     *          can be applied. 
     */
    A,  
    /*
     * @brief   The reg field of the ModR/M byte selects a control register.
     */
    C,
    /*
     * @brief   The reg field of the ModR/M byte selects a debug register.
     */
    D,
    /*
     * @brief   A ModR/M byte follows the opcode and specifies the operand. The operand is either 
     *          a general-purpose register or a memory address. If it is a memory address, the 
     *          address is computed from a segment register and any of the following values: 
     *          a base register, an index register, a scaling factor, or a displacement.
     */
    E,  
    /*
     * @brief   rFLAGS register.
     */
    F,  
    /*
     * @brief   The reg field of the ModR/M byte selects a general register. 
     */
    G,
    /*
     * @brief   The r/m field of the ModR/M byte always selects a general register, regardless of 
     *          the mod field.
     */
    H,
    /*
     * @brief   Immediate data. The operand value is encoded in subsequent bytes of the 
     *          instruction. 
     */
    I,
    /*
     * @brief   Signed immediate data. The operand value is encoded in subsequent bytes of the 
     *          instruction. 
     */
    sI,
    /*
     * @brief   Constant immediate data value of 1. 
     */
    I1,
    /*
     * @brief   The instruction contains a relative offset to be added to the instruction pointer 
     *          register.
     */
    J,
    /*
     * @brief   Source operand is encoded in immediate byte (VEX only). 
     */
    L,
    /*
     * @brief   The ModR/M byte may refer only to memory: mod != 11bin. 
     */
    M, 
    /*
     * @brief   Combination of M and R.  
     */
    MR,
    /*
     * @brief   Combination of M and U. 
     */
    MU,
    /*
     * @brief   The R/M field of the ModR/M byte selects a packed quadword MMX technology register.
     */
    N, 
    /*
     * @brief   The instruction has no ModR/M byte; the offset of the operand is coded as a word, 
     *          double word or quad word (depending on address size attribute) in the instruction. 
     *          No base register, index register, or scaling factor can be applied.
     */
    O,
    /*
     * @brief   The reg field of the ModR/M byte selects a packed quadword MMX technology register.
     */
    P,
    /*
     * @brief   A ModR/M byte follows the opcode and specifies the operand. The operand is either 
     *          an MMX technology register or a memory address. If it is a memory address, the 
     *          address is computed from a segment register and any of the following values:
     *          a base register, an index register, a scaling factor, and a displacement.
     */
    Q, 
    /*
     * @brief   The mod field of the ModR/M byte may refer only to a general register.
     */
    R,  
    /*
     * @brief   The reg field of the ModR/M byte selects a segment register.
     */
    S, 
    /*
     * @brief   The R/M field of the ModR/M byte selects a 128-bit XMM register.
     */
    U,  
    /*
     * @brief   The reg field of the ModR/M byte selects a 128-bit XMM register.
     */
    V,   
    /*
     * @brief   A ModR/M byte follows the opcode and specifies the operand. The operand is either 
     *          a 128-bit XMM register or a memory address. If it is a memory address, the address 
     *          is computed from a segment register and any of the following values: 
     *          a base register, an index register, a scaling factor, and a displacement.
     */
    W, 
    /**
     * @brief   Register 0.
     */
    R0, 
    /**
     * @brief   Register 1.
     */
    R1, 
    /**
     * @brief   Register 2.
     */
    R2,    
    /**
     * @brief   Register 3.
     */
    R3, 
    /**
     * @brief   Register 4.
     */
    R4, 
    /**
     * @brief   Register 5.
     */
    R5, 
    /**
     * @brief   Register 6.
     */
    R6, 
    /**
     * @brief   Register 7.
     */
    R7,
    /**
     * @brief   AL register.
     */
    AL,  
    /**
     * @brief   CL register.
     */
    CL,  
    /**
     * @brief   DL register.
     */
    DL,
    /**
     * @brief   AX register.
     */
    AX,  
    /**
     * @brief   CX register.
     */
    CX,  
    /**
     * @brief   DX register.
     */
    DX,
    /**
     * @brief   EAX register.
     */
    EAX, 
    /**
     * @brief   ECX register.
     */
    ECX, 
    /**
     * @brief   EDX register.
     */
    EDX,
    /**
     * @brief   RAX register.
     */
    RAX, 
    /**
     * @brief   RCX register.
     */
    RCX, 
    /**
     * @brief   RDX register.
     */
    RDX,
    /**
     * @brief   ES segment register.
     */
    ES, 
    /**
     * @brief   CS segment register.
     */
    CS, 
    /**
     * @brief   SS segment register.
     */
    SS, 
    /**
     * @brief   DS segment register.
     */
    DS, 
    /**
     * @brief   FS segment register.
     */
    FS, 
    /**
     * @brief   GS segment register.
     */
    GS,
    /**
     * @brief   Floating point register 0.
     */
    ST0, 
    /**
     * @brief   Floating point register 1.
     */
    ST1, 
    /**
     * @brief   Floating point register 2.
     */
    ST2, 
    /**
     * @brief   Floating point register 3.
     */
    ST3, 
    /**
     * @brief   Floating point register 4.
     */
    ST4, 
    /**
     * @brief   Floating point register 5.
     */
    ST5, 
    /**
     * @brief   Floating point register 6.
     */
    ST6, 
    /**
     * @brief   Floating point register 7.
     */
    ST7
};

/**
 * @brief   Values that represent the size of an operand in the instruction definition.
 *          Do not change the order or the values of this enum! 
 */
enum class DefinedOperandSize : uint8_t
{
    /**
     * @brief   No operand.
     */
    NA  = 0,
    /**
     * @brief   Word, dword or qword.
     */
    Z,
    /**
     * @brief   Word, dword or qword.
     */
    V,
    /**
     * @brief   Dword or qword.
     */
    Y,
    /**
     * @brief   Oword or yword.
     */
    X,
    /**
     * @brief   Dword or qword, depending on the disassembler mode.
     */
    RDQ,
    /*
     * @brief   Byte, regardless of operand-size attribute.
     */
    B,
    /*
     * @brief   Word, regardless of operand-size attribute.
     */
    W,
    /*
     * @brief   Doubleword, regardless of operand-size attribute.
     */
    D,
    /*
     * @brief   Quadword, regardless of operand-size attribute.
     */
    Q,
    /*
     * @brief   10-byte far pointer.
     */
    T,
    /**
     * @brief   TODO:
     */
    O,
    /*
     * @brief   Double-quadword, regardless of operand-size attribute.
     */
    DQ, 
    /*
     * @brief   Quad-quadword, regardless of operand-size attribute.
     */
    QQ,
    /**
     * @brief   B sized register or D sized memory operand.
     */
    BD  = (static_cast<uint8_t>(B) << 4) | static_cast<uint8_t>(D),
    /**
     * @brief   B sized register or V sized memory operand.
     */
    BV  = (static_cast<uint8_t>(B) << 4) | static_cast<uint8_t>(V),
    /**
     * @brief   W sized register or D sized memory operand.
     */
    WD  = (static_cast<uint8_t>(W) << 4) | static_cast<uint8_t>(D),
    /**
     * @brief   W sized register or V sized memory operand.
     */
    WV  = (static_cast<uint8_t>(W) << 4) | static_cast<uint8_t>(V),
    /**
     * @brief   W sized register or Y sized memory operand.
     */
    WY  = (static_cast<uint8_t>(W) << 4) | static_cast<uint8_t>(Y),
    /**
     * @brief   D sized register or Y sized memory operand.
     */
    DY  = (static_cast<uint8_t>(D) << 4) | static_cast<uint8_t>(Y),
    /**
     * @brief   W sized register or O sized memory operand.
     */
    WO  = (static_cast<uint8_t>(W) << 4) | static_cast<uint8_t>(O),
    /**
     * @brief   D sized register or O sized memory operand.
     */
    DO  = (static_cast<uint8_t>(D) << 4) | static_cast<uint8_t>(O),
    /**
     * @brief   Q sized register or O sized memory operand.
     */
    QO  = (static_cast<uint8_t>(Q) << 4) | static_cast<uint8_t>(O),
};

/**
 * @brief   Values that represent optional flags in the instruction definition.   
 *          Do not change the order or the values of this enum!            
 */
enum InstructionDefinitionFlags : uint16_t
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
    IDF_OPERAND2_READWRITE              = 0x4000
};

#pragma pack (push, 1)
/**
 * @brief   An operand definition.
 */
struct OperandDefinition     
{               
    /**
     * @brief   The defined operand type.
     */
    DefinedOperandType type;
    /**
     * @brief   The defined operand size.
     */
    DefinedOperandSize size;
};
/**
 * @brief   An instruction definition.
 */
struct InstructionDefinition
{
    /**
     * @brief   The instruction mnemonic.
     */
    InstructionMnemonic mnemonic;
    /**
     * @brief   The operand definitions for all four possible operands.
     */
    OperandDefinition operand[4];
    /**
     * @brief   Additional flags for the instruction definition.
     */
    uint16_t flags;   
};
#pragma pack (pop)

namespace Internal
{

/**
 * @brief   Contains all opcode tables.
 *          Indexed by the numeric value of the opcode.
 */
extern const OpcodeTreeNode optreeTable[][256];
/**
 * @brief   Contains all modrm_mod switch tables.
 *          Index values:
 *          0 = [modrm_mod == !11]
 *          1 = [modrm_mod ==  11]
 */
extern const OpcodeTreeNode optreeModrmMod[][2];
/**
 * @brief   Contains all modrm_reg switch tables.
 *          Indexed by the numeric value of the modrm_reg field.
 */
extern const OpcodeTreeNode optreeModrmReg[][8];
/**
 * @brief   Contains all modrm_rm switch tables.
 *          Indexed by the numeric value of the modrm_rm field.
 */
extern const OpcodeTreeNode optreeModrmRm[][8];
/**
 * @brief   Contains all mandatory-prefix switch tables.
 *          Index values:
 *          0 = none
 *          1 = F2  
 *          2 = F3  
 *          3 = 66
 */
extern const OpcodeTreeNode optreeMandatory[][4];
/**
 * @brief   Contains all x87 opcode tables.
 *          Indexed by the numeric value of the 6 lowest bits of the modrm byte (modrm_mod should
 *          always be 11). 
 */
extern const OpcodeTreeNode optreeX87[][64];
/**
 * @brief   Contains all address-size switch tables.
 *          Index values:
 *          0 = 16
 *          1 = 32  
 *          2 = 64
 */
extern const OpcodeTreeNode optreeAddressSize[][3];
/**
 * @brief   Contains all operand-size switch tables.
 *          Index values:
 *          0 = 16
 *          1 = 32  
 *          2 = 64
 */
extern const OpcodeTreeNode optreeOperandSize[][3];
/**
 * @brief   Contains all cpu-mode switch tables.
 *          Index values:
 *          0 = [!= 64]
 *          1 = 64
 */
extern const OpcodeTreeNode optreeMode[][2];
/**
 * @brief   Contains all vendor switch tables. 
 *          Index values:
 *          0 = AMD
 *          1 = Intel  
 */
extern const OpcodeTreeNode optreeVendor[][2];
/**
 * @brief   Contains all 3dnow! switch tables.
 *          Indexed by the numeric value of the 3dnow! opcode.
 */
extern const OpcodeTreeNode optree3dnow[][256];
/**
 * @brief   Contains all vex switch tables.
 *          Index values:
 *          0 = none
 *          1 = 0F  
 *          2 = 0F38  
 *          3 = 0F3A  
 *          4 = 66  
 *          5 = 66_0F  
 *          6 = 66_0F38  
 *          7 = 66_0F3A  
 *          8 = F3  
 *          9 = F3_0F
 *          A = F3_0F38
 *          B = F3_0F3A
 *          C = F2
 *          D = F2_0F
 *          E = F2_0F38
 *          F = F2_0F3A
 */
extern const OpcodeTreeNode optreeVex[][16];
/**
 * @brief   Contains all vex_w switch tables.
 *          Indexed by the numeric value of the vex_w field.
 */
extern const OpcodeTreeNode optreeVexW[][2];
/**
 * @brief   Contains all vex_l switch tables.
 *          Indexed by the numeric value of the vex_l field.
 */
extern const OpcodeTreeNode optreeVexL[][2];
/**
 * @brief   Contains all instruction definitions.
 */
extern const InstructionDefinition instrDefinitions[];
/**
 * @brief   Contains all instruction mnemonic strings.
 */
extern const char* instrMnemonicStrings[];

/**
 * @brief   Returns the type of the specified opcode tree node.
 * @param   node    The node.
 * @return  The type of the specified opcode tree node.
 */
inline OpcodeTreeNodeType GetOpcodeNodeType(OpcodeTreeNode node)
{
    return static_cast<OpcodeTreeNodeType>((node >> 12) & 0x0F);
} 

/**
 * @brief   Returns the value of the specified opcode tree node.
 * @param   node    The node.
 * @return  The value of the specified opcode tree node.
 */
inline uint16_t GetOpcodeNodeValue(OpcodeTreeNode node)
{
    return (node & 0x0FFF);   
}

/**
 * @brief   Returns the root node of the opcode tree.
 * @return  The root node of the opcode tree.
 */
inline OpcodeTreeNode GetOpcodeTreeRoot()
{
    return 0x1000;
}

/**
 * @brief   Returns a child node of @c parent specified by @c index.
 * @param   parent  The parent node.
 * @param   index   The index of the child node to retrieve.
 * @return  The specified child node.
 */
inline OpcodeTreeNode GetOpcodeTreeChild(OpcodeTreeNode parent, uint16_t index)
{
    using namespace Internal;
    OpcodeTreeNodeType nodeType = GetOpcodeNodeType(parent);
    uint16_t tableIndex = GetOpcodeNodeValue(parent);
    switch (nodeType)
    {
    case OpcodeTreeNodeType::TABLE:
        assert(index < 256);
        return optreeTable[tableIndex][index];
    case OpcodeTreeNodeType::MODRM_MOD:
        assert(index < 2);
        return optreeModrmMod[tableIndex][index];
    case OpcodeTreeNodeType::MODRM_REG:
        assert(index < 8);
        return optreeModrmReg[tableIndex][index];
    case OpcodeTreeNodeType::MODRM_RM:
        assert(index < 8);
        return optreeModrmRm[tableIndex][index];
    case OpcodeTreeNodeType::MANDATORY:
        assert(index < 4);
        return optreeMandatory[tableIndex][index];
    case OpcodeTreeNodeType::X87:
        assert(index < 64);
        return optreeX87[tableIndex][index];
    case OpcodeTreeNodeType::ADDRESS_SIZE:
        assert(index < 3);
        return optreeAddressSize[tableIndex][index];
    case OpcodeTreeNodeType::OPERAND_SIZE:
        assert(index < 3);
        return optreeOperandSize[tableIndex][index];
    case OpcodeTreeNodeType::MODE:
        assert(index < 2);
        return optreeMode[tableIndex][index];
    case OpcodeTreeNodeType::VENDOR:
        assert(index < 3);
        return optreeVendor[tableIndex][index];
    case OpcodeTreeNodeType::AMD3DNOW:
        assert(index < 256);
        return optree3dnow[tableIndex][index];
    case OpcodeTreeNodeType::VEX:
        assert(index < 16);
        return optreeVex[tableIndex][index];
    case OpcodeTreeNodeType::VEXW:
        assert(index < 2);
        return optreeVexW[tableIndex][index];
    case OpcodeTreeNodeType::VEXL:
        assert(index < 2);
        return optreeVexL[tableIndex][index];
    default:
        assert(0);
    }
    return 0xFFFF;
}

/**
 * @brief   Returns the instruction definition that is linked to the given @c node.
 * @param   node    The instruction definition node.
 * @return  Pointer to the instruction definition.
 */
inline const InstructionDefinition* GetInstructionDefinition(OpcodeTreeNode node)
{
    assert(GetOpcodeNodeType(node) == OpcodeTreeNodeType::INSTRUCTION_DEFINITION);
    return& instrDefinitions[node & 0x0FFF];    
}

/**
 * @brief   Returns the specified instruction mnemonic string.
 * @param   mnemonic    The mnemonic.
 * @return  The instruction mnemonic string.
 */
inline const char* GetInstructionMnemonicString(InstructionMnemonic mnemonic)
{
    return instrMnemonicStrings[static_cast<uint16_t>(mnemonic)];
}

/**
 * @brief   Returns the numeric value for a simple operand size definition.
 * @param   operandSize The defined operand size.
 * @return  The the numeric value for the simple operand size definition.
 */
inline uint16_t GetSimpleOperandSize(DefinedOperandSize operandSize)
{
    static uint16_t operandSizes[8] =
    {
        8, 16, 32, 64, 80, 12, 128, 256
    };
    uint16_t index = 
        static_cast<uint8_t>(operandSize) - static_cast<uint8_t>(DefinedOperandSize::B);
    assert(index < 8);
    return operandSizes[index];
}

/**
 * @brief   Returns the memory-size part of a complex operand size definition.
 * @param   operandSize The defined operand size.
 * @return  The memory-size part of the operand size definition.
 */
inline DefinedOperandSize GetComplexOperandMemSize(DefinedOperandSize operandSize)
{
    return static_cast<DefinedOperandSize>(static_cast<uint8_t>(operandSize) & 0x0F);
}

/**
 * @brief   Returns the register-size part of a complex operand size definition.
 * @param   operandSize The defined operand size.
 * @return  The register-size part of the operand size definition.
 */
inline DefinedOperandSize GetComplexOperandRegSize(DefinedOperandSize operandSize)
{
    return static_cast<DefinedOperandSize>((static_cast<uint8_t>(operandSize) >> 4) & 0x0F);    
}

}

}

#endif /* _ZYDIS_OPCODETABLE_HPP_ */
