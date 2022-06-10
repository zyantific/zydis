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
 * Functions and types providing encoding information about individual instruction bytes.
 */

#ifndef ZYDIS_SEGMENT_H
#define ZYDIS_SEGMENT_H

#include <Zycore/Defines.h>
#include <Zydis/DecoderTypes.h>
#include <Zydis/Status.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
* @addtogroup segment Segment
* Functions and types providing encoding information about individual instruction bytes.
* @{
*/

/* ============================================================================================== */
/* Macros                                                                                         */
/* ============================================================================================== */

/* ---------------------------------------------------------------------------------------------- */
/* Constants                                                                                      */
/* ---------------------------------------------------------------------------------------------- */

#define ZYDIS_MAX_INSTRUCTION_SEGMENT_COUNT 9

/* ---------------------------------------------------------------------------------------------- */

/* ============================================================================================== */
/* Types                                                                                          */
/* ============================================================================================== */

/* ---------------------------------------------------------------------------------------------- */
/* Structs for each segment kind                                                                  */
/* ---------------------------------------------------------------------------------------------- */

/**
 * This instruction segment doesn't have individual bits to be decoded.
 */
typedef struct ZydisInstructionSegmentNoBits_
{
    /**
     * The C standard doesn't permit empty structs, so we need to add a one byte dummy member.
     */
    ZyanU8 dummy;
} ZydisInstructionSegmentNoBits;

/**
 * The `REX` prefix, decoded into individual bit-fields.
 */
typedef struct ZydisInstructionSegmentREX_
{
    /**
     * 64-bit operand-size promotion.
     */
    ZyanU8 W;
    /**
     * Extension of the `ModRM.reg` field.
     */
    ZyanU8 R;
    /**
     * Extension of the `SIB.index` field.
     */
    ZyanU8 X;
    /**
     * Extension of the `ModRM.rm`, `SIB.base`, or `opcode.reg` field.
     */
    ZyanU8 B;
} ZydisInstructionSegmentREX;

/**
 * The `VEX` prefix, decoded into individual bit-fields.
 */
typedef struct ZydisInstructionSegmentVEX_
{
    /**
     * Extension of the `ModRM.reg` field (inverted).
     */
    ZyanU8 R;
    /**
     * Extension of the `SIB.index` field (inverted).
     */
    ZyanU8 X;
    /**
     * Extension of the `ModRM.rm`, `SIB.base`, or `opcode.reg` field (inverted).
     */
    ZyanU8 B;
    /**
     * Opcode-map specifier.
     */
    ZyanU8 m_mmmm;
    /**
     * 64-bit operand-size promotion or opcode-extension.
     */
    ZyanU8 W;
    /**
     * `NDS`/`NDD` (non-destructive-source/destination) register specifier
     *  (inverted).
     */
    ZyanU8 vvvv;
    /**
     * Vector-length specifier.
     */
    ZyanU8 L;
    /**
     * Compressed legacy prefix.
     */
    ZyanU8 pp;
} ZydisInstructionSegmentVEX;

/**
 * The `XOP` prefix, decoded into individual bit-fields.
 */
typedef struct ZydisInstructionSegmentXOP_
{
    /**
     * Extension of the `ModRM.reg` field (inverted).
     */
    ZyanU8 R;
    /**
     * Extension of the `SIB.index` field (inverted).
     */
    ZyanU8 X;
    /**
     * Extension of the `ModRM.rm`, `SIB.base`, or `opcode.reg` field (inverted).
     */
    ZyanU8 B;
    /**
     * Opcode-map specifier.
     */
    ZyanU8 m_mmmm;
    /**
     * 64-bit operand-size promotion or opcode-extension.
     */
    ZyanU8 W;
    /**
     * `NDS`/`NDD` (non-destructive-source/destination) register
     * specifier (inverted).
     */
    ZyanU8 vvvv;
    /**
     * Vector-length specifier.
     */
    ZyanU8 L;
    /**
     * Compressed legacy prefix.
     */
    ZyanU8 pp;
} ZydisInstructionSegmentXOP;

/**
 * The `EVEX` prefix, decoded into individual bit-fields.
 */
typedef struct ZydisInstructionSegmentEVEX_
{
    /**
     * Extension of the `ModRM.reg` field (inverted).
     */
    ZyanU8 R;
    /**
     * Extension of the `SIB.index/vidx` field (inverted).
     */
    ZyanU8 X;
    /**
     * Extension of the `ModRM.rm` or `SIB.base` field (inverted).
     */
    ZyanU8 B;
    /**
     * High-16 register specifier modifier (inverted).
     */
    ZyanU8 R2;
    /**
     * Opcode-map specifier.
     */
    ZyanU8 mmm;
    /**
     * 64-bit operand-size promotion or opcode-extension.
     */
    ZyanU8 W;
    /**
     * `NDS`/`NDD` (non-destructive-source/destination) register specifier
     * (inverted).
     */
    ZyanU8 vvvv;
    /**
     * Compressed legacy prefix.
     */
    ZyanU8 pp;
    /**
     * Zeroing/Merging.
     */
    ZyanU8 z;
    /**
     * Vector-length specifier or rounding-control (most significant bit).
     */
    ZyanU8 L2;
    /**
     * Vector-length specifier or rounding-control (least significant bit).
     */
    ZyanU8 L;
    /**
     * Broadcast/RC/SAE context.
     */
    ZyanU8 b;
    /**
     * High-16 `NDS`/`VIDX` register specifier.
     */
    ZyanU8 V2;
    /**
     * Embedded opmask register specifier.
     */
    ZyanU8 aaa;
} ZydisInstructionSegmentEVEX;

/**
 * The `MVEX` prefix, decoded into individual bit-fields.
 */
typedef struct ZydisInstructionSegmentMVEX_
{
    /**
     * Extension of the `ModRM.reg` field (inverted).
     */
    ZyanU8 R;
    /**
     * Extension of the `SIB.index/vidx` field (inverted).
     */
    ZyanU8 X;
    /**
     * Extension of the `ModRM.rm` or `SIB.base` field (inverted).
     */
    ZyanU8 B;
    /**
     * High-16 register specifier modifier (inverted).
     */
    ZyanU8 R2;
    /**
     * Opcode-map specifier.
     */
    ZyanU8 mmmm;
    /**
     * 64-bit operand-size promotion or opcode-extension.
     */
    ZyanU8 W;
    /**
     * `NDS`/`NDD` (non-destructive-source/destination) register specifier
     *  (inverted).
     */
    ZyanU8 vvvv;
    /**
     * Compressed legacy prefix.
     */
    ZyanU8 pp;
    /**
     * Non-temporal/eviction hint.
     */
    ZyanU8 E;
    /**
     * Swizzle/broadcast/up-convert/down-convert/static-rounding controls.
     */
    ZyanU8 SSS;
    /**
     * High-16 `NDS`/`VIDX` register specifier.
     */
    ZyanU8 V2;
    /**
     * Embedded opmask register specifier.
     */
    ZyanU8 kkk;
} ZydisInstructionSegmentMVEX;

/**
 * The `ModRM` prefix, decoded into individual bit-fields.
 */
typedef struct ZydisInstructionSegmentModRM_
{
    /**
     * The addressing mode.
     */
    ZyanU8 mod;
    /**
     * Register specifier or opcode-extension.
     */
    ZyanU8 reg;
    /**
     * Register specifier or opcode-extension.
     */
    ZyanU8 rm;
} ZydisInstructionSegmentModRM;

/**
 * The `SIB` prefix, decoded into individual bit-fields.
 */
typedef struct ZydisInstructionSegmentSIB_
{
    /**
     * The scale factor.
     */
    ZyanU8 scale;
    /**
     * The index-register specifier.
     */
    ZyanU8 index;
    /**
     * The base-register specifier.
     */
    ZyanU8 base;
} ZydisInstructionSegmentSIB;

/* ---------------------------------------------------------------------------------------------- */
/* Types for ZydisGetInstructionSegments                                                          */
/* ---------------------------------------------------------------------------------------------- */

/**
 * Determines the kind of an instruction segment.
 */
typedef enum ZydisInstructionSegmentKind_
{
    ZYDIS_INSTR_SEGMENT_NONE,
    /**
     * The legacy prefixes (including ignored `REX` prefixes).
     */
    ZYDIS_INSTR_SEGMENT_PREFIXES,
    /**
     * The effective `REX` prefix byte.
     */
    ZYDIS_INSTR_SEGMENT_REX,
    /**
     * The `XOP` prefix bytes.
     */
    ZYDIS_INSTR_SEGMENT_XOP,
    /**
     * The `VEX` prefix bytes.
     */
    ZYDIS_INSTR_SEGMENT_VEX,
    /**
     * The `EVEX` prefix bytes.
     */
    ZYDIS_INSTR_SEGMENT_EVEX,
    /**
     * The `MVEX` prefix bytes.
     */
    ZYDIS_INSTR_SEGMENT_MVEX,
    /**
     * The opcode bytes.
     */
    ZYDIS_INSTR_SEGMENT_OPCODE,
    /**
     * The `ModRM` byte.
     */
    ZYDIS_INSTR_SEGMENT_MODRM,
    /**
     * The `SIB` byte.
     */
    ZYDIS_INSTR_SEGMENT_SIB,
    /**
     * The displacement bytes.
     */
    ZYDIS_INSTR_SEGMENT_DISPLACEMENT,
    /**
     * The immediate bytes.
     */
    ZYDIS_INSTR_SEGMENT_IMMEDIATE,

    /**
     * Maximum value of this enum.
     */
    ZYDIS_INSTR_SEGMENT_MAX_VALUE = ZYDIS_INSTR_SEGMENT_IMMEDIATE,
    /**
     * The minimum number of bits required to represent all values of this enum.
     */
    ZYDIS_INSTR_SEGMENT_REQUIRED_BITS = ZYAN_BITS_TO_REPRESENT(ZYDIS_INSTR_SEGMENT_MAX_VALUE)
} ZydisInstructionSegmentKind;

/**
 * Information about an individual instruction segment.
 */
typedef struct ZydisInstructionSegment_
{
    /**
     * The offset of the segment relative to the start of the instruction (in bytes).
     */
    ZyanU8 offset;
    /**
     * The size of the segment, in bytes.
     */
    ZyanU8 size;
    /**
     * The type of the segment.
     */
    ZydisInstructionSegmentKind type;
    /**
     * The individual bits of the segment, decoded into a struct.
     *
     * The active union variant is determined by the preceding `type` field.
     */
    union {
        ZydisInstructionSegmentNoBits prefix;
        ZydisInstructionSegmentREX rex;
        ZydisInstructionSegmentVEX vex;
        ZydisInstructionSegmentXOP xop;
        ZydisInstructionSegmentEVEX evex;
        ZydisInstructionSegmentMVEX mvex;
        ZydisInstructionSegmentNoBits opcode;
        ZydisInstructionSegmentModRM modrm;
        ZydisInstructionSegmentSIB sib;
        ZydisInstructionSegmentNoBits disp;
        ZydisInstructionSegmentNoBits imm;
    };
} ZydisInstructionSegment;

/**
 * Container for instruction segments.
 */
typedef struct ZydisInstructionSegments_
{
    /**
     * The number of logical instruction segments.
     */
    ZyanU8 count;
    /**
     * The information about each individual segment.
     */
    ZydisInstructionSegment segments[ZYDIS_MAX_INSTRUCTION_SEGMENT_COUNT];
} ZydisInstructionSegments;

/* ---------------------------------------------------------------------------------------------- */
/* Types for ZydisGetInstructionSegments                                                          */
/* ---------------------------------------------------------------------------------------------- */

typedef struct ZydisInstructionSegmentReflectionInfo_ {
    /**
     * Name of the struct field.
     */
    const char* field_name;
    /**
     * Bit width of the field.
     *
     * `0` means that the field is "virtual" (not actually read from the prefix).
     */
    ZyanU8 bit_width;
    /**
     * Where to find the value for this field of the segment.
     *
     * The active variant is determined by whether `bit_width` is `0` (`constant`) or not
     * (`bit_offset`).
     */
    union {
        /**
         * The field is virtual and the value is always `constant`.
         */
        ZyanU8 constant;
        /**
         * The value lives at bit offset within the segment (0..=31).
         */
        ZyanU8 bit_offset;
    } value_source;
    /**
     * Struct offset in the active union variant of `ZydisInstructionSegment`.
     */
    ZyanU8 struct_offset;
} ZydisInstructionSegmentReflectionInfo;

/* ============================================================================================== */
/* Exported functions                                                                             */
/* ============================================================================================== */

/**
 * Returns information about logical instruction segments (e.g. `OPCODE`, `MODRM`, ...).
 *
 * @param   instruction The instruction to create segments for.
 * @param   buffer      A pointer to the raw instruction bytes.
 * @param   length      The length of the buffer passed in `buffer`. Must be at least
 *                      `instruction.length`.
 * @param   segments    Receives the instruction segments information.
 *
 * @return  A zyan status code.
 */
ZYDIS_EXPORT ZyanStatus ZydisGetInstructionSegments(const ZydisDecodedInstruction* instruction,
    const ZyanU8* buffer, ZyanUSize length, ZydisInstructionSegments* segments);

/**
 * Return reflection information for the segment bit structure of a given kind.
 *
 * @param   kind    The segment kind to retrieve information for.
 * @param   length  The length of the instruction segment.
 *
 * @return  The reflection info, or `ZYAN_NULL` for invalid segment kinds.
 */
ZYDIS_EXPORT const ZydisInstructionSegmentReflectionInfo* ZydisSegmentGetReflectionInfo(
    ZydisInstructionSegmentKind kind, ZyanU8 length);

/**
 * Return the string representation for a segment kind.
 *
 * @param kind  The kind to get the string for.
 *
 * @return The segment kind as a string, or `ZYAN_NULL` for invalid values.
 */
ZYDIS_EXPORT const char* ZydisSegmentKindGetString(ZydisInstructionSegmentKind kind);

/* ============================================================================================== */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* ZYDIS_SEGMENT_H */
