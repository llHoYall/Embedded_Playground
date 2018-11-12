# ARM-NONE-EABI-GCC

## Options Controlling C Dialect

* `-std=` : Determine the language standard.
	+ `c99`, `c11`
	+ `gnu99`, `gnu11`

## Options to Request or Suppress Warnings

* `-Werror` : Make all warnings  into errors.
* `-Wfatal-error` : This option causes the compiler to abort compilation on the first error occurred rather than trying to keep going and printing further error messages.
* `-Wall` : This enables all the warnings about constructions that some users consider questionable, and that are easy to avoid, even in conjunction with macros.
* `-Wextra` : This enables some extra warning flags that are not enabled by `-Wall`.
* `-Wshadow` : Warn whenever a local variable or type declaration shadows another variable, parameter, type, class member, or instance variable or whenever a built-in function is shadowed.

## Options That Control Optimization

* `-Os` : Optimize for size. `-Os` enables all `-O2` optimizations that do not typically increase code size. It also performs further optimizations designed to reduce code size.
`-Os` disables the following optimization flags.
  + `-falign-functions`
  + `-falign-jumps`
  + `-falign-loops`
  + `-falign-labels`
  + `-freorder-blocks`
  + `-freorder-blocks-algorithm=stc`
  + `-freorder-blocks-and-partition`
  + `-fprefetch-loop-arrays`
* `-Og` : Optimize debugging experience. `-Og` enables optimizations that do not interfere with debugging. It should be the optimization level of choice for the standard edit-compile-debug cycle, offering a reasonable level of optimization while maintaining fast compilation and a good debugging experience.
* `-ffunction-sections`
* `-fdata-sections` : Place each function or data item into its own section in the output file if the target supports arbitrary sections. The name of the function or the name of the data item determines the section's name in the output file.

## Options Controlling the Preprocessor

* `-MF file` : Like `-M` but do not mention header files that are found in system header directories, nor header files that are included, directly or indirectly, from such a header.
* `-MP` : This option instructs CPP to add a phony target for each dependency other than the main file, causing each to depend on nothing. These dummy rules work around errors make gives if you remove header files without updating the Makefile to match.
* `-MT target` : Change the target of the rule emitted by dependency generation.
* `-MD` : `-MD` is equivalent to `-M -MF file`, except that `-E` is not implied.
* `-MMD` : Like `-MD` except mention only user header files, not system header files.


## Options

* `-Wa,<options>` : Pass comma-separated <options> on to the assember.
* `-Wl,<options>` : Pass comma-separated <options> on to the linker.
* `-Xlinker <Arg>` : Pass <arg> on to the linker.
* `-c` : Compile and assemble, but do not link.
* `-o <file>` : Place the output into <file>.
* `-x <language>` : Specify the language of the following input files.
	> Ex) -x=assembler-with-cpp

## Reference

* https://gcc.gnu.org/onlinedoos/gcc/C-Dialect-Options.html
* https://gcc.gnu.org/onlinedocs/gcc/Warning-Options.html
* https://gcc.gnu.org/onlinedocs/gcc/Optimize-Options.html
