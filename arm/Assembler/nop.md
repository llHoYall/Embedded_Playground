# NOP

No Operation.

## Syntax

> NOP{cond}

* `cond` : is an optional condition code.

## Usage

`NOP` does nothing. If `NOP` is not implemented as a specific instruction on your target architecture, the assembler treats it as a pseudo-instruction and generates an alternative instruction that does nothing, such as `MOV r0, r0 (A32)` or `MOV r8, r8 (T32)`.

`NOP` is not necessarily a time-consuming `NOP`. The processor might remove it from the pipeline before it reaches the execution stage.

You can use `NOP` for padding, for example to place the following instruction on a 64-bit boundary in `A32`, or a 32-bit boundary in `T32`.
