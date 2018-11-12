# ARM-NONE-EABI-AS

## Options

* `-a[sub-option...]` : turn on listings
  + `d`: omit debugging directives
  + `l`: include assembly
  + `m`: include macro expansions
  + `s`: include symbols
  + `=FILE`: list to FILE (must be last  sub-option)
  > Ex) -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.c=.lst))
* `-g`, `--gen-debug` : generate debugging information
* `-I DIR` : add DIR to search list for .include directives
* `--MD FILE` : write dependency information in FILE (default none)
* `-o OBJFILE` : name the object-file output OBJFILE (default a.out)
* `--warn` : don't suppress warning

## ARM-Specific assembler options:

* `-mthumb` : assemble Thumb code
* `-mcpu=<cpu name>` : assemble for CPU
	> Ex) -mcpu=cortex-m4
* `-mfpu=<fpu name>` : assemble for FPU architecture
 	> Ex) -mfpu=fpv4-sp-d16
* `-mfloat-abi=<abi>` : assemble for floating point ABI
	> Ex) -mfloat-abi=hard
