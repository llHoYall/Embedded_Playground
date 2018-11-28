# ENTRY

The `ENTRY` directive declares an entry point to a program.

## Syntax

> ENTRY

## Usage

A program must have an entry point. You can specify an entry point in the following ways:

Using the `ENTRY` directive in assembly language source code.

Providing a main() function in C or C++ source code.

Using the armlink `--entry` command-line option.

You can declare more than one entry point in a program, although a source file cannot contain more than one `ENTRY` directive. For example, a program could contain multiple assembly language source files, each with an `ENTRY` directive. Or it could contain a C or C++ file with a main() function and one or more assembly source files with an `ENTRY` directive.

If the program contains multiple entry points, then you must select one of them. You do this by exporting the symbol for the `ENTRY` directive that you want to use as the entry point, then using the armlink `--entry` option to select the exported symbol.
