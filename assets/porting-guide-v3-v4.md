# Porting Guide v3 -> v4

## API changes

- Type renamed: `ZydisAddressWidth` -> `ZydisStackWidth`
  - Constants renamed: `ZYDIS_ADDRESS_WIDTH_XXX` -> `ZYDIS_STACK_WIDTH_XXX`
- Enum changed: `ZydisMemoryOperandType`
  - Constants added: `ZYDIS_MEMOP_TYPE_VSIB`
- Decoding behavior changed:
  - In case of vector SIB addressing memory operands, `ZYDIS_MEMOP_TYPE_VSIB` will be reported by the decoder instead of `ZYDIS_MEMOP_TYPE_MEM` (in `ZydisDecodedOperand.mem.type`)

## Changes relevant for language bindings

- The `ZYDIS_ATTRIB_` defines were rebased (underlying bits were changed)
