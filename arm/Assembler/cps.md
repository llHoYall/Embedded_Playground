# CPS

Change Processor State.

## Syntax

> CPSeffect iflags{, #mode}

> CPS #mode

* `effect`
	+ `IE` : Interrupt or abort enable.
	+ `ID` : Interrupt or abort disable.
* `iflags` : is a sequence of one or more of:
	+ `a` : Enables or disables imprecise aborts.
	+ `i` : Enables or disables IRQ interrupts.
	+ `f` : Enables or disables FIQ interrupts.
	+ `mode` : specifies the number of the mode to change to.

## Usage

Changes one or more of the mode, A, I, and F bits in the CPSR, without changing the other CPSR bits.

`CPS` is only permitted in privileged software execution, and has no effect in User mode.

`CPS` cannot be conditional, and is not permitted in an IT block.
