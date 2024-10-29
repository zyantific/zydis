# Porting Guide v4 -> v5

### Encoder

- `ZydisRegisterGetLargestEnclosing` will now return the given register itself for registers that don't have
  an enclosing register. Previously it would return `ZYDIS_REGISTER_NONE` in these cases.
- `ZydisEncoderDecodedInstructionToEncoderRequest` now expects exactly `instruction->operand_count_visible` to be
  passed, not `operand_count_visible` at maximum. Passing a lower value was previously allowed but didn't really
  make much sense at all.
  
### Decoder
  
- `ZydisDecodedOperandImm` struct was changed
  - Added field `offset`
    - Contains the offset of the immediate data, relative to the beginning of the instruction, in bytes.
  - Added field `size`
    - Contains the physical immediate size, in bits.
- `ZydisDecodedOperandMemDisp_` struct was changed
  - Added field `offset`
    - Contains the offset of the immediate data, relative to the beginning of the instruction, in bytes.
  - Added field `size`
    - Contains the physical displacement size, in bits.
  - Removed field `has_displacement`
    - A `size` of 0 indicates that there is no displacement, effectively replacing the need for `has_displacement`.