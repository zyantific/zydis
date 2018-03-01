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

#include <Zydis/Internal/SharedData.h>

/* ============================================================================================== */
/* Data tables                                                                                    */
/* ============================================================================================== */

/* ---------------------------------------------------------------------------------------------- */
/* Forward declarations                                                                           */
/* ---------------------------------------------------------------------------------------------- */

/**
 * @brief   Contains all operand-definitions.
 */
extern const ZydisOperandDefinition operandDefinitions[];

/* ---------------------------------------------------------------------------------------------- */

/**
 * @brief   Contains all instruction-definitions with @c DEFAULT encoding.
 */
extern const ZydisInstructionDefinitionDEFAULT instructionDefinitionsDEFAULT[];

/**
 * @brief   Contains all instruction-definitions with @c 3DNOW encoding.
 */
extern const ZydisInstructionDefinition3DNOW instructionDefinitions3DNOW[];

/**
 * @brief   Contains all instruction-definitions with @c XOP encoding.
 */
extern const ZydisInstructionDefinitionXOP instructionDefinitionsXOP[];

/**
 * @brief   Contains all instruction-definitions with @c VEX encoding.
 */
extern const ZydisInstructionDefinitionVEX instructionDefinitionsVEX[];

#ifndef ZYDIS_DISABLE_EVEX
/**
 * @brief   Contains all instruction-definitions with @c EVEX encoding.
 */
extern const ZydisInstructionDefinitionEVEX instructionDefinitionsEVEX[];
#endif

#ifndef ZYDIS_DISABLE_MVEX
/**
 * @brief   Contains all instruction-definitions with @c MVEX encoding.
 */
extern const ZydisInstructionDefinitionMVEX instructionDefinitionsMVEX[];
#endif

/* ---------------------------------------------------------------------------------------------- */
/* Instruction definitions                                                                        */
/* ---------------------------------------------------------------------------------------------- */

#include <Generated/InstructionDefinitions.inc>

/* ---------------------------------------------------------------------------------------------- */
/* Operand definitions                                                                            */
/* ---------------------------------------------------------------------------------------------- */

#define ZYDIS_OPERAND_DEFINITION(type, encoding, access) \
    { type, encoding, access }

#include <Generated/OperandDefinitions.inc>

#undef ZYDIS_OPERAND_DEFINITION

/* ---------------------------------------------------------------------------------------------- */
/* Accessed CPU flags                                                                             */
/* ---------------------------------------------------------------------------------------------- */

#include <Generated/AccessedFlags.inc>

/* ---------------------------------------------------------------------------------------------- */

/* ============================================================================================== */
/* Functions                                                                                      */
/* ============================================================================================== */

/* ---------------------------------------------------------------------------------------------- */
/* Instruction definition                                                                         */
/* ---------------------------------------------------------------------------------------------- */

void ZydisGetInstructionDefinition(ZydisInstructionEncoding encoding, ZydisU16 id,
    const ZydisInstructionDefinition** definition)
{
    switch (encoding)
    {
    case ZYDIS_INSTRUCTION_ENCODING_DEFAULT:
        *definition = (ZydisInstructionDefinition*)&instructionDefinitionsDEFAULT[id];
        break;
    case ZYDIS_INSTRUCTION_ENCODING_3DNOW:
        *definition = (ZydisInstructionDefinition*)&instructionDefinitions3DNOW[id];
        break;
    case ZYDIS_INSTRUCTION_ENCODING_XOP:
        *definition = (ZydisInstructionDefinition*)&instructionDefinitionsXOP[id];
        break;
    case ZYDIS_INSTRUCTION_ENCODING_VEX:
        *definition = (ZydisInstructionDefinition*)&instructionDefinitionsVEX[id];
        break;
#ifndef ZYDIS_DISABLE_EVEX
    case ZYDIS_INSTRUCTION_ENCODING_EVEX:
        *definition = (ZydisInstructionDefinition*)&instructionDefinitionsEVEX[id];
        break;
#endif
#ifndef ZYDIS_DISABLE_MVEX
    case ZYDIS_INSTRUCTION_ENCODING_MVEX:
        *definition = (ZydisInstructionDefinition*)&instructionDefinitionsMVEX[id];
        break;
#endif
    default:
        ZYDIS_UNREACHABLE;
    }
}

/* ---------------------------------------------------------------------------------------------- */
/* Operand definition                                                                             */
/* ---------------------------------------------------------------------------------------------- */

ZydisU8 ZydisGetOperandDefinitions(const ZydisInstructionDefinition* definition,
    const ZydisOperandDefinition** operand)
{
    if (definition->operandCount == 0)
    {
        *operand = ZYDIS_NULL;
        return 0;
    }
    ZYDIS_ASSERT(definition->operandReference != 0xFFFF);
    *operand = &operandDefinitions[definition->operandReference];
    return definition->operandCount;
}

/* ---------------------------------------------------------------------------------------------- */
/* Element info                                                                                   */
/* ---------------------------------------------------------------------------------------------- */

void ZydisGetElementInfo(ZydisInternalElementType element, ZydisElementType* type,
    ZydisElementSize* size)
{
    static const struct
    {
        ZydisElementType type;
        ZydisElementSize size;
    } lookup[21] =
    {
        { ZYDIS_ELEMENT_TYPE_INVALID  ,   0 },
        { ZYDIS_ELEMENT_TYPE_INVALID  ,   0 },
        { ZYDIS_ELEMENT_TYPE_STRUCT   ,   0 },
        { ZYDIS_ELEMENT_TYPE_INT      ,   0 },
        { ZYDIS_ELEMENT_TYPE_UINT     ,   0 },
        { ZYDIS_ELEMENT_TYPE_INT      ,   1 },
        { ZYDIS_ELEMENT_TYPE_INT      ,   8 },
        { ZYDIS_ELEMENT_TYPE_INT      ,  16 },
        { ZYDIS_ELEMENT_TYPE_INT      ,  32 },
        { ZYDIS_ELEMENT_TYPE_INT      ,  64 },
        { ZYDIS_ELEMENT_TYPE_UINT     ,   8 },
        { ZYDIS_ELEMENT_TYPE_UINT     ,  16 },
        { ZYDIS_ELEMENT_TYPE_UINT     ,  32 },
        { ZYDIS_ELEMENT_TYPE_UINT     ,  64 },
        { ZYDIS_ELEMENT_TYPE_UINT     , 128 },
        { ZYDIS_ELEMENT_TYPE_UINT     , 256 },
        { ZYDIS_ELEMENT_TYPE_FLOAT16  ,  16 },
        { ZYDIS_ELEMENT_TYPE_FLOAT32  ,  32 },
        { ZYDIS_ELEMENT_TYPE_FLOAT64  ,  64 },
        { ZYDIS_ELEMENT_TYPE_FLOAT80  ,  80 },
        { ZYDIS_ELEMENT_TYPE_LONGBCD  ,  80 }
    };

    ZYDIS_ASSERT(element < ZYDIS_ARRAY_SIZE(lookup));

    *type = lookup[element].type;
    *size = lookup[element].size;
}

/* ---------------------------------------------------------------------------------------------- */
/* Accessed CPU flags                                                                             */
/* ---------------------------------------------------------------------------------------------- */

void ZydisGetAccessedFlags(const ZydisInstructionDefinition* definition,
    const ZydisAccessedFlags** flags)
{
    ZYDIS_ASSERT(definition->flagsReference < ZYDIS_ARRAY_SIZE(accessedFlags));
    *flags = &accessedFlags[definition->flagsReference];
}

/* ---------------------------------------------------------------------------------------------- */

/* ============================================================================================== */
