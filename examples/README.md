# Zydis Examples

## Decoder

Comming soon™ ...

## Formatter

### Formatter01
Demonstrates basic hooking functionality of the `ZydisFormatter` class by implementing a custom symbol-resolver.

### Formatter02
Demonstrates basic hooking functionality of the `ZydisFormatter` class and the ability to completely omit specific operands. 

The example demonstrates the hooking functionality of the `ZydisFormatter` class by rewriting the mnemonics of `(V)CMPPS` and `(V)CMPPD` to their corresponding alias-forms (based on the condition encoded in the immediate operand).

### Formatter03
Demonstrates the tokenizing feature of the `ZydisFormatter` class.

## Misc

### ZydisWinKernel
Implements an example Windows kernel-mode driver.

## License

Zydis is licensed under the MIT license.
