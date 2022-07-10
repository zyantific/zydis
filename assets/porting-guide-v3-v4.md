# Porting Guide v3 -> v4

### General

- Zydis now requires a C11 capable compiler
- Type renamed: `ZydisAddressWidth` -> `ZydisStackWidth`
- Enum changed: `ZydisMemoryOperandType`
  - Constants added: `ZYDIS_MEMOP_TYPE_VSIB`
- Decoding behavior changed:
  - In case of vector SIB addressing memory operands, `ZYDIS_MEMOP_TYPE_VSIB` will be reported by the decoder instead
    of `ZYDIS_MEMOP_TYPE_MEM` (in `ZydisDecodedOperand.mem.type`)
- Constants renamed:
  - `ZYDIS_STATIC_DEFINE` -> `ZYDIS_STATIC_BUILD`
  - `Zydis_EXPORTS` -> `ZYDIS_SHOULD_EXPORT`
  - `ZYDIS_ADDRESS_WIDTH_XXX` -> `ZYDIS_STACK_WIDTH_XXX`
- `ZydisCPUFlagAction` got replaced by `ZydisAccessedFlagsMask`
- `ZydisAccessedFlags` was added as a replacement for the CPU flag arrays
- `ZYDIS_CPUFLAG_C[0-3]` were replaced with `ZYDIS_FPUFLAG_C[0-3]`
- The segment API (`ZydisGetInstructionSegments` and corresponding types) was moved to a separate
  header file

### Decoder

- Added functions to decode instructions and operands individually, allowing for improved performance when the operands
  are not actually needed.
  - `ZydisDecoderDecodeInstruction`
  - `ZydisDecoderDecodeOperands`
- `ZydisDecoderDecodeBuffer` got replaced by `ZydisDecoderDecodeFull`
- `ZydisDecodedInstruction` struct was changed
  - Removed field `operands`
     - The `operands` array is passed to the desired decoder function as a separate argument instead
  - Added field `operand_count_visible`
     - Contains the number of visible (explicit and implicit) operands
  - The `cpu_flags_read` and `cpu_flags_written` fields are replaced with the `cpu_flags` field
  - The `fpu_flags_read` and `fpu_flags_read` fields are replaced with the `fpu_flags` field
  - The older `accessed_flags` array is replaced by the `cpu_flags` and `fpu_flags` fields

### Formatter

- Added arguments to accommodate the new decoder API changes
  - The signature of `ZydisFormatterFormatInstruction` changed
  - The functionality of `ZydisFormatterFormatInstructionEx` was integrated into the non-`Ex`
    variant of the function
  - The signature of `ZydisFormatterFormatOperand` changed
  - The functionality of `ZydisFormatterFormatOperandEx` was integrated into the non-`Ex`
    variant of the function
  - The signature of `ZydisFormatterTokenizeInstruction` changed
  - The functionality of `ZydisFormatterTokenizeInstructionEx` was integrated into the non-`Ex`
    variant of the function
  - The signature of `ZydisFormatterTokenizeOperand` changed
  - The functionality of `ZydisFormatterTokenizeOperandEx` was integrated into the non-`Ex`
    variant of the function

### Utils

- Removed flag helpers (no longer needed with new flags format!)
  - `ZydisGetAccessedFlagsByAction`
  - `ZydisGetAccessedFlagsRead`
  - `ZydisGetAccessedFlagsWritten`

### Changes relevant for language bindings

- Encoder added
  - `Encoder.h`, various new types and functions
- Type `ZydisRegisterKind` added
- The `ZYDIS_ATTRIB_` defines were rebased (underlying bits were changed)
- New type `ZydisDecodingFlags`
- New type `ZydisDecoderContext`
- An anonymous union was added around some fields in the `raw` part of `ZydisDecodedInstruction`
- An anonymous union was added around the operand type specific fields in `ZydisDecodedOperand`
- The previously anonymous sub-structs in `ZydisDecodedOperand` were lifted to 
  the top level scope and are proper types now
- Some of the previously anonymous sub-structs in `ZydisDecodedInstruction` were lifted to the top level scope as well
- `ZydisDecodedOperand::type` was moved to a different location in the struct
- Unions were added around fields in `ZydisDecodedOperand` and `ZydisDecodedInstruction`
