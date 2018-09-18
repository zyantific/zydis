# Zydis Examples

## Decoder

Comming soon™ ...

## Formatter

### [Formatter01](./Formatter01.c)
Demonstrates basic hooking functionality of the `ZydisFormatter` class by implementing a custom symbol-resolver.

### [Formatter02](./Formatter02.c)
Demonstrates basic hooking functionality of the `ZydisFormatter` class and the ability to completely omit specific operands. 

The example demonstrates the hooking functionality of the `ZydisFormatter` class by rewriting the mnemonics of `(V)CMPPS` and `(V)CMPPD` to their corresponding alias-forms (based on the condition encoded in the immediate operand).

### [Formatter03](./Formatter03.c)
Demonstrates the tokenizing feature of the `ZydisFormatter` class.

## Misc

### [ZydisWinKernel](./ZydisWinKernel.c)
Implements an example Windows kernel-mode driver.