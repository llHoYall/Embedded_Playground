# THUMB

The `THUMB` directive instructs the assembler to interpret subsequent instructions as T32 instructions, using the UAL syntax.

```
Note:
Not supported for AArch64 state.
```

## Syntax

> THUMB

## Usage

In files that contain code using different instruction sets, THUMB must precede T32 code written in UAL syntax.

If necessary, this directive also inserts one byte of padding to align to the next halfword boundary.

This directive does not assemble to any instructions. It also does not change the state. It only instructs armasm to assemble T32 instructions as appropriate, and inserts padding if necessary.
