# System Control Block

The System control block (`SCB`) provides system implementation information, and system control. This includes configuration, control, and reporting of the system exceptions.

## SCB Register

Address    | Name  | Type | Required privilege | Reset value | Description
-----------|-------|------|--------------------|-------------|------------
0xE000E008 | ACTLR | RW   | Privileged         | 0x00000000  | Auxiliary Control Register
0xE000ED00 | CPUID | RO   | Privileged         | 0x412FC230  | CPUID Base Register
0xE000ED04 | [ICSR](#Interrupt-Control-and-State-Register)  | RW   |	Privileged         | 0x00000000  | Interrupt Control and State Register
0xE000ED08 | [VTOR](#Vector-Table-Offset-Register)  | RW   | Privileged         | 0x00000000  | Vector Table Offset Register
0xE000ED0C | AIRCR | RW   |	Privileged	       | 0xFA050000  | Application Interrupt and Reset Control Register
0xE000ED10 | SCR   | RW   | Privileged         | 0x00000000  | System Control Register
0xE000ED14 | CCR 	 | RW   | Privileged         | 0x00000200  | Configuration and Control Register
0xE000ED18 | [SHPR1](#System-Handler-Priority-Register-1-3) | RW   | Privileged         | 0x00000000  | System Handler Priority Register 1
0xE000ED1C | [SHPR2](#System-Handler-Priority-Register-1-3) | RW   | Privileged         | 0x00000000  | System Handler Priority Register 2
0xE000ED20 | [SHPR3](#System-Handler-Priority-Register-1-3) | RW   | Privileged         | 0x00000000  | System Handler Priority Register 3
0xE000ED24 | SHCRS | RW   | Privileged         | 0x00000000  | System Handler Control and State Register
0xE000ED28 | CFSR  | RW	  | Privileged         | 0x00000000	 | Configurable Fault Status Register
0xE000ED28 | MMSR  | RW	  | Privileged         | 0x00	       | MemManage Fault Status Register
0xE000ED29 | BFSR  | RW	  | Privileged         | 0x00	       | BusFault Status Register
0xE000ED2A | UFSR  | RW	  | Privileged         | 0x0000	     | UsageFault Status Register
0xE000ED2C | HFSR  | RW	  | Privileged         | 0x00000000	 | HardFault Status Register
0xE000ED34 | MMAR  | RW	  | Privileged         | Unknown	   | MemManage Fault Address Register
0xE000ED38 | BFAR  | RW   | Privileged         | Unknown     | BusFault Address Register
0xE000ED3C | AFSR  | RW   | Privileged         | 0x00000000	 | Auxiliary Fault Status Register

* The `MMSR`, `BFSR`, `UFSR` is a subregister of the `CFSR`.

### Interrupt Control and State Register

* provides:
	+ a set-pending bit for the Non-Maskable Interrupt (NMI) exception
	+ set-pending and clear-pending bits for the PendSV and SysTick exceptions
* indicates:
	+ the exception number of the exception being processed
	+ whether there are preempted active exceptions
	+ the exception number of the highest priority pending exception
	+ whether any interrupts are pending.

```
 31 30 29 28 27 26 25 24 23 22 21                          12 11 10  9  8                       0
+--+-----+--+--+--+--+--+--+--+------------------------------+--+-----+--------------------------+
|  |     |  |  |  |  |  |  |  |         VECTPENDING          |  |     |        VECTACTIVE        |
+--+-----+--+--+--+--+--+--+--+------------------------------+--+-----+--------------------------+
```

* [31] NMIPENDSET (RW)
	+ NMI set-pending bit.

		Write:
		- 0 = no effect1 = changes NMI exception state to pending.

		Read:
		- 0 = NMI exception is not pending
		- 1 = NMI exception is pending.

		Because NMI is the highest-priority exception, normally the processor enter the NMI exception handler as soon as it registers a write of 1 to this bit, and entering the handler clears this bit to 0. A read of this bit by the NMI exception handler returns 1 only if the NMI signal is reasserted while the processor is executing that handler.
* [30:29] -
	+ Reserved.
* [28] PENDSVSET (RW)
	+ PendSV set-pending bit.

		Write:
		- 0 = no effect1 = changes PendSV exception state to pending.

		Read:
		- 0 = PendSV exception is not pending
		- 1 = PendSV exception is pending.

		Writing 1 to this bit is the only way to set the PendSV exception state to pending.
* [27] PENDSVCLR (WO)
	+ PendSV clear-pending bit.

		Write:
		- 0 = no effect1 = removes the pending state from the PendSV exception.
* [26] PENDSTSET (RW)
	+ SysTick exception set-pending bit.

		Write:
		- 0 = no effect1 = changes SysTick exception state to pending.

		Read:
		- 0 = SysTick exception is not pending
		- 1 = SysTick exception is pending.
* [25] PENDSTCLR (WO)
	+ SysTick exception clear-pending bit.

		Write:
		- 0 = no effect1 = removes the pending state from the SysTick exception.

		This bit is WO. On a register read its value is Unknown.
* [24] -
	+ Reserved.
* [23] Reserved for Debug use (RO)
	+ This bit is reserved for Debug use and reads-as-zero when the processor is not in Debug.
* [22] ISRPENDING (RO)
	+ Interrupt pending flag, excluding NMI and Faults:
		- 0 = interrupt not pending1 = interrupt pending.
* [21:18] -
	+ Reserved.
* [17:12] VECTPENDING (RO)
	+ Indicates the exception number of the highest priority pending enabled exception:
		- 0 = no pending exceptions
		- Nonzero = the exception number of the highest priority pending enabled exception.

		The value indicated by this field includes the effect of the BASEPRI and FAULTMASK registers, but not any effect of the PRIMASK register.
* [11] RETTOBASE (RO)
	+ Indicates whether there are preempted active exceptions:
		- 0 = there are preempted active exceptions to execute
		- 1 = there are no active exceptions, or the currently-executing exception is the only active exception.
* [10:9] -
	+ Reserved.
* [8:0] VECTACTIVE (RO)
	+ Contains the active exception number:
		- 0 = Thread mode
		- Nonzero = The exception number[a] of the currently active exception.

		```
		Note
		Subtract 16 from this value to obtain the CMSIS IRQ number required to index into the Interrupt Clear-Enable, Set-Enable, Clear-Pending, Set-Pending, or Priority Registers
		```

### Vector Table Offset Register

The `VTOR` indicates the offset of the vector table base address from memory address 0x00000000.

```
 31                                                                        7  6                 0
+---------------------------------------------------------------------------+--------------------+
|                                  TBLOFF                                   |      Reserved      |
+---------------------------------------------------------------------------+--------------------+
```

* [31:7] TBLOFF
	+ Vector table base offset field. It contains bits[29:7] of the offset of the table base from the bottom of the memory map.

		```
		Note
		Bit[29] determines whether the vector table is in the code or SRAM memory region:
		  * 0 = code
		  * 1 = SRAM.
		In implementations bit[29] is sometimes called the TBLBASE bit.
		```
* [6:0] -
	+ Reserved.

When setting `TBLOFF`, you must align the offset to the number of exception entries in the vector table. The minimum alignment is 32 words, enough for up to 16 interrupts. For more interrupts, adjust the alignment by rounding up to the next power of two. For example, if you require 21 interrupts, the alignment must be on a 64-word boundary because the required table size is 37 words, and the next power of two is 64. See your vendor documentation for the alignment details for your device.

```
Note
Table alignment requirements mean that bits[6:0] of the table offset are always zero.
```

### System Handler Priority Register 1-3

The `SHPR1-SHPR3` registers set the priority level, 0 to 255, of the exception handlers that have configurable priority.

`SHPR1-SHPR3` are byte accessible.

#### System Handler Priority Register 3

```
 31                   24 23                   16 15                                             0
+-----------------------+-----------------------+------------------------------------------------+
|        PRI_15         |        PRI_14         |                    Reserved                    |
+-----------------------+-----------------------+------------------------------------------------+
```

* [31:24] PRI_15
	+ Priority of system handler 15, SysTick exception
* [23:16] PRI_14
	+ Priority of system handler 14, PendSV
* [15:0] -
	+ Reserved.

## Reference

* [SCB](http://infocenter.arm.com/help/index.jsp?topic=/com.arm.doc.dui0552a/CIHFDJCA.html)
