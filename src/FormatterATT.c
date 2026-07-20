/***************************************************************************************************

  Zyan Disassembler Library (Zydis)

  Original Author : Florian Bernd, Joel Hoener

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

#include <Zydis/Internal/FormatterATT.h>

/* ============================================================================================== */
/* Constants                                                                                      */
/* ============================================================================================== */

#include <Generated/FormatterStrings.inc>

static const ZydisShortString STR_SIZE_SHORT_ATT = ZYDIS_MAKE_SHORTSTRING("s");
static const ZydisShortString STR_SIZE_EXTENDED_ATT = ZYDIS_MAKE_SHORTSTRING("t");
static const ZydisShortString STR_SIZE_LONG_LONG_ATT = ZYDIS_MAKE_SHORTSTRING("ll");

/* ============================================================================================== */
/* Formatter functions                                                                            */
/* ============================================================================================== */

/* ---------------------------------------------------------------------------------------------- */
/* Instruction                                                                                    */
/* ---------------------------------------------------------------------------------------------- */

ZyanStatus ZydisFormatterATTFormatInstruction(const ZydisFormatter* formatter,
    ZydisFormatterBuffer* buffer, ZydisFormatterContext* context)
{
    ZYAN_ASSERT(formatter);
    ZYAN_ASSERT(buffer);
    ZYAN_ASSERT(context);
    ZYAN_ASSERT(context->instruction);
    ZYAN_ASSERT(context->operands);

    if (!formatter->deco_apx_nf_use_suffix)
    {
        ZYAN_CHECK(formatter->func_print_decorator(formatter, buffer, context, ZYDIS_DECORATOR_APX_NF));
    }

    ZYAN_CHECK(formatter->func_print_prefixes(formatter, buffer, context));
    ZYAN_CHECK(formatter->func_print_mnemonic(formatter, buffer, context));
    
    if (!formatter->deco_apx_dfv_use_immediate)
    {
        ZYAN_CHECK(formatter->func_print_decorator(formatter, buffer, context, ZYDIS_DECORATOR_APX_DFV));
    }

    ZyanUPointer state_mnemonic;
    ZYDIS_BUFFER_REMEMBER(buffer, state_mnemonic);

    if (formatter->deco_apx_dfv_use_immediate && (context->instruction->apx.scc != ZYDIS_SCC_NONE))
    {
        ZYDIS_BUFFER_APPEND(buffer, DELIM_MNEMONIC);
        ZYDIS_BUFFER_APPEND_TOKEN(buffer, ZYDIS_TOKEN_IMMEDIATE);
        ZYDIS_BUFFER_APPEND(buffer, IMMEDIATE);
        ZYAN_CHECK(ZydisStringAppendDecU(&buffer->string,
            context->instruction->apx.default_flags, 0,
            formatter->number_format[ZYDIS_NUMERIC_BASE_DEC][0].string,
            formatter->number_format[ZYDIS_NUMERIC_BASE_DEC][1].string));
    }

    const ZyanI8 c = (ZyanI8)context->instruction->operand_count_visible - 1;
    for (ZyanI8 i = c; i >= 0; --i)
    {
        const ZydisDecodedOperand* const operand = &context->operands[i];

        // Print embedded-mask registers as decorator instead of a regular operand
        if ((i == 1) && (operand->type == ZYDIS_OPERAND_TYPE_REGISTER) &&
            (operand->encoding == ZYDIS_OPERAND_ENCODING_MASK))
        {
            continue;
        }

        ZyanUPointer buffer_state;
        ZYDIS_BUFFER_REMEMBER(buffer, buffer_state);

        if (buffer_state != state_mnemonic)
        {
            ZYDIS_BUFFER_APPEND(buffer, DELIM_OPERAND);
        } else
        {
            ZYDIS_BUFFER_APPEND(buffer, DELIM_MNEMONIC);
        }

        // Set current operand
        context->operand = operand;

        ZyanStatus status;
        if (formatter->func_pre_operand)
        {
            status = formatter->func_pre_operand(formatter, buffer, context);
            if (status == ZYDIS_STATUS_SKIP_TOKEN)
            {
                ZYAN_CHECK(ZydisFormatterBufferRestore(buffer, buffer_state));
                continue;
            }
            if (!ZYAN_SUCCESS(status))
            {
                return status;
            }
        }

        switch (operand->type)
        {
        case ZYDIS_OPERAND_TYPE_REGISTER:
            status = formatter->func_format_operand_reg(formatter, buffer, context);
            break;
        case ZYDIS_OPERAND_TYPE_MEMORY:
            status = formatter->func_format_operand_mem(formatter, buffer, context);
            break;
        case ZYDIS_OPERAND_TYPE_POINTER:
            status = formatter->func_format_operand_ptr(formatter, buffer, context);
            break;
        case ZYDIS_OPERAND_TYPE_IMMEDIATE:
            status = formatter->func_format_operand_imm(formatter, buffer, context);
            break;
        default:
            return ZYAN_STATUS_INVALID_ARGUMENT;
        }
        if (status == ZYDIS_STATUS_SKIP_TOKEN)
        {
            ZYAN_CHECK(ZydisFormatterBufferRestore(buffer, buffer_state));
            continue;
        }
        if (!ZYAN_SUCCESS(status))
        {
            return status;
        }

        if (formatter->func_post_operand)
        {
            status = formatter->func_post_operand(formatter, buffer, context);
            if (status == ZYDIS_STATUS_SKIP_TOKEN)
            {
                ZYAN_CHECK(ZydisFormatterBufferRestore(buffer, buffer_state));
                continue;
            }
            if (!ZYAN_SUCCESS(status))
            {
                return status;
            }
        }

#if !defined(ZYDIS_DISABLE_AVX512) || !defined(ZYDIS_DISABLE_KNC)
        if ((context->instruction->encoding == ZYDIS_INSTRUCTION_ENCODING_EVEX) ||
            (context->instruction->encoding == ZYDIS_INSTRUCTION_ENCODING_MVEX))
        {
            if  ((i == 0) && 
                (context->instruction->operand_count_visible > 1) && 
                (context->operands[1].encoding == ZYDIS_OPERAND_ENCODING_MASK))
            {
                ZYAN_CHECK(formatter->func_print_decorator(formatter, buffer, context,
                    ZYDIS_DECORATOR_MASK));
            }
            if (operand->type == ZYDIS_OPERAND_TYPE_MEMORY)
            {
                ZYAN_CHECK(formatter->func_print_decorator(formatter, buffer, context,
                    ZYDIS_DECORATOR_BC));
                if (context->instruction->encoding == ZYDIS_INSTRUCTION_ENCODING_MVEX)
                {
                    ZYAN_CHECK(formatter->func_print_decorator(formatter, buffer, context,
                        ZYDIS_DECORATOR_CONVERSION));
                    ZYAN_CHECK(formatter->func_print_decorator(formatter, buffer, context,
                        ZYDIS_DECORATOR_EH));
                }
            } else
            {
                ZyanBool decorate_operand;
                if (i == (context->instruction->operand_count_visible - 1))
                {
                    decorate_operand = operand->type != ZYDIS_OPERAND_TYPE_IMMEDIATE;
                }
                else
                {
                    decorate_operand =
                        (context->instruction->operand_count_visible > (i + 1)) &&
                        ((context->operands[i + 1].type == ZYDIS_OPERAND_TYPE_IMMEDIATE) ||
                        (context->operands[i + 1].visibility == ZYDIS_OPERAND_VISIBILITY_HIDDEN));
                }
                if (decorate_operand)
                {
                    if (context->instruction->encoding == ZYDIS_INSTRUCTION_ENCODING_MVEX)
                    {
                        ZYAN_CHECK(formatter->func_print_decorator(formatter, buffer, context,
                            ZYDIS_DECORATOR_SWIZZLE));
                    }
                    ZYAN_CHECK(formatter->func_print_decorator(formatter, buffer, context,
                        ZYDIS_DECORATOR_RC));
                    ZYAN_CHECK(formatter->func_print_decorator(formatter, buffer, context,
                        ZYDIS_DECORATOR_SAE));
                }
            }
        }
#endif
    }

    return ZYAN_STATUS_SUCCESS;
}

/* ---------------------------------------------------------------------------------------------- */
/* Operands                                                                                       */
/* ---------------------------------------------------------------------------------------------- */

ZyanStatus ZydisFormatterATTFormatOperandREG(const ZydisFormatter* formatter,
    ZydisFormatterBuffer* buffer, ZydisFormatterContext* context)
{
    ZYAN_ASSERT(formatter);
    ZYAN_ASSERT(buffer);
    ZYAN_ASSERT(context);

    // A `ModRM.rm` register operand of a near branch is an indirect target (e.g. `call *%rax`)
    // and, like the memory-operand form, has to carry the leading `*` in AT&T syntax. Other
    // register operands of a branch (such as the mask register of `jkzd`) are not the target and
    // keep no marker.
    if ((context->instruction->meta.branch_type != ZYDIS_BRANCH_TYPE_NONE) &&
        (context->operand->encoding == ZYDIS_OPERAND_ENCODING_MODRM_RM))
    {
        ZYDIS_BUFFER_APPEND(buffer, MUL);
    }

    return formatter->func_print_register(formatter, buffer, context,
        context->operand->reg.value);
}

ZyanStatus ZydisFormatterATTFormatOperandMEM(const ZydisFormatter* formatter,
    ZydisFormatterBuffer* buffer, ZydisFormatterContext* context)
{
    ZYAN_ASSERT(formatter);
    ZYAN_ASSERT(buffer);
    ZYAN_ASSERT(context);

    // AT&T marks indirect near/far branches with a leading `*`, regardless of whether the
    // target operand is rendered as an absolute address or as a base/index expression.
    if (context->instruction->meta.branch_type != ZYDIS_BRANCH_TYPE_NONE)
    {
        ZYDIS_BUFFER_APPEND(buffer, MUL);
    }

    ZYAN_CHECK(formatter->func_print_segment(formatter, buffer, context));

    const ZyanBool absolute = !formatter->force_relative_riprel &&
        (context->runtime_address != ZYDIS_RUNTIME_ADDRESS_NONE);
    if (absolute && context->operand->mem.disp.size &&
        (context->operand->mem.index == ZYDIS_REGISTER_NONE) &&
       ((context->operand->mem.base  == ZYDIS_REGISTER_NONE) ||
        (context->operand->mem.base  == ZYDIS_REGISTER_EIP ) ||
        (context->operand->mem.base  == ZYDIS_REGISTER_RIP )))
    {
        // EIP/RIP-relative or absolute-displacement address operand
        ZYAN_CHECK(formatter->func_print_address_abs(formatter, buffer, context));
    } else
    {
        const ZyanBool should_print_reg = context->operand->mem.base != ZYDIS_REGISTER_NONE;
        const ZyanBool should_print_idx = context->operand->mem.index != ZYDIS_REGISTER_NONE;
        const ZyanBool neither_reg_nor_idx = !should_print_reg && !should_print_idx;

        // Regular memory operand
        if (neither_reg_nor_idx)
        {
            ZYAN_CHECK(formatter->func_print_address_abs(formatter, buffer, context));
        } else if (context->operand->mem.disp.size && context->operand->mem.disp.value)
        {
            ZYAN_CHECK(formatter->func_print_disp(formatter, buffer, context));
        }

        if (neither_reg_nor_idx)
        {
            return ZYAN_STATUS_SUCCESS;
        }

        ZYDIS_BUFFER_APPEND(buffer, MEMORY_BEGIN_ATT);

        if (should_print_reg)
        {
            ZYAN_CHECK(formatter->func_print_register(formatter, buffer, context,
                context->operand->mem.base));
        }
        if (should_print_idx)
        {
            ZYDIS_BUFFER_APPEND(buffer, DELIM_MEMORY);
            ZYAN_CHECK(formatter->func_print_register(formatter, buffer, context,
                context->operand->mem.index));
            if (context->operand->mem.scale &&
                (context->operand->mem.type != ZYDIS_MEMOP_TYPE_MIB) &&
                ((context->operand->mem.scale > 1) || formatter->force_memory_scale))
            {
                ZYDIS_BUFFER_APPEND_TOKEN(buffer, ZYDIS_TOKEN_DELIMITER);
                ZYDIS_BUFFER_APPEND(buffer, DELIM_MEMORY);
                ZYDIS_BUFFER_APPEND_TOKEN(buffer, ZYDIS_TOKEN_IMMEDIATE);
                ZYAN_CHECK(ZydisStringAppendDecU(&buffer->string, context->operand->mem.scale, 0,
                    ZYAN_NULL, ZYAN_NULL));
            }
        }

        ZYDIS_BUFFER_APPEND(buffer, MEMORY_END_ATT);
        return ZYAN_STATUS_SUCCESS;
    }

    return ZYAN_STATUS_SUCCESS;
}

/* ---------------------------------------------------------------------------------------------- */
/* Elemental tokens                                                                               */
/* ---------------------------------------------------------------------------------------------- */

static const ZydisShortString* ZydisFormatterATTGetSizeSuffix(ZyanU32 size)
{
    switch (size)
    {
    case   8: return &STR_SIZE_8_ATT;
    case  16: return &STR_SIZE_16_ATT;
    case  32: return &STR_SIZE_32_ATT;
    case  64: return &STR_SIZE_64_ATT;
    case 128: return &STR_SIZE_128_ATT;
    case 256: return &STR_SIZE_256_ATT;
    case 512: return &STR_SIZE_512_ATT;
    default: return ZYAN_NULL;
    }
}

static const ZydisShortString* ZydisFormatterATTGetMnemonicSuffix(
    const ZydisFormatter* formatter, ZydisFormatterContext* context)
{
    ZYAN_ASSERT(formatter);
    ZYAN_ASSERT(context);
    ZYAN_ASSERT(context->instruction);
    ZYAN_ASSERT(context->operands);

    const ZydisDecodedInstruction* const instruction = context->instruction;
    const ZydisDecodedOperand* memory_operand = ZYAN_NULL;
    for (ZyanU8 i = 0; i < instruction->operand_count_visible; ++i)
    {
        const ZydisDecodedOperand* const operand = &context->operands[i];
        if ((operand->type == ZYDIS_OPERAND_TYPE_MEMORY) &&
            (operand->mem.type == ZYDIS_MEMOP_TYPE_MEM))
        {
            memory_operand = operand;
            break;
        }
    }

    if (memory_operand)
    {
        switch (instruction->mnemonic)
        {
        case ZYDIS_MNEMONIC_FADD:
        case ZYDIS_MNEMONIC_FCOM:
        case ZYDIS_MNEMONIC_FCOMP:
        case ZYDIS_MNEMONIC_FDIV:
        case ZYDIS_MNEMONIC_FDIVR:
        case ZYDIS_MNEMONIC_FLD:
        case ZYDIS_MNEMONIC_FMUL:
        case ZYDIS_MNEMONIC_FST:
        case ZYDIS_MNEMONIC_FSTP:
        case ZYDIS_MNEMONIC_FSUB:
        case ZYDIS_MNEMONIC_FSUBR:
            switch (memory_operand->size)
            {
            case 32: return &STR_SIZE_SHORT_ATT;
            case 64: return &STR_SIZE_32_ATT;
            case 80: return &STR_SIZE_EXTENDED_ATT;
            default: return ZYAN_NULL;
            }
        case ZYDIS_MNEMONIC_FIADD:
        case ZYDIS_MNEMONIC_FICOM:
        case ZYDIS_MNEMONIC_FICOMP:
        case ZYDIS_MNEMONIC_FIDIV:
        case ZYDIS_MNEMONIC_FIDIVR:
        case ZYDIS_MNEMONIC_FILD:
        case ZYDIS_MNEMONIC_FIMUL:
        case ZYDIS_MNEMONIC_FIST:
        case ZYDIS_MNEMONIC_FISTP:
        case ZYDIS_MNEMONIC_FISTTP:
        case ZYDIS_MNEMONIC_FISUB:
        case ZYDIS_MNEMONIC_FISUBR:
            switch (memory_operand->size)
            {
            case 16: return &STR_SIZE_SHORT_ATT;
            case 32: return &STR_SIZE_32_ATT;
            case 64: return &STR_SIZE_LONG_LONG_ATT;
            default: return ZYAN_NULL;
            }
        case ZYDIS_MNEMONIC_FLDENV:
        case ZYDIS_MNEMONIC_FNSAVE:
        case ZYDIS_MNEMONIC_FNSTENV:
        case ZYDIS_MNEMONIC_FRSTOR:
            switch (memory_operand->size)
            {
            case 112:
            case 752:
                return &STR_SIZE_SHORT_ATT;
            case 224:
            case 864:
                return &STR_SIZE_32_ATT;
            default: return ZYAN_NULL;
            }
        default:
            break;
        }

        // The remaining x87 memory instructions have a fixed operand size encoded by their
        // mnemonic. Applying the generic suffix mapping to them would produce invalid names such
        // as `fldcww`.
        if (instruction->meta.category == ZYDIS_CATEGORY_X87_ALU)
        {
            return ZYAN_NULL;
        }

        if (instruction->operand_count_visible == 1)
        {
            switch (instruction->mnemonic)
            {
            case ZYDIS_MNEMONIC_CALL:
            case ZYDIS_MNEMONIC_JMP:
            case ZYDIS_MNEMONIC_POP:
            case ZYDIS_MNEMONIC_PUSH:
                return ZydisFormatterATTGetSizeSuffix(instruction->operand_width);
            case ZYDIS_MNEMONIC_DEC:
            case ZYDIS_MNEMONIC_DIV:
            case ZYDIS_MNEMONIC_IDIV:
            case ZYDIS_MNEMONIC_IMUL:
            case ZYDIS_MNEMONIC_INC:
            case ZYDIS_MNEMONIC_MUL:
            case ZYDIS_MNEMONIC_NEG:
            case ZYDIS_MNEMONIC_NOP:
            case ZYDIS_MNEMONIC_NOT:
            case ZYDIS_MNEMONIC_PTWRITE:
                return ZydisFormatterATTGetSizeSuffix(memory_operand->size);
            default:
                break;
            }
        }

        switch (instruction->mnemonic)
        {
        case ZYDIS_MNEMONIC_LGDT:
        case ZYDIS_MNEMONIC_LIDT:
        case ZYDIS_MNEMONIC_SGDT:
        case ZYDIS_MNEMONIC_SIDT:
            if (instruction->machine_mode != ZYDIS_MACHINE_MODE_LONG_64)
            {
                return ZydisFormatterATTGetSizeSuffix(instruction->operand_width);
            }
            return ZYAN_NULL;
        default:
            break;
        }

        if (formatter->force_memory_size)
        {
            switch (instruction->mnemonic)
            {
            case ZYDIS_MNEMONIC_LKGS:
            case ZYDIS_MNEMONIC_LLDT:
            case ZYDIS_MNEMONIC_LMSW:
            case ZYDIS_MNEMONIC_LTR:
            case ZYDIS_MNEMONIC_SLDT:
            case ZYDIS_MNEMONIC_SMSW:
            case ZYDIS_MNEMONIC_STR:
            case ZYDIS_MNEMONIC_VERR:
            case ZYDIS_MNEMONIC_VERW:
                return &STR_SIZE_16_ATT;
            default:
                break;
            }
        }

        // All single-memory mnemonics that accept a size suffix are handled above. The remaining
        // instructions have a fixed size encoded by their mnemonic or instruction semantics. This
        // also prevents FORCE_SIZE from creating unsupported or non-canonical names such as
        // `clflushz` or `setbb`.
        if (instruction->operand_count_visible == 1)
        {
            return ZYAN_NULL;
        }

        const ZyanU32 size = ZydisFormatterHelperGetExplicitSize(formatter, context,
            memory_operand);
        if (size)
        {
            return ZydisFormatterATTGetSizeSuffix(size);
        }
    }

    switch (instruction->mnemonic)
    {
    case ZYDIS_MNEMONIC_CALL:
        if ((instruction->operand_count_visible == 1) &&
            (context->operands[0].type == ZYDIS_OPERAND_TYPE_REGISTER))
        {
            return ZYAN_NULL;
        }
        return ZydisFormatterATTGetSizeSuffix(instruction->operand_width);
    case ZYDIS_MNEMONIC_JMP:
        if ((instruction->meta.branch_type == ZYDIS_BRANCH_TYPE_SHORT) ||
            ((instruction->operand_count_visible == 1) &&
             (context->operands[0].type == ZYDIS_OPERAND_TYPE_REGISTER)))
        {
            return ZYAN_NULL;
        }
        return ZydisFormatterATTGetSizeSuffix(instruction->operand_width);
    case ZYDIS_MNEMONIC_PUSH:
        if ((instruction->operand_count_visible == 1) &&
            (context->operands[0].type == ZYDIS_OPERAND_TYPE_IMMEDIATE))
        {
            return ZydisFormatterATTGetSizeSuffix(instruction->operand_width);
        }
        return ZYAN_NULL;
    case ZYDIS_MNEMONIC_ENTER:
    case ZYDIS_MNEMONIC_LEAVE:
    case ZYDIS_MNEMONIC_RET:
        return ZydisFormatterATTGetSizeSuffix(instruction->operand_width);
    case ZYDIS_MNEMONIC_SYSEXIT:
    case ZYDIS_MNEMONIC_SYSRET:
        // These instructions only have 32-bit and 64-bit forms. An operand-size override does not
        // turn the 32-bit form into a 16-bit instruction.
        return (instruction->operand_width == 64) ? &STR_SIZE_64_ATT : &STR_SIZE_32_ATT;
    case ZYDIS_MNEMONIC_LOOP:
    case ZYDIS_MNEMONIC_LOOPE:
    case ZYDIS_MNEMONIC_LOOPNE:
        return ZydisFormatterATTGetSizeSuffix(instruction->address_width);
    case ZYDIS_MNEMONIC_XBEGIN:
        if ((instruction->machine_mode == ZYDIS_MACHINE_MODE_LONG_64) &&
            (instruction->operand_width == 32))
        {
            return &STR_SIZE_64_ATT;
        }
        return ZydisFormatterATTGetSizeSuffix(instruction->operand_width);
    default:
        return ZYAN_NULL;
    }
}

ZyanStatus ZydisFormatterATTPrintMnemonic(const ZydisFormatter* formatter,
    ZydisFormatterBuffer* buffer, ZydisFormatterContext* context)
{
    ZYAN_ASSERT(formatter);
    ZYAN_ASSERT(buffer);
    ZYAN_ASSERT(context);
    ZYAN_ASSERT(context->instruction);
    ZYAN_ASSERT(context->operands);

    const ZydisShortString* mnemonic = ZydisMnemonicGetStringWrapped(
        context->instruction->mnemonic);
    if (!mnemonic)
    {
        ZYDIS_BUFFER_APPEND_CASE(buffer, INVALID_MNEMONIC, formatter->case_mnemonic);
        return ZYAN_STATUS_SUCCESS;
    }

    ZYDIS_BUFFER_APPEND_TOKEN(buffer, ZYDIS_TOKEN_MNEMONIC);
    if (context->instruction->meta.branch_type == ZYDIS_BRANCH_TYPE_FAR)
    {
        ZYAN_CHECK(ZydisStringAppendShortCase(&buffer->string, &STR_FAR_ATT,
            formatter->case_mnemonic));
    }

    ZYAN_CHECK(ZydisStringAppendShortCase(&buffer->string, mnemonic, formatter->case_mnemonic));

    if (formatter->deco_apx_nf_use_suffix && context->instruction->apx.has_nf)
    {
        ZYAN_CHECK(ZydisStringAppendShortCase(&buffer->string, &STR_NF, formatter->case_mnemonic));
    }

    // Append operand-size suffix
    const ZydisShortString* const suffix = ZydisFormatterATTGetMnemonicSuffix(formatter, context);
    if (suffix)
    {
        ZYAN_CHECK(ZydisStringAppendShortCase(&buffer->string, suffix, formatter->case_mnemonic));
    }

    if (formatter->print_branch_size)
    {
        switch (context->instruction->meta.branch_type)
        {
        case ZYDIS_BRANCH_TYPE_NONE:
        case ZYDIS_BRANCH_TYPE_FAR:
        case ZYDIS_BRANCH_TYPE_ABSOLUTE:
            break;
        case ZYDIS_BRANCH_TYPE_SHORT:
            return ZydisStringAppendShortCase(&buffer->string, &STR_SHORT,
                formatter->case_mnemonic);
        case ZYDIS_BRANCH_TYPE_NEAR:
            return ZydisStringAppendShortCase(&buffer->string, &STR_NEAR,
                formatter->case_mnemonic);
        default:
            return ZYAN_STATUS_INVALID_ARGUMENT;
        }
    }

    return ZYAN_STATUS_SUCCESS;
}

ZyanStatus ZydisFormatterATTPrintRegister(const ZydisFormatter* formatter,
    ZydisFormatterBuffer* buffer, ZydisFormatterContext* context, ZydisRegister reg)
{
    ZYAN_UNUSED(context);

    ZYAN_ASSERT(formatter);
    ZYAN_ASSERT(buffer);
    ZYAN_ASSERT(context);

    ZYDIS_BUFFER_APPEND(buffer, REGISTER);
    const ZydisShortString* str = ZydisRegisterGetStringWrapped(reg);
    if (!str)
    {
        return ZydisStringAppendShortCase(&buffer->string, &STR_INVALID_REG,
            formatter->case_registers);
    }
    return ZydisStringAppendShortCase(&buffer->string, str, formatter->case_registers);
}

ZyanStatus ZydisFormatterATTPrintDISP(const ZydisFormatter* formatter,
    ZydisFormatterBuffer* buffer, ZydisFormatterContext* context)
{
    ZYAN_ASSERT(formatter);
    ZYAN_ASSERT(buffer);
    ZYAN_ASSERT(context);

    ZYDIS_BUFFER_APPEND_TOKEN(buffer, ZYDIS_TOKEN_DISPLACEMENT);
    switch (formatter->disp_signedness)
    {
    case ZYDIS_SIGNEDNESS_AUTO:
    case ZYDIS_SIGNEDNESS_SIGNED:
        ZYDIS_STRING_APPEND_NUM_S(formatter, formatter->disp_base, &buffer->string,
            context->operand->mem.disp.value, formatter->disp_padding, 
            formatter->hex_force_leading_number, ZYAN_FALSE);
        break;
    case ZYDIS_SIGNEDNESS_UNSIGNED:
        ZYDIS_STRING_APPEND_NUM_U(formatter, formatter->disp_base, &buffer->string,
            context->operand->mem.disp.value, formatter->disp_padding, 
            formatter->hex_force_leading_number);
        break;
    default:
        return ZYAN_STATUS_INVALID_ARGUMENT;
    }

    return ZYAN_STATUS_SUCCESS;
}

ZyanStatus ZydisFormatterATTPrintIMM(const ZydisFormatter* formatter,
    ZydisFormatterBuffer* buffer, ZydisFormatterContext* context)
{
    ZYAN_ASSERT(formatter);
    ZYAN_ASSERT(buffer);
    ZYAN_ASSERT(context);

    ZYDIS_BUFFER_APPEND(buffer, IMMEDIATE);
    return ZydisFormatterBasePrintIMM(formatter, buffer, context);
}

/* ---------------------------------------------------------------------------------------------- */

/* ============================================================================================== */
