# ARM Compiler 6.6.1 - ARM ASM

## Usage

> armclang --target=\<triple\> [options] file1 file2 ... fileN

## Options

### Mandatory Options

* `--target` : Generate code for the specified target triple.
	+ `arm-arm-none-eabi` : Generate code for AArch32 state
	+ `aarch64-arm-none-eabi` : Generate code for AArch64 state

### Compiler and Integrated Assembler Options

* `-march` : Targets an architecture, generating generic code that runs on any processor of that architecture.
* `-mcpu` : Targets a specific processor, generating optimized code for that specific processor.
* `-mfpu` : Targets a specific floating-point unit.
* `-march=list` : Show a list of available architectures
* `-mcpu=list` : Show a list of available CPUs
* `-mfpu=list` : Show a list of available FPUs.
* `-c` : Only perform the compile step, do not invoke armlink.
* `-D<k>=<v>` : Define pre-processor macro \<k\> with value \<v\>.
* `-E` : Only perform the preprocess step, do not compile or link.
* `-g` : Emit debug tables for source-level debugging.
* `-I<dir>` : Add \<dir\> to the search path for include files.
* `-o <file>` : Write output to <file>.
* `-x <language>` : Specifies the language of source files.
	+ `c` : C code.
	+ `c++` : C++ code.
	+ `assembler-with-cpp` : Assembly code containing C directives that require the C preprocessor.
	+ `assembler` : Assembly code that does not require the C preprocessor.

### Compiler-Specific Options

* `-mfloat-abi=<value>` : Specify if hardware instructions or library calls should be used for floating-point operations, and which registers are used for floating-point parameters. Valid values are `soft`, `softfp` and `hard`.
* `-mthumb` : Requests that the compiler targets the Thumb instruction set.
* `-L<dir>` : Add \<dir\> to the search path for library files.
* `-l<lib>` : Add *lib\<lib\>.a* to the list of libraries to be linked.
* `-O<level>` : Specifies the level of optimization to use when compiling source files. Valid values are `-O0`, `-O1`, `-O2`, `-O3`, `-Os`, `-Oz` and `-Ofast`.
* `-S` : Output assembly code, rather than object code.
* `-std` : Select the source language standard to compile for.
* `-Wall` : Emit more warning messages for potentially incorrect or non-portable source code.
* `-Werror` : Treat all warnings as errors.

### Etc. Options

* `-fdata-sections`, `-fno-data-sections` : Enables or disables the generation of one ELF section for each variable in the source file. The default is `-fdata-sections`.
* `ffunction-sections`, `-fno-function-sections` : `-ffunction-sections` generates a separate ELF section for each function in the source file. `-ffunction-sections` is set by default. The output section for each function has the same name as the function that generates the section, but with a .text. prefix. To disable this, use `-fno-function-sections`.
* `-M`, `-MM` : Produces a list of makefile dependency rules suitable for use by a make utility. The compiler executes only the preprocessor step of the compilation. By default, output is on the standard output stream. If you specify multiple source files, a single dependency file is created.
	+ `-M` : lists both system header files and user header files.
	+ `-MM` : lists only user header files.
* `-MD`, `-MMD` : Compiles source files and produces a list of makefile dependency rules suitable for use by a make utility. The compiler creates a makefile dependency file for each source file, using a .d suffix. Unlike `-M` and `-MM`, that cause compilation to stop after the preprocessing stage, `-MD` and `-MMD` allow for compilation to continue.
	+ `-MD` lists both system header files and user header files.
	+ `-MMD` lists only user header files.
* `-MF <filename>` : Specifies a filename for the makefile dependency rules produced by the `-M` and `-MD` options.
	+ The `-MF` option only has an effect when used in conjunction with one of the `-M`, `-MM`, `-MD`, or `-MMD` options.
* `-MG` : Prints dependency lines for header files even if the header files are missing. Warning and error messages on missing header files are suppressed, and compilation continues.
	+ The `-MG` option only has an effect when used with one of the following options: `-M` or `-MM`.
* `-MP` : Emits dummy dependency rules. These rules work around make errors that are generated if you remove header files without a corresponding update to the makefile.
	+ The `-MP` option only has an effect when used in conjunction with the `-M`, `-MD`, `-MM`, or `-MMD` options.
* `-MT` : Changes the target of the makefile dependency rule produced by dependency generating options.
	+ The `-MT` option only has an effect when used in conjunction with either the `-M`, `-MM`, `-MD`, or `-MMD` options.

## Reference

* [ARM Compiler Command-Line Options](http://infocenter.arm.com/help/topic/com.arm.doc.dui0774h/chr1383574213854.html)
