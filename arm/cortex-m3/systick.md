# System Timer (SysTick)

## About the SysTick

The SCS also includes a system timer (SysTick) that can be used by an operating system to ease porting from another platform. The SysTick can be polled by software or can be configured to generate an interrupt. The SysTick interrupt has its own entry in the vector table and therefore can have its own handler.


## SysTick Register

 Name                       | Address    | Type |Description
----------------------------|------------|------|-----------
[SysTick Control and Status](#SysTick-Control-and-Status-Register) | 0xE000E010 | RW | basic control of SysTick e.g. enable, clock source, interrupt or poll
[SysTick Reload Value](#SysTick-Reload-Value-Register) | 0xE000E014 | RW | value to load Current Value register when 0 is reached
[SysTick Current Value](#SysTick-Current-Value-Register) | 0xE000E018 | RW | the current value of the count down
[SysTick Calibration Value](#SysTick-Calibration-Value-Register) | 0xE000E01C | RO | might contain the number of ticks to generate a 10ms interval and other information, depending on the implementation

* Required Privilege : Privileged

### SysTick Control and Status Register

The SysTick SYST_CSR register enables the SysTick features. The register resets to 0x00000000, or to 0x00000004 if your device does not implement a reference clock.

```
 31                                         17 16 15                                   3  2  1  0
+---------------------------------------------+--+--------------------------------------+--+--+--+
|                  Reserved                   |  |               Reserved               |  |  |  |
+---------------------------------------------+--+--------------------------------------+--+--+--+
```

* [31:17] -
	+ Reserved.
* [16] COUNTFLAG
	+ Returns 1 if timer counted to 0 since last time this was read.
* [15:3] -
	+ Reserved.
* [2] CLKSOURCE
	+ Indicates the clock source:
		- 0 = external clock.
		- 1 = processor clock.
* [1]	TICKINT
	+ Enables SysTick exception request:
		- 0 = counting down to zero does not assert the SysTick exception request.
		- 1 = counting down to zero asserts the SysTick exception request.
	+ Software can use COUNTFLAG to determine if SysTick has ever counted to zero.
* [0] ENABLE
	+ Enables the counter:
		- 0 = counter disabled.
		- 1 = counter enabled.

When `ENABLE` is set to 1, the counter loads the `RELOAD` value from the SYST_RVR register and then counts down. On reaching 0, it sets the `COUNTFLAG` to 1 and optionally asserts the SysTick depending on the value of `TICKINT`. It then loads the `RELOAD` value again, and begins counting.

### SysTick Reload Value Register

The SYST_RVR register specifies the start value to load into the SYST_CVR register.

```
 31                    24 23                                                                    0
+------------------------+-----------------------------------------------------------------------+
|        Reserved        |                                RELOAD                                 |
+------------------------+-----------------------------------------------------------------------+
```

* [31:24] -
	+ Reserved.
* [23:0] RELOAD
	+ Value to load into the SYST_CVR register when the counter is enabled.

#### Calculating the RELOAD value
The `RELOAD` value can be any value in the range 0x00000001-0x00FFFFFF. A start value of 0 is possible, but has no effect because the SysTick exception request and `COUNTFLAG` are activated when counting from 1 to 0.

The `RELOAD` value is calculated according to its use. For example, to generate a multi-shot timer with a period of N processor clock cycles, use a `RELOAD` value of N-1. If the SysTick interrupt is required every 100 clock pulses, set `RELOAD` to 99.

### SysTick Current Value Register

The SYST_CVR register contains the current value of the SysTick counter.

```
 31                    24 23                                                                    0
+------------------------+-----------------------------------------------------------------------+
|        Reserved        |                                CURRENT                                |
+------------------------+-----------------------------------------------------------------------+
```

* [31:24] -
	+ Reserved.
* [23:0] CURRENT
	+ Reads return the current value of the SysTick counter.
	+ A write of any value clears the field to 0, and also clears the SYST_CSR COUNTFLAG bit to 0.

### SysTick Calibration Value Register

The SYST_CALIB register indicates the SysTick calibration properties. The reset value of this register is implementation-defined.

```
 31 30 29              24 23                                                                    0
+--+--+------------------+-----------------------------------------------------------------------+
|  |  |     Reserved     |                                 TENMS                                 |
+--+--+------------------+-----------------------------------------------------------------------+
```

* [31] NOREF
	+ Indicates whether the device provides a reference clock to the processor:
		- 0 = reference clock provided.
		- 1 = no reference clock provided.
  + If your device does not provide a reference clock, the SYST_CSR.CLKSOURCE bit reads-as-one and ignores writes.
* [30] SKEW
	+ Indicates whether the TENMS value is exact:
		- 0 = TENMS value is exact.
		- 1 = TENMS value is inexact, or not given.
	+ An inexact TENMS value can affect the suitability of SysTick as a software real time clock.
* [29:24] -
	+ Reserved.
* [23:0] TENMS
	+ Reload value for 10ms (100Hz) timing, subject to system clock skew errors. If the value reads as zero, the calibration value is not known.

If calibration information is not known, calculate the calibration value required from the frequency of the processor clock or external clock.

## Configuring SysTick

To configure the SysTick you need to load the SysTick Reload Value register with the interval required between SysTick events. **The timer interrupt or `COUNTFLAG` bit (in the SysTick Control and Status register) is activated on the transition from 1 to 0, therefore it activates every n+1 clock ticks.** If a period of 100 is required 99 should be written to the SysTick Reload Value register. **The SysTick Reload Value register supports values between 1 and 0x00FFFFFF.**

If you want to use the SysTick to generate an event at a timed interval, for example 1ms, you can use the SysTick Calibration Value Register to scale your value for the Reload register. **The SysTick Calibration Value Register is a read-only register that contains the number of pulses for a period of 10ms, in the `TENMS` field (bits 0 to 23).** This register also has a `SKEW` bit (30) that is used to indicate that the calibration for 10ms in the `TENMS` section is not exactly 10ms due to small variations in clock frequency. Bit 31 is used to indicate if the reference clock is provided.

**The Control and Status Register allows you to select between polling the timer by reading `COUNTFLAG` (bit 16), or by the SysTick generating an interrupt.**

By default the SysTick is configured for polling mode. In this mode, user code must read `COUNTFLAG` to ascertain if the SysTick event had occurred. This is indicated by `COUNTFLAG` being set. **Reading of the Control and Status register clears the `COUNTFLAG` bit.** **To configure the SysTick to generate an interrupt you must set `TICKINT` (bit 1 of the SysTick Control and Status register) HIGH.** **You will also need to enable the appropriate interrupt in the NVIC.** You must set `CLKSOURCE` (bit 2) to 1 to select the core clock and zero select the external reference clock.

**The Timer is enabled by setting bit 0 of the SysTick Status and Control register.**
