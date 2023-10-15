# Porting Guide v4 -> v5

# Encoder

- `ZydisEncoderDecodedInstructionToEncoderRequest` now expects exactly `instruction->operand_count_visible` to be
  passed, not `operand_count_visible` at maximum. Passing a lower value was previously allowed but didn't really
  make much sense at all.