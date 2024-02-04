# Porting Guide v4 -> v5

# Encoder

- `ZydisRegisterGetLargestEnclosing` will now return the given register itself for registers that don't have
  an enclosing register. Previously it would return `ZYDIS_REGISTER_NONE` in these cases.
- `ZydisEncoderDecodedInstructionToEncoderRequest` now expects exactly `instruction->operand_count_visible` to be
  passed, not `operand_count_visible` at maximum. Passing a lower value was previously allowed but didn't really
  make much sense at all.