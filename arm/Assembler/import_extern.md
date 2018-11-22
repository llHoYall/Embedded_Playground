# IMPORT and EXTERN

The `IMPORT` and `EXTERN` directives provide the assembler with a name that is not defined in the current assembly.

## Syntax

> directive symbol {[SIZE=n]}

> directive symbol {[type]}

> directive symbol [attr{,type}{,SIZE=n}]

> directive symbol [WEAK {,attr}{,type}{,SIZE=n}]

* `directive` : can be either:
	+ `IMPORT` : imports the symbol unconditionally.
	+ `EXTERN` : imports the symbol only if it is referred to in the current assembly.
* `symbol` : is a symbol name defined in a separately assembled source file, object file, or library. The symbol name is case-sensitive.
* `WEAK` : prevents the linker generating an error message if the symbol is not defined elsewhere. It also prevents the linker searching libraries that are not already included.
* `attr` : can be any one of:
	+ `DYNAMIC` : sets the `ELF` symbol visibility to `STV_DEFAULT`.
	+ `PROTECTED` : sets the `ELF` symbol visibility to `STV_PROTECTED`.
	+ `HIDDEN` : sets the `ELF` symbol visibility to `STV_HIDDEN`.
	+ `INTERNAL` : sets the `ELF` symbol visibility to `STV_INTERNAL`.
* `type` : specifies the symbol type:
	+ `DATA` : symbol is treated as data when the source is assembled and linked.
	+ `CODE` : symbol is treated as code when the source is assembled and linked.
	+ `ELFTYPE=n` : symbol is treated as a particular ELF symbol, as specified by the value of n, where n can be any number from 0 to 15.

	If unspecified, the linker determines the most appropriate type.
* `n` : specifies the size and can be any 32-bit value. If the SIZE attribute is not specified, the assembler calculates the size:
	+ For `PROC` and `FUNCTION` symbols, the size is set to the size of the code until its `ENDP` or `ENDFUNC`.
	+ For other symbols, the size is the size of instruction or data on the same source line. If there is no instruction or data, the size is zero.

## Usage

The name is resolved at link time to a symbol defined in a separate object file. The symbol is treated as a program address. If `[WEAK]` is not specified, the linker generates an error if no corresponding symbol is found at link time.

If `[WEAK]` is specified and no corresponding symbol is found at link time:

* If the reference is the destination of a `B` or `BL` instruction, the value of the symbol is taken as the address of the following instruction. This makes the `B` or `BL` instruction effectively a `NOP`.
* Otherwise, the value of the symbol is taken as zero.
