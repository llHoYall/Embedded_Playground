# DCD

The `DCD` directive allocates one or more words of memory, aligned on four-byte boundaries, and defines the initial runtime contents of the memory. `DCDU` is the same, except that the memory alignment is arbitrary.

## Syntax

> {label} DCD{U} expr{,expr}

* `expr` : is either:
	+ A numeric expression.
	+ A PC-relative expression.

## Usage

`DCD` inserts up to three bytes of padding before the first defined word, if necessary, to achieve four-byte alignment.

Use `DCDU` if you do not require alignment.

`&` is a synonym for `DCD`.
