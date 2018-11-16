# DCD

## Syntax

> {label} DCD{U} expr{,expr}

* `expr` : is either:
	+ A numeric expression.
	+ A PC-relative expression.

## Usage

`DCD` inserts up to three bytes of padding before the first defined word, if necessary, to achieve four-byte alignment.

Use `DCDU` if you do not require alignment.

`&` is a synonym for `DCD`.
