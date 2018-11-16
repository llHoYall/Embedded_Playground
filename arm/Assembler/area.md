# AREA

The `AREA` directive instructs the assembler to assemble a new code or data section.

## Syntax

> AREA sectionname{,attr}{,attr}...

* `sectionname` : is the name to give to the section. Sections are independent, named, indivisible chunks of code or data that are manipulated by the linker.

	You can choose any name for your sections. However, names starting with a non-alphabetic character must be enclosed in bars or a missing section name error is generated. For example, **|1_DataArea|**.

	Certain names are conventional. For example, |.text| is used for code sections produced by the C compiler, or for code sections otherwise associated with the C library.

* `attr` : are one or more comma-delimited section attributes. Valid attributes are:
	+ `ALIGN=expression` : By default, ELF sections are aligned on a four-byte boundary. expression can have any integer value from 0 to 31. The section is aligned on a 2expression-byte boundary. For example, if expression is 10, the section is aligned on a 1KB boundary.

		This is not the same as the way that the ALIGN directive is specified.

		```
		Note:
		Do not use ALIGN=0 or ALIGN=1 for ARM code sections.
		Do not use ALIGN=0 for Thumb code sections.
		```

	+ `CODE` : Contains machine instructions. READONLY is the default.
	+ `DATA` : Contains data, not instructions. READWRITE is the default.
	+ `NOINIT` : Indicates that the data section is uninitialized, or initialized to zero. It contains only space reservation directives `SPACE` or `DCB`, `DCD`, `DCDU`, `DCQ`, `DCQU`, `DCW`, or `DCWU` with initialized values of zero. You can decide at link time whether an area is uninitialized or zero-initialized.

		```
		Note:
		ARM® Compiler does not support systems with ECC or parity protection where the memory is not initialized.
		```

	+ `READONLY` : Indicates that this section must not be written to. This is the default for Code areas.
	+ `READWRITE` : Indicates that this section can be read from and written to. This is the default for Data areas.

## Usage

Use the `AREA` directive to subdivide your source file into ELF sections. You can use the same name in more than one `AREA` directive. All areas with the same name are placed in the same ELF section. Only the attributes of the first `AREA` directive of a particular name are applied.

In general, ARM recommends that you use separate ELF sections for code and data. However, you can put data in code sections. Large programs can usually be conveniently divided into several code sections. Large independent data sets are also usually best placed in separate sections.

The scope of numeric local labels is defined by AREA directives, optionally subdivided by `ROUT` directives.

There must be at least one AREA directive for an assembly.

```
Note:
armasm emits R_ARM_TARGET1 relocations for the DCD and DCDU directives if the directive uses PC-relative expressions and is in any of the PREINIT_ARRAY, FINI_ARRAY, or INIT_ARRAY ELF sections. You can override the relocation using the RELOC directive after each DCD or DCDU directive. If this relocation is used, read-write sections might become read-only sections at link time if the platform ABI permits this.
```
