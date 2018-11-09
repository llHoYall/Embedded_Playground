# Mbed OS 5

Mbed OS is an open-source operating system for platforms using Arm microcontrollers designed specifically for Internet of Things (IoT) devices: low-powered, constrained devices that need to connect to the internet.

Mbed OS provides an abstraction layer for the microcontrollers it runs on, so that developers can focus on writing C/C++ applications that call functionality available on a range of hardware.

Mbed OS applications can be reused on any Mbed-compatible platform.

## Mbed CLI (Windows)

### Installation

```
$ pip install mbed-cli
```

### Setup

```
$ mbed config -G ARM_PATH <path to ARM bin>
```

> Ex) $ mbed config -G ARMC6_PATH 'C:\Program Files\ARMCompiler6.6.1\bin\'

### Create

Create new mbed program or library.

```
$ mbed new <project>
```

### Import Program

Import program from URL.

```
$ mbed import <url>
```

> Ex) $ mbed import https://github.com/ARMmbed/mbed-os-example-blinky

### Add a Library

Add library from URL.

```
$ mbed add <url>
```

### Remove a Library

Remove library.

```
$ mbed remove <library>
```

### Detect Hardware

Detect connected Mbed targets/boards.

```
$ mbed detect
```

### Serial Terminal

Open serial terminal to connected target.

```
$ mbed sterm
```

> Ex) $ mbed sterm -b 115200 -p 3
> * -b \<BAUDRATE\> / --baudrate \<BAUDRATE\>
> * -p \<PORT\> / --port \<PORT\>

### Compile

Compile code using the mbed build tools.

```
$ mbed compile -m <TARGET> -t <TOOLCHAIN>
```

> Ex) $ mbed compile -t ARMC6 -m NUCLEO_F411RE -f
> * -t \<TOOLCHAIN\> / --toolchain \<TOOLCHAIN\> : ARM, GCC_ARM, IAR
> * -m \<TARGET\> / --target \<TARGET\>: K64F, NUCLEO_F401RE, NRF51822, ...
> * -f / --flash
> * --sterm

## Reference

* https://www.mbed.com
