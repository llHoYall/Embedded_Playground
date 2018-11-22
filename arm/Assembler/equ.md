# EQU

The `EQU` directive gives a symbolic name to a numeric constant, a register-relative value or a PC-relative value.

## Syntax

> name EQU expr{, type}

* `name` : is the symbolic name to assign to the value.
* `expr` : is a register-relative address, a PC-relative address, an absolute address, or a 32-bit integer constant.
* `type` : is optional. type can be any one of:
	+ ARM.
	+ THUMB.
	+ CODE32.
	+ CODE16.
	+ DATA.

	You can use type only if expr is an absolute address. If name is exported, the name entry in the symbol table in the object file is marked as ARM, THUMB, CODE32, CODE16, or DATA, according to type. This can be used by the linker.

## Usage

Use `EQU` to define constants. This is similar to the use of `#define` to define a constant in C.

`*` is a synonym for `EQU`.
