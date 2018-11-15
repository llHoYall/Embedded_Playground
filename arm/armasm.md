# ARM Compiler 6.6.1 - ARM ASM

## Usage

> armasm [options] sourcefile

## Options

* `-o <outputfile>` : Name the final output file
* `-g` : Output debugging tables
* `--keep` : Keep local labels in symbol table of object file
* `--cpu <target-cpu>` : Set the target ARM core type
* `--cpu list` : Output a list of all the selectable CPUs
* `--fpu <target-arch>` : Set target FP architecture version
* `--fpu list` : Output a list of all selectable FP architectures
* `--thumb` : Assemble ARM instructions
* `--brief_diagnostics` : Enables and disables the output of brief diagnostic messages.

## Reference

* [ARM ASM Command-Line Options](http://infocenter.arm.com/help/index.jsp?topic=/com.arm.doc.dui0801h/pge1424433195614.html)
