/**************************************************************************************************

  Verteron Disassembler Engine
  Version 1.0

  Remarks         : Freeware, Copyright must be included

  Original Author : Florian Bernd
  Modifications   :

  Last change     : 14. October 2014

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
#pragma once

#include "stdint.h"
#include "assert.h"

namespace Verteron
{

namespace Disassembler 
{

/**
 * @brief   Values that represent an instruction mnemonic.
 */
enum class VXInstructionMnemonic : uint16_t
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
    /* 034 */ CMOVG,
    /* 035 */ CMOVGE,
    /* 036 */ CMOVL,
    /* 037 */ CMOVLE,
    /* 038 */ CMOVNO,
    /* 039 */ CMOVNP,
    /* 03A */ CMOVNS,
    /* 03B */ CMOVNZ,
    /* 03C */ CMOVO,
    /* 03D */ CMOVP,
    /* 03E */ CMOVS,
    /* 03F */ CMOVZ,
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
    /* 0AF */ FNINIT,
    /* 0B0 */ FNOP,
    /* 0B1 */ FNSAVE,
    /* 0B2 */ FNSTCW,
    /* 0B3 */ FNSTENV,
    /* 0B4 */ FNSTSW,
    /* 0B5 */ FPATAN,
    /* 0B6 */ FPREM,
    /* 0B7 */ FPREM1,
    /* 0B8 */ FPTAN,
    /* 0B9 */ FRNDINT,
    /* 0BA */ FRSTOR,
    /* 0BB */ FSCALE,
    /* 0BC */ FSIN,
    /* 0BD */ FSINCOS,
    /* 0BE */ FSQRT,
    /* 0BF */ FST,
    /* 0C0 */ FSTP,
    /* 0C1 */ FSTP1,
    /* 0C2 */ FSTP8,
    /* 0C3 */ FSTP9,
    /* 0C4 */ FSUB,
    /* 0C5 */ FSUBP,
    /* 0C6 */ FSUBR,
    /* 0C7 */ FSUBRP,
    /* 0C8 */ FTST,
    /* 0C9 */ FUCOM,
    /* 0CA */ FUCOMI,
    /* 0CB */ FUCOMIP,
    /* 0CC */ FUCOMP,
    /* 0CD */ FUCOMPP,
    /* 0CE */ FXAM,
    /* 0CF */ FXCH,
    /* 0D0 */ FXCH4,
    /* 0D1 */ FXCH7,
    /* 0D2 */ FXRSTOR,
    /* 0D3 */ FXSAVE,
    /* 0D4 */ FXTRACT,
    /* 0D5 */ FYL2X,
    /* 0D6 */ FYL2XP1,
    /* 0D7 */ GETSEC,
    /* 0D8 */ HADDPD,
    /* 0D9 */ HADDPS,
    /* 0DA */ HLT,
    /* 0DB */ HSUBPD,
    /* 0DC */ HSUBPS,
    /* 0DD */ IDIV,
    /* 0DE */ IMUL,
    /* 0DF */ IN,
    /* 0E0 */ INC,
    /* 0E1 */ INSB,
    /* 0E2 */ INSD,
    /* 0E3 */ INSERTPS,
    /* 0E4 */ INSW,
    /* 0E5 */ INT,
    /* 0E6 */ INT1,
    /* 0E7 */ INT3,
    /* 0E8 */ INTO,
    /* 0E9 */ INVD,
    /* 0EA */ INVEPT,
    /* 0EB */ INVLPG,
    /* 0EC */ INVLPGA,
    /* 0ED */ INVVPID,
    /* 0EE */ IRETD,
    /* 0EF */ IRETQ,
    /* 0F0 */ IRETW,
    /* 0F1 */ JA,
    /* 0F2 */ JAE,
    /* 0F3 */ JB,
    /* 0F4 */ JBE,
    /* 0F5 */ JCXZ,
    /* 0F6 */ JECXZ,
    /* 0F7 */ JG,
    /* 0F8 */ JGE,
    /* 0F9 */ JL,
    /* 0FA */ JLE,
    /* 0FB */ JMP,
    /* 0FC */ JNO,
    /* 0FD */ JNP,
    /* 0FE */ JNS,
    /* 0FF */ JNZ,
    /* 100 */ JO,
    /* 101 */ JP,
    /* 102 */ JRCXZ,
    /* 103 */ JS,
    /* 104 */ JZ,
    /* 105 */ LAHF,
    /* 106 */ LAR,
    /* 107 */ LDDQU,
    /* 108 */ LDMXCSR,
    /* 109 */ LDS,
    /* 10A */ LEA,
    /* 10B */ LEAVE,
    /* 10C */ LES,
    /* 10D */ LFENCE,
    /* 10E */ LFS,
    /* 10F */ LGDT,
    /* 110 */ LGS,
    /* 111 */ LIDT,
    /* 112 */ LLDT,
    /* 113 */ LMSW,
    /* 114 */ LOCK,
    /* 115 */ LODSB,
    /* 116 */ LODSD,
    /* 117 */ LODSQ,
    /* 118 */ LODSW,
    /* 119 */ LOOP,
    /* 11A */ LOOPE,
    /* 11B */ LOOPNE,
    /* 11C */ LSL,
    /* 11D */ LSS,
    /* 11E */ LTR,
    /* 11F */ MASKMOVDQU,
    /* 120 */ MASKMOVQ,
    /* 121 */ MAXPD,
    /* 122 */ MAXPS,
    /* 123 */ MAXSD,
    /* 124 */ MAXSS,
    /* 125 */ MFENCE,
    /* 126 */ MINPD,
    /* 127 */ MINPS,
    /* 128 */ MINSD,
    /* 129 */ MINSS,
    /* 12A */ MONITOR,
    /* 12B */ MONTMUL,
    /* 12C */ MOV,
    /* 12D */ MOVAPD,
    /* 12E */ MOVAPS,
    /* 12F */ MOVBE,
    /* 130 */ MOVD,
    /* 131 */ MOVDDUP,
    /* 132 */ MOVDQ2Q,
    /* 133 */ MOVDQA,
    /* 134 */ MOVDQU,
    /* 135 */ MOVHLPS,
    /* 136 */ MOVHPD,
    /* 137 */ MOVHPS,
    /* 138 */ MOVLHPS,
    /* 139 */ MOVLPD,
    /* 13A */ MOVLPS,
    /* 13B */ MOVMSKPD,
    /* 13C */ MOVMSKPS,
    /* 13D */ MOVNTDQ,
    /* 13E */ MOVNTDQA,
    /* 13F */ MOVNTI,
    /* 140 */ MOVNTPD,
    /* 141 */ MOVNTPS,
    /* 142 */ MOVNTQ,
    /* 143 */ MOVQ,
    /* 144 */ MOVQ2DQ,
    /* 145 */ MOVSB,
    /* 146 */ MOVSD,
    /* 147 */ MOVSHDUP,
    /* 148 */ MOVSLDUP,
    /* 149 */ MOVSQ,
    /* 14A */ MOVSS,
    /* 14B */ MOVSW,
    /* 14C */ MOVSX,
    /* 14D */ MOVSXD,
    /* 14E */ MOVUPD,
    /* 14F */ MOVUPS,
    /* 150 */ MOVZX,
    /* 151 */ MPSADBW,
    /* 152 */ MUL,
    /* 153 */ MULPD,
    /* 154 */ MULPS,
    /* 155 */ MULSD,
    /* 156 */ MULSS,
    /* 157 */ MWAIT,
    /* 158 */ NEG,
    /* 159 */ NOP,
    /* 15A */ NOT,
    /* 15B */ OR,
    /* 15C */ ORPD,
    /* 15D */ ORPS,
    /* 15E */ OUT,
    /* 15F */ OUTSB,
    /* 160 */ OUTSD,
    /* 161 */ OUTSW,
    /* 162 */ PABSB,
    /* 163 */ PABSD,
    /* 164 */ PABSW,
    /* 165 */ PACKSSDW,
    /* 166 */ PACKSSWB,
    /* 167 */ PACKUSDW,
    /* 168 */ PACKUSWB,
    /* 169 */ PADDB,
    /* 16A */ PADDD,
    /* 16B */ PADDQ,
    /* 16C */ PADDSB,
    /* 16D */ PADDSW,
    /* 16E */ PADDUSB,
    /* 16F */ PADDUSW,
    /* 170 */ PADDW,
    /* 171 */ PALIGNR,
    /* 172 */ PAND,
    /* 173 */ PANDN,
    /* 174 */ PAUSE,
    /* 175 */ PAVGB,
    /* 176 */ PAVGUSB,
    /* 177 */ PAVGW,
    /* 178 */ PBLENDVB,
    /* 179 */ PBLENDW,
    /* 17A */ PCLMULQDQ,
    /* 17B */ PCMPEQB,
    /* 17C */ PCMPEQD,
    /* 17D */ PCMPEQQ,
    /* 17E */ PCMPEQW,
    /* 17F */ PCMPESTRI,
    /* 180 */ PCMPESTRM,
    /* 181 */ PCMPGTB,
    /* 182 */ PCMPGTD,
    /* 183 */ PCMPGTQ,
    /* 184 */ PCMPGTW,
    /* 185 */ PCMPISTRI,
    /* 186 */ PCMPISTRM,
    /* 187 */ PEXTRB,
    /* 188 */ PEXTRD,
    /* 189 */ PEXTRQ,
    /* 18A */ PEXTRW,
    /* 18B */ PF2ID,
    /* 18C */ PF2IW,
    /* 18D */ PFACC,
    /* 18E */ PFADD,
    /* 18F */ PFCMPEQ,
    /* 190 */ PFCMPGE,
    /* 191 */ PFCMPGT,
    /* 192 */ PFMAX,
    /* 193 */ PFMIN,
    /* 194 */ PFMUL,
    /* 195 */ PFNACC,
    /* 196 */ PFPNACC,
    /* 197 */ PFRCP,
    /* 198 */ PFRCPIT1,
    /* 199 */ PFRCPIT2,
    /* 19A */ PFRSQIT1,
    /* 19B */ PFRSQRT,
    /* 19C */ PFSUB,
    /* 19D */ PFSUBR,
    /* 19E */ PHADDD,
    /* 19F */ PHADDSW,
    /* 1A0 */ PHADDW,
    /* 1A1 */ PHMINPOSUW,
    /* 1A2 */ PHSUBD,
    /* 1A3 */ PHSUBSW,
    /* 1A4 */ PHSUBW,
    /* 1A5 */ PI2FD,
    /* 1A6 */ PI2FW,
    /* 1A7 */ PINSRB,
    /* 1A8 */ PINSRD,
    /* 1A9 */ PINSRQ,
    /* 1AA */ PINSRW,
    /* 1AB */ PMADDUBSW,
    /* 1AC */ PMADDWD,
    /* 1AD */ PMAXSB,
    /* 1AE */ PMAXSD,
    /* 1AF */ PMAXSW,
    /* 1B0 */ PMAXUB,
    /* 1B1 */ PMAXUD,
    /* 1B2 */ PMAXUW,
    /* 1B3 */ PMINSB,
    /* 1B4 */ PMINSD,
    /* 1B5 */ PMINSW,
    /* 1B6 */ PMINUB,
    /* 1B7 */ PMINUD,
    /* 1B8 */ PMINUW,
    /* 1B9 */ PMOVMSKB,
    /* 1BA */ PMOVSXBD,
    /* 1BB */ PMOVSXBQ,
    /* 1BC */ PMOVSXBW,
    /* 1BD */ PMOVSXDQ,
    /* 1BE */ PMOVSXWD,
    /* 1BF */ PMOVSXWQ,
    /* 1C0 */ PMOVZXBD,
    /* 1C1 */ PMOVZXBQ,
    /* 1C2 */ PMOVZXBW,
    /* 1C3 */ PMOVZXDQ,
    /* 1C4 */ PMOVZXWD,
    /* 1C5 */ PMOVZXWQ,
    /* 1C6 */ PMULDQ,
    /* 1C7 */ PMULHRSW,
    /* 1C8 */ PMULHRW,
    /* 1C9 */ PMULHUW,
    /* 1CA */ PMULHW,
    /* 1CB */ PMULLD,
    /* 1CC */ PMULLW,
    /* 1CD */ PMULUDQ,
    /* 1CE */ POP,
    /* 1CF */ POPA,
    /* 1D0 */ POPAD,
    /* 1D1 */ POPCNT,
    /* 1D2 */ POPFD,
    /* 1D3 */ POPFQ,
    /* 1D4 */ POPFW,
    /* 1D5 */ POR,
    /* 1D6 */ PREFETCH,
    /* 1D7 */ PREFETCHNTA,
    /* 1D8 */ PREFETCHT0,
    /* 1D9 */ PREFETCHT1,
    /* 1DA */ PREFETCHT2,
    /* 1DB */ PSADBW,
    /* 1DC */ PSHUFB,
    /* 1DD */ PSHUFD,
    /* 1DE */ PSHUFHW,
    /* 1DF */ PSHUFLW,
    /* 1E0 */ PSHUFW,
    /* 1E1 */ PSIGNB,
    /* 1E2 */ PSIGND,
    /* 1E3 */ PSIGNW,
    /* 1E4 */ PSLLD,
    /* 1E5 */ PSLLDQ,
    /* 1E6 */ PSLLQ,
    /* 1E7 */ PSLLW,
    /* 1E8 */ PSRAD,
    /* 1E9 */ PSRAW,
    /* 1EA */ PSRLD,
    /* 1EB */ PSRLDQ,
    /* 1EC */ PSRLQ,
    /* 1ED */ PSRLW,
    /* 1EE */ PSUBB,
    /* 1EF */ PSUBD,
    /* 1F0 */ PSUBQ,
    /* 1F1 */ PSUBSB,
    /* 1F2 */ PSUBSW,
    /* 1F3 */ PSUBUSB,
    /* 1F4 */ PSUBUSW,
    /* 1F5 */ PSUBW,
    /* 1F6 */ PSWAPD,
    /* 1F7 */ PTEST,
    /* 1F8 */ PUNPCKHBW,
    /* 1F9 */ PUNPCKHDQ,
    /* 1FA */ PUNPCKHQDQ,
    /* 1FB */ PUNPCKHWD,
    /* 1FC */ PUNPCKLBW,
    /* 1FD */ PUNPCKLDQ,
    /* 1FE */ PUNPCKLQDQ,
    /* 1FF */ PUNPCKLWD,
    /* 200 */ PUSH,
    /* 201 */ PUSHA,
    /* 202 */ PUSHAD,
    /* 203 */ PUSHFD,
    /* 204 */ PUSHFQ,
    /* 205 */ PUSHFW,
    /* 206 */ PXOR,
    /* 207 */ RCL,
    /* 208 */ RCPPS,
    /* 209 */ RCPSS,
    /* 20A */ RCR,
    /* 20B */ RDMSR,
    /* 20C */ RDPMC,
    /* 20D */ RDRAND,
    /* 20E */ RDTSC,
    /* 20F */ RDTSCP,
    /* 210 */ REP,
    /* 211 */ REPNE,
    /* 212 */ RETF,
    /* 213 */ RETN,
    /* 214 */ ROL,
    /* 215 */ ROR,
    /* 216 */ ROUNDPD,
    /* 217 */ ROUNDPS,
    /* 218 */ ROUNDSD,
    /* 219 */ ROUNDSS,
    /* 21A */ RSM,
    /* 21B */ RSQRTPS,
    /* 21C */ RSQRTSS,
    /* 21D */ SAHF,
    /* 21E */ SALC,
    /* 21F */ SAR,
    /* 220 */ SBB,
    /* 221 */ SCASB,
    /* 222 */ SCASD,
    /* 223 */ SCASQ,
    /* 224 */ SCASW,
    /* 225 */ SETA,
    /* 226 */ SETAE,
    /* 227 */ SETB,
    /* 228 */ SETBE,
    /* 229 */ SETG,
    /* 22A */ SETGE,
    /* 22B */ SETL,
    /* 22C */ SETLE,
    /* 22D */ SETNO,
    /* 22E */ SETNP,
    /* 22F */ SETNS,
    /* 230 */ SETNZ,
    /* 231 */ SETO,
    /* 232 */ SETP,
    /* 233 */ SETS,
    /* 234 */ SETZ,
    /* 235 */ SFENCE,
    /* 236 */ SGDT,
    /* 237 */ SHL,
    /* 238 */ SHLD,
    /* 239 */ SHR,
    /* 23A */ SHRD,
    /* 23B */ SHUFPD,
    /* 23C */ SHUFPS,
    /* 23D */ SIDT,
    /* 23E */ SKINIT,
    /* 23F */ SLDT,
    /* 240 */ SMSW,
    /* 241 */ SQRTPD,
    /* 242 */ SQRTPS,
    /* 243 */ SQRTSD,
    /* 244 */ SQRTSS,
    /* 245 */ STC,
    /* 246 */ STD,
    /* 247 */ STGI,
    /* 248 */ STI,
    /* 249 */ STMXCSR,
    /* 24A */ STOSB,
    /* 24B */ STOSD,
    /* 24C */ STOSQ,
    /* 24D */ STOSW,
    /* 24E */ STR,
    /* 24F */ SUB,
    /* 250 */ SUBPD,
    /* 251 */ SUBPS,
    /* 252 */ SUBSD,
    /* 253 */ SUBSS,
    /* 254 */ SWAPGS,
    /* 255 */ SYSCALL,
    /* 256 */ SYSENTER,
    /* 257 */ SYSEXIT,
    /* 258 */ SYSRET,
    /* 259 */ TEST,
    /* 25A */ UCOMISD,
    /* 25B */ UCOMISS,
    /* 25C */ UD2,
    /* 25D */ UNPCKHPD,
    /* 25E */ UNPCKHPS,
    /* 25F */ UNPCKLPD,
    /* 260 */ UNPCKLPS,
    /* 261 */ VADDPD,
    /* 262 */ VADDPS,
    /* 263 */ VADDSD,
    /* 264 */ VADDSS,
    /* 265 */ VADDSUBPD,
    /* 266 */ VADDSUBPS,
    /* 267 */ VAESDEC,
    /* 268 */ VAESDECLAST,
    /* 269 */ VAESENC,
    /* 26A */ VAESENCLAST,
    /* 26B */ VAESIMC,
    /* 26C */ VAESKEYGENASSIST,
    /* 26D */ VANDNPD,
    /* 26E */ VANDNPS,
    /* 26F */ VANDPD,
    /* 270 */ VANDPS,
    /* 271 */ VBLENDPD,
    /* 272 */ VBLENDPS,
    /* 273 */ VBLENDVPD,
    /* 274 */ VBLENDVPS,
    /* 275 */ VBROADCASTSD,
    /* 276 */ VBROADCASTSS,
    /* 277 */ VCMPPD,
    /* 278 */ VCMPPS,
    /* 279 */ VCMPSD,
    /* 27A */ VCMPSS,
    /* 27B */ VCOMISD,
    /* 27C */ VCOMISS,
    /* 27D */ VCVTDQ2PD,
    /* 27E */ VCVTDQ2PS,
    /* 27F */ VCVTPD2DQ,
    /* 280 */ VCVTPD2PS,
    /* 281 */ VCVTPS2DQ,
    /* 282 */ VCVTPS2PD,
    /* 283 */ VCVTSD2SI,
    /* 284 */ VCVTSD2SS,
    /* 285 */ VCVTSI2SD,
    /* 286 */ VCVTSI2SS,
    /* 287 */ VCVTSS2SD,
    /* 288 */ VCVTSS2SI,
    /* 289 */ VCVTTPD2DQ,
    /* 28A */ VCVTTPS2DQ,
    /* 28B */ VCVTTSD2SI,
    /* 28C */ VCVTTSS2SI,
    /* 28D */ VDIVPD,
    /* 28E */ VDIVPS,
    /* 28F */ VDIVSD,
    /* 290 */ VDIVSS,
    /* 291 */ VDPPD,
    /* 292 */ VDPPS,
    /* 293 */ VERR,
    /* 294 */ VERW,
    /* 295 */ VEXTRACTF128,
    /* 296 */ VEXTRACTPS,
    /* 297 */ VHADDPD,
    /* 298 */ VHADDPS,
    /* 299 */ VHSUBPD,
    /* 29A */ VHSUBPS,
    /* 29B */ VINSERTF128,
    /* 29C */ VINSERTPS,
    /* 29D */ VLDDQU,
    /* 29E */ VMASKMOVDQU,
    /* 29F */ VMASKMOVPD,
    /* 2A0 */ VMASKMOVPS,
    /* 2A1 */ VMAXPD,
    /* 2A2 */ VMAXPS,
    /* 2A3 */ VMAXSD,
    /* 2A4 */ VMAXSS,
    /* 2A5 */ VMCALL,
    /* 2A6 */ VMCLEAR,
    /* 2A7 */ VMINPD,
    /* 2A8 */ VMINPS,
    /* 2A9 */ VMINSD,
    /* 2AA */ VMINSS,
    /* 2AB */ VMLAUNCH,
    /* 2AC */ VMLOAD,
    /* 2AD */ VMMCALL,
    /* 2AE */ VMOVAPD,
    /* 2AF */ VMOVAPS,
    /* 2B0 */ VMOVD,
    /* 2B1 */ VMOVDDUP,
    /* 2B2 */ VMOVDQA,
    /* 2B3 */ VMOVDQU,
    /* 2B4 */ VMOVHLPS,
    /* 2B5 */ VMOVHPD,
    /* 2B6 */ VMOVHPS,
    /* 2B7 */ VMOVLHPS,
    /* 2B8 */ VMOVLPD,
    /* 2B9 */ VMOVLPS,
    /* 2BA */ VMOVMSKPD,
    /* 2BB */ VMOVMSKPS,
    /* 2BC */ VMOVNTDQ,
    /* 2BD */ VMOVNTDQA,
    /* 2BE */ VMOVNTPD,
    /* 2BF */ VMOVNTPS,
    /* 2C0 */ VMOVQ,
    /* 2C1 */ VMOVSD,
    /* 2C2 */ VMOVSHDUP,
    /* 2C3 */ VMOVSLDUP,
    /* 2C4 */ VMOVSS,
    /* 2C5 */ VMOVUPD,
    /* 2C6 */ VMOVUPS,
    /* 2C7 */ VMPSADBW,
    /* 2C8 */ VMPTRLD,
    /* 2C9 */ VMPTRST,
    /* 2CA */ VMREAD,
    /* 2CB */ VMRESUME,
    /* 2CC */ VMRUN,
    /* 2CD */ VMSAVE,
    /* 2CE */ VMULPD,
    /* 2CF */ VMULPS,
    /* 2D0 */ VMULSD,
    /* 2D1 */ VMULSS,
    /* 2D2 */ VMWRITE,
    /* 2D3 */ VMXOFF,
    /* 2D4 */ VMXON,
    /* 2D5 */ VORPD,
    /* 2D6 */ VORPS,
    /* 2D7 */ VPABSB,
    /* 2D8 */ VPABSD,
    /* 2D9 */ VPABSW,
    /* 2DA */ VPACKSSDW,
    /* 2DB */ VPACKSSWB,
    /* 2DC */ VPACKUSDW,
    /* 2DD */ VPACKUSWB,
    /* 2DE */ VPADDB,
    /* 2DF */ VPADDD,
    /* 2E0 */ VPADDQ,
    /* 2E1 */ VPADDSB,
    /* 2E2 */ VPADDSW,
    /* 2E3 */ VPADDUSB,
    /* 2E4 */ VPADDUSW,
    /* 2E5 */ VPADDW,
    /* 2E6 */ VPALIGNR,
    /* 2E7 */ VPAND,
    /* 2E8 */ VPANDN,
    /* 2E9 */ VPAVGB,
    /* 2EA */ VPAVGW,
    /* 2EB */ VPBLENDVB,
    /* 2EC */ VPBLENDW,
    /* 2ED */ VPCLMULQDQ,
    /* 2EE */ VPCMPEQB,
    /* 2EF */ VPCMPEQD,
    /* 2F0 */ VPCMPEQQ,
    /* 2F1 */ VPCMPEQW,
    /* 2F2 */ VPCMPESTRI,
    /* 2F3 */ VPCMPESTRM,
    /* 2F4 */ VPCMPGTB,
    /* 2F5 */ VPCMPGTD,
    /* 2F6 */ VPCMPGTQ,
    /* 2F7 */ VPCMPGTW,
    /* 2F8 */ VPCMPISTRI,
    /* 2F9 */ VPCMPISTRM,
    /* 2FA */ VPERM2F128,
    /* 2FB */ VPERMILPD,
    /* 2FC */ VPERMILPS,
    /* 2FD */ VPEXTRB,
    /* 2FE */ VPEXTRD,
    /* 2FF */ VPEXTRQ,
    /* 300 */ VPEXTRW,
    /* 301 */ VPHADDD,
    /* 302 */ VPHADDSW,
    /* 303 */ VPHADDW,
    /* 304 */ VPHMINPOSUW,
    /* 305 */ VPHSUBD,
    /* 306 */ VPHSUBSW,
    /* 307 */ VPHSUBW,
    /* 308 */ VPINSRB,
    /* 309 */ VPINSRD,
    /* 30A */ VPINSRQ,
    /* 30B */ VPINSRW,
    /* 30C */ VPMADDUBSW,
    /* 30D */ VPMADDWD,
    /* 30E */ VPMAXSB,
    /* 30F */ VPMAXSD,
    /* 310 */ VPMAXSW,
    /* 311 */ VPMAXUB,
    /* 312 */ VPMAXUD,
    /* 313 */ VPMAXUW,
    /* 314 */ VPMINSB,
    /* 315 */ VPMINSD,
    /* 316 */ VPMINSW,
    /* 317 */ VPMINUB,
    /* 318 */ VPMINUD,
    /* 319 */ VPMINUW,
    /* 31A */ VPMOVMSKB,
    /* 31B */ VPMOVSXBD,
    /* 31C */ VPMOVSXBQ,
    /* 31D */ VPMOVSXBW,
    /* 31E */ VPMOVSXWD,
    /* 31F */ VPMOVSXWQ,
    /* 320 */ VPMOVZXBD,
    /* 321 */ VPMOVZXBQ,
    /* 322 */ VPMOVZXBW,
    /* 323 */ VPMOVZXDQ,
    /* 324 */ VPMOVZXWD,
    /* 325 */ VPMOVZXWQ,
    /* 326 */ VPMULDQ,
    /* 327 */ VPMULHRSW,
    /* 328 */ VPMULHUW,
    /* 329 */ VPMULHW,
    /* 32A */ VPMULLD,
    /* 32B */ VPMULLW,
    /* 32C */ VPOR,
    /* 32D */ VPSADBW,
    /* 32E */ VPSHUFB,
    /* 32F */ VPSHUFD,
    /* 330 */ VPSHUFHW,
    /* 331 */ VPSHUFLW,
    /* 332 */ VPSIGNB,
    /* 333 */ VPSIGND,
    /* 334 */ VPSIGNW,
    /* 335 */ VPSLLD,
    /* 336 */ VPSLLDQ,
    /* 337 */ VPSLLQ,
    /* 338 */ VPSLLW,
    /* 339 */ VPSRAD,
    /* 33A */ VPSRAW,
    /* 33B */ VPSRLD,
    /* 33C */ VPSRLDQ,
    /* 33D */ VPSRLQ,
    /* 33E */ VPSRLW,
    /* 33F */ VPSUBB,
    /* 340 */ VPSUBD,
    /* 341 */ VPSUBQ,
    /* 342 */ VPSUBSB,
    /* 343 */ VPSUBSW,
    /* 344 */ VPSUBUSB,
    /* 345 */ VPSUBUSW,
    /* 346 */ VPSUBW,
    /* 347 */ VPTEST,
    /* 348 */ VPUNPCKHBW,
    /* 349 */ VPUNPCKHDQ,
    /* 34A */ VPUNPCKHQDQ,
    /* 34B */ VPUNPCKHWD,
    /* 34C */ VPUNPCKLBW,
    /* 34D */ VPUNPCKLDQ,
    /* 34E */ VPUNPCKLQDQ,
    /* 34F */ VPUNPCKLWD,
    /* 350 */ VPXOR,
    /* 351 */ VRCPPS,
    /* 352 */ VRCPSS,
    /* 353 */ VROUNDPD,
    /* 354 */ VROUNDPS,
    /* 355 */ VROUNDSD,
    /* 356 */ VROUNDSS,
    /* 357 */ VRSQRTPS,
    /* 358 */ VRSQRTSS,
    /* 359 */ VSHUFPD,
    /* 35A */ VSHUFPS,
    /* 35B */ VSQRTPD,
    /* 35C */ VSQRTPS,
    /* 35D */ VSQRTSD,
    /* 35E */ VSQRTSS,
    /* 35F */ VSTMXCSR,
    /* 360 */ VSUBPD,
    /* 361 */ VSUBPS,
    /* 362 */ VSUBSD,
    /* 363 */ VSUBSS,
    /* 364 */ VTESTPD,
    /* 365 */ VTESTPS,
    /* 366 */ VUCOMISD,
    /* 367 */ VUCOMISS,
    /* 368 */ VUNPCKHPD,
    /* 369 */ VUNPCKHPS,
    /* 36A */ VUNPCKLPD,
    /* 36B */ VUNPCKLPS,
    /* 36C */ VXORPD,
    /* 36D */ VXORPS,
    /* 36E */ VZEROALL,
    /* 36F */ VZEROUPPER,
    /* 370 */ WAIT,
    /* 371 */ WBINVD,
    /* 372 */ WRMSR,
    /* 373 */ XADD,
    /* 374 */ XCHG,
    /* 375 */ XCRYPTCBC,
    /* 376 */ XCRYPTCFB,
    /* 377 */ XCRYPTCTR,
    /* 378 */ XCRYPTECB,
    /* 379 */ XCRYPTOFB,
    /* 37A */ XGETBV,
    /* 37B */ XLATB,
    /* 37C */ XOR,
    /* 37D */ XORPD,
    /* 37E */ XORPS,
    /* 37F */ XRSTOR,
    /* 380 */ XSAVE,
    /* 381 */ XSETBV,
    /* 382 */ XSHA1,
    /* 383 */ XSHA256,
    /* 384 */ XSTORE,
};

/**
 * @brief   Defines an alias representing an opcode tree node. An opcode tree node is a 16 bit
 *          unsigned integer.
 *          The first 4 bits are reserved for the node type and the rest contains the actual value.
 *          In case of an instruction definition node, the 5th bit of the node (or the first bit
 *          of the value) is used to signal whether the modrm byte is used by the instruction.
 */
typedef uint16_t VXOpcodeTreeNode;

/**
 * @brief   Values that represent the type of an opcode tree node.
 */
enum class VXOpcodeTreeNodeType : uint8_t
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
enum class VXDefinedOperandType : uint8_t
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
 */
enum class VXDefinedOperandSize : uint8_t
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
enum VXInstructionDefinitionFlags : uint16_t
{
    IDF_ACCEPTS_REXB                    = 0x0001,
    IDF_ACCEPTS_REXX                    = 0x0002,
    IDF_ACCEPTS_REXR                    = 0x0004,
    IDF_ACCEPTS_REXW                    = 0x0008,
    IDF_ACCEPTS_ADDRESS_SIZE_OVERRIDE   = 0x0010,
    IDF_ACCEPTS_OPERAND_SIZE_OVERRIDE   = 0x0020,
    IDF_ACCEPTS_SEGMENT_OVERRIDE        = 0x0040,
    IDF_ACCEPTS_REP_PREFIX              = 0x0080,
    IDF_ACCEPTS_VEXL                    = 0x0100,
    IDF_INVALID_64                      = 0x0200,
    IDF_DEFAULT_64                      = 0x0400,
    IDF_ACCEPTS_LOCK_PREFIX             = 0x0800, // TODO:
    IDF_PRIVILEGED_INSTRUCTION          = 0x1000  // TODO:
};

#pragma pack (push, 1)
/**
 * @brief   An operand definition.
 */
struct VXOperandDefinition     
{                                  
    VXDefinedOperandType type;
    VXDefinedOperandSize size;
};
/**
 * @brief   An instruction definition.
 */
struct VXInstructionDefinition
{
    VXInstructionMnemonic mnemonic;
    VXOperandDefinition   operand[4];
    uint16_t              flags;   
};
#pragma pack (pop)

namespace Internal
{

/**
 * @brief   Contains all opcode tables.
 *          Indexed by the numeric value of the opcode.
 */
extern const VXOpcodeTreeNode optreeTable[][256];
/**
 * @brief   Contains all modrm_mod switch tables.
 *          Index values:
 *          0 = [modrm_mod == !11]
 *          1 = [modrm_mod ==  11]
 */
extern const VXOpcodeTreeNode optreeModrmMod[][2];
/**
 * @brief   Contains all modrm_reg switch tables.
 *          Indexed by the numeric value of the modrm_reg field.
 */
extern const VXOpcodeTreeNode optreeModrmReg[][8];
/**
 * @brief   Contains all modrm_rm switch tables.
 *          Indexed by the numeric value of the modrm_rm field.
 */
extern const VXOpcodeTreeNode optreeModrmRm[][8];
/**
 * @brief   Contains all mandatory-prefix switch tables.
 *          Index values:
 *          0 = none
 *          1 = F2  
 *          2 = F3  
 *          3 = 66
 */
extern const VXOpcodeTreeNode optreeMandatory[][4];
/**
 * @brief   Contains all x87 opcode tables.
 *          Indexed by the numeric value of the 6 lowest bits of the modrm byte (modrm_mod should
 *          always be 11). 
 */
extern const VXOpcodeTreeNode optreeX87[][64];
/**
 * @brief   Contains all address-size switch tables.
 *          Index values:
 *          0 = 16
 *          1 = 32  
 *          2 = 64
 */
extern const VXOpcodeTreeNode optreeAddressSize[][3];
/**
 * @brief   Contains all operand-size switch tables.
 *          Index values:
 *          0 = 16
 *          1 = 32  
 *          2 = 64
 */
extern const VXOpcodeTreeNode optreeOperandSize[][3];
/**
 * @brief   Contains all cpu-mode switch tables.
 *          Index values:
 *          0 = [!= 64]
 *          1 = 64
 */
extern const VXOpcodeTreeNode optreeMode[][2];
/**
 * @brief   Contains all vendor switch tables. 
 *          Index values:
 *          0 = AMD
 *          1 = Intel  
 */
extern const VXOpcodeTreeNode optreeVendor[][2];
/**
 * @brief   Contains all 3dnow! switch tables.
 *          Indexed by the numeric value of the 3dnow! opcode.
 */
extern const VXOpcodeTreeNode optree3dnow[][256];
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
extern const VXOpcodeTreeNode optreeVex[][16];
/**
 * @brief   Contains all vex_w switch tables.
 *          Indexed by the numeric value of the vex_w field.
 */
extern const VXOpcodeTreeNode optreeVexW[][2];
/**
 * @brief   Contains all vex_l switch tables.
 *          Indexed by the numeric value of the vex_l field.
 */
extern const VXOpcodeTreeNode optreeVexL[][2];
/**
 * @brief   Contains all instruction definitions.
 */
extern const VXInstructionDefinition instrDefinitions[];
/**
 * @brief   Contains all instruction mnemonic strings.
 */
extern const char* instrMnemonicStrings[];

/**
 * @brief   Returns the type of the specified opcode tree node.
 * @param   node    The node.
 * @return  The type of the specified opcode tree node.
 */
inline VXOpcodeTreeNodeType GetOpcodeNodeType(VXOpcodeTreeNode node)
{
    return static_cast<VXOpcodeTreeNodeType>((node >> 12) & 0x0F);
} 

/**
 * @brief   Returns the value of the specified opcode tree node.
 * @param   node    The node.
 * @return  The value of the specified opcode tree node.
 */
inline uint16_t GetOpcodeNodeValue(VXOpcodeTreeNode node)
{
    return (node & 0x0FFF);   
}

/**
 * @brief   Returns the root node of the opcode tree.
 * @return  The root node of the opcode tree.
 */
inline VXOpcodeTreeNode GetOpcodeTreeRoot()
{
    return 0x1000;
}

/**
 * @brief   Returns a child node of @c parent specified by @c index.
 * @param   parent  The parent node.
 * @param   index   The index of the child node to retrieve.
 * @return  The specified child node.
 */
inline VXOpcodeTreeNode GetOpcodeTreeChild(VXOpcodeTreeNode parent, uint16_t index)
{
    using namespace Internal;
    VXOpcodeTreeNodeType nodeType = GetOpcodeNodeType(parent);
    uint16_t tableIndex = GetOpcodeNodeValue(parent);
    switch (nodeType)
    {
    case VXOpcodeTreeNodeType::TABLE:
        assert(index < 256);
        return optreeTable[tableIndex][index];
    case VXOpcodeTreeNodeType::MODRM_MOD:
        assert(index < 2);
        return optreeModrmMod[tableIndex][index];
    case VXOpcodeTreeNodeType::MODRM_REG:
        assert(index < 8);
        return optreeModrmReg[tableIndex][index];
    case VXOpcodeTreeNodeType::MODRM_RM:
        assert(index < 8);
        return optreeModrmRm[tableIndex][index];
    case VXOpcodeTreeNodeType::MANDATORY:
        assert(index < 4);
        return optreeMandatory[tableIndex][index];
    case VXOpcodeTreeNodeType::X87:
        assert(index < 64);
        return optreeX87[tableIndex][index];
    case VXOpcodeTreeNodeType::ADDRESS_SIZE:
        assert(index < 3);
        return optreeAddressSize[tableIndex][index];
    case VXOpcodeTreeNodeType::OPERAND_SIZE:
        assert(index < 3);
        return optreeOperandSize[tableIndex][index];
    case VXOpcodeTreeNodeType::MODE:
        assert(index < 2);
        return optreeMode[tableIndex][index];
    case VXOpcodeTreeNodeType::VENDOR:
        assert(index < 3);
        return optreeVendor[tableIndex][index];
    case VXOpcodeTreeNodeType::AMD3DNOW:
        assert(index < 256);
        return optree3dnow[tableIndex][index];
    case VXOpcodeTreeNodeType::VEX:
        assert(index < 16);
        return optreeVex[tableIndex][index];
    case VXOpcodeTreeNodeType::VEXW:
        assert(index < 2);
        return optreeVexW[tableIndex][index];
    case VXOpcodeTreeNodeType::VEXL:
        assert(index < 2);
        return optreeVexL[tableIndex][index];
    default:
        assert(0);
    }
    return 0xFFFF;
}

/**
 * @brief   Returns the instruction definition that is linked to the given @c node.
 * @param   node        The instruction definition node.
 * @param   hasModrm    Signals whether the instruction uses the modrm byte.
 * @return  NULL if it fails, else the instruction definition.
 */
inline const VXInstructionDefinition* GetInstructionDefinition(VXOpcodeTreeNode node,
    bool &hasModrm)
{
    assert(GetOpcodeNodeType(node) == VXOpcodeTreeNodeType::INSTRUCTION_DEFINITION);
    hasModrm = ((node & 0x0800) == 0x800);
    return &instrDefinitions[node & 0x07FF];    
}

/**
 * @brief   Returns the instruction definition that is linked to the given @c node.
 * @param   node    The instruction definition node.
 * @return  NULL if it fails, else the instruction definition.
 */
inline const VXInstructionDefinition* GetInstructionDefinition(VXOpcodeTreeNode node)
{
    bool hasModrm = false;
    return GetInstructionDefinition(node, hasModrm);    
}

/**
 * @brief   Returns the specified instruction mnemonic string.
 * @param   mnemonic    The mnemonic.
 * @return  The instruction mnemonic string.
 */
inline const char* GetInstructionMnemonicString(VXInstructionMnemonic mnemonic)
{
    return instrMnemonicStrings[static_cast<uint16_t>(mnemonic)];
}

/**
 * @brief   Returns the memory size part of the complex operand size.
 * @param   operandSize The defined operand size.
 * @return  The defined memory operand size.
 */
inline VXDefinedOperandSize GetComplexOperandMemSize(VXDefinedOperandSize operandSize)
{
    return static_cast<VXDefinedOperandSize>(static_cast<uint8_t>(operandSize) & 0xF);
}

/**
 * @brief   Returns the register size part of the complex operand size.
 * @param   operandSize The defined operand size.
 * @return  The defined register operand size.
 */
inline VXDefinedOperandSize GetComplexOperandRegSize(VXDefinedOperandSize operandSize)
{
    return static_cast<VXDefinedOperandSize>((static_cast<uint8_t>(operandSize) >> 4) & 0xF);    
}

}

}

}
