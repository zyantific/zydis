## API changes

- Type renamed: `ZydisAddressWidth` -> `ZydisStackWidth` 
  - Constants renamed: `ZYDIS_ADDRESS_WIDTH_XXX` -> `ZYDIS_STACK_WIDTH_XXX`

## Changes relevant for language bindings

- The `ZYDIS_ATTRIB_` defines were rebased (underlying bits were changed)