# REQUIRE8 and PRESERVE8

The `REQUIRE8` and `PRESERVE8` directives specify that the current file requires or preserves eight-byte alignment of the stack.

```
Note:
This directive is required to support non-ABI conforming toolchains. It has no effect on AArch64 assembly and is not required when targeting AArch64.
```

## Syntax

> REQUIRE8 {bool}

> PRESERVE8 {bool}

* `bool` : is an optional Boolean constant, either {`TRUE`} or {`FALSE`}.

## Usage

Where required, if your code preserves eight-byte alignment of the stack, use `PRESERVE8` to set the `PRES8` build attribute on your file. If your code does not preserve eight-byte alignment of the stack, use `PRESERVE8` {FALSE} to ensure that the `PRES8` build attribute is not set. Use `REQUIRE8` to set the `REQ8` build attribute. If there are multiple `REQUIRE8` or `PRESERVE8` directives in a file, the assembler uses the value of the last directive.

The linker checks that any code that requires eight-byte alignment of the stack is only called, directly or indirectly, by code that preserves eight-byte alignment of the stack.

```
Note:
If you omit both PRESERVE8 and PRESERVE8 {FALSE}, the assembler decides whether to set the PRES8 build attribute or not, by examining instructions that modify the SP. ARM recommends that you specify PRESERVE8 explicitly.

You can enable a warning by using the --diag_warning 1546 option when invoking armasm.

This gives you warnings like:

"test.s", line 37: Warning: A1546W: Stack pointer update potentially breaks 8 byte stack alignment
       37 00000044         STMFD    sp!,{r2,r3,lr}
```
