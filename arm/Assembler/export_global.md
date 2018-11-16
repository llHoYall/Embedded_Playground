# EXPORT or GLOBAL

The `EXPORT` directive declares a symbol that can be used by the linker to resolve symbol references in separate object and library files. `GLOBAL` is a synonym for `EXPORT`.

## Syntax

> EXPORT {[WEAK]}

> EXPORT symbol {[SIZE=n]}

> EXPORT symbol {[type{,set}]}

> EXPORT symbol [attr{,type{,set}}{,SIZE=n}]

> EXPORT symbol [WEAK {,attr}{,type{,set}}{,SIZE=n}]

* `symbol` : is the symbol name to export. The symbol name is case-sensitive. If symbol is omitted, all symbols are exported.
* `WEAK` : symbol is only imported into other sources if no other source exports an alternative symbol. If `[WEAK]` is used without symbol, all exported symbols are weak.

## Usage

Use `EXPORT` to give code in other files access to symbols in the current file.

Use the `[WEAK]` attribute to inform the linker that a different instance of symbol takes precedence over this one, if a different one is available from another source. You can use the `[WEAK]` attribute with any of the symbol visibility attributes.
