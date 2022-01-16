# Porting Guide v3 -> v4

## API changes

### ZydisDecodedInstruction

1. Removed field `operands`
   - The `operands` array is passed to the desired decoder function as a separate argument instead
2. Added field `operand_count_visible`
   - Contains the number of visible (explicit and implicit) operands

### ZydisDecoder

#### 1

Removed:

```c
ZYDIS_EXPORT ZyanStatus ZydisDecoderDecodeBuffer(const ZydisDecoder* decoder,
    const void* buffer, ZyanUSize length, ZydisDecodedInstruction* instruction);
```

Replaced by:

```c
ZYDIS_EXPORT ZyanStatus ZydisDecoderDecodeFull(const ZydisDecoder* decoder,
    const void* buffer, ZyanUSize length, ZydisDecodedInstruction* instruction,
    ZydisDecodedOperand* operands, ZyanU8 operand_count, ZydisDecodingFlags flags);
```

#### 2

Added:

```c
ZYDIS_EXPORT ZyanStatus ZydisDecoderDecodeInstruction(const ZydisDecoder* decoder,
    ZydisDecoderContext* context, const void* buffer, ZyanUSize length,
    ZydisDecodedInstruction* instruction);
```

Added:

```c
ZYDIS_EXPORT ZyanStatus ZydisDecoderDecodeOperands(const ZydisDecoder* decoder,
    const ZydisDecoderContext* context, const ZydisDecodedInstruction* instruction,
    ZydisDecodedOperand* operands, ZyanU8 operand_count);
```

### General

- Type renamed: `ZydisAddressWidth` -> `ZydisStackWidth`
  - Constants renamed: `ZYDIS_ADDRESS_WIDTH_XXX` -> `ZYDIS_STACK_WIDTH_XXX`
- Enum changed: `ZydisMemoryOperandType`
  - Constants added: `ZYDIS_MEMOP_TYPE_VSIB`
- Decoding behavior changed:
  - In case of vector SIB addressing memory operands, `ZYDIS_MEMOP_TYPE_VSIB` will be reported by the decoder instead of `ZYDIS_MEMOP_TYPE_MEM` (in `ZydisDecodedOperand.mem.type`)
- Constants renamed:
  - `ZYDIS_STATIC_DEFINE` -> `ZYDIS_STATIC_BUILD`
  - `Zydis_EXPORTS` -> `ZYDIS_SHOULD_EXPORT`

## Changes relevant for language bindings

- The `ZYDIS_ATTRIB_` defines were rebased (underlying bits were changed)
- New type: `ZydisDecodingFlags`
- New type: `ZydisDecoderContext`
