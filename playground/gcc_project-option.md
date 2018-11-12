# GCC Project Option

## System Calls

* `Freestanding` : A typical embedded configuration, that does not use the POSIX system calls (open, close, read, write, etc).
* `POSIX (retargetting)` : A more elaborate embedded configuration where the application makes use of these calls, but redirects the file descriptors to local devices or files, by providing custom implementations for the system calls (like _open, _close, _read, _write etc). This configuration allows to port POSIX programs easier.
* `Semihosting` : A special testing configuration, that bridges all system calls to the host operating system where the GDB server runs. This configurations is particularly interesting for running test programs that can leave the test results in a file stored on the host, for automated integration in a test suite.

## Trace Output

* `None (no trace output)` : A basic configuration that doesn't use trace output messages.
* `ARM IRM (via SWO)` : A specific configuration that help to print information via SWO pin when using J-Link.
* `Semihosting STDOUT stream` : A more complex configuration that configure stdout to use a physical serial connection as UART or any other peripherals that offer the possibility to output messages.
* `Semihosting DEBUG channel` : A debug specific configuration which enable semihosting in DEBUG mode and offer the possibility to use resources from the development platform n the embedded target via debugger. This can help the user to send trace stream to debugger console (like trace_printf, trace_puts etc).
