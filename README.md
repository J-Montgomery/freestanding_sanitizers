[![License](https://img.shields.io/github/license/J-Montgomery/freestanding_sanitizers)](https://github.com/J-Montgomery/freestanding_sanitizers/blob/master/LICENSE.txt)
![Latest Release](https://img.shields.io/github/v/release/J-Montgomery/freestanding_sanitizers)

# Introduction

Sanitizers are one of the most important modern tools for writing high-quality code in C and C++. Unfortunately developers working on platforms where code quality is the most important like safety-critical devices often lack access to sanitizers. This library provides freestanding sanitizer implementations that can be used in situations where the sanitizers normally shipped with compiler toolchains are either unavailable or unsupported.

This project currently provides a freestanding implementation of the Undefined Behavior Sanitizer (UBSAN) and an in-progress implementation of AddressSanitizer (ASAN), both implemented in C99 and compatible with ambiguous, recent versions of LLVM and GCC.

## Features
| Feature             | Implemented        | Notes |
|---------------------|--------------------|-------|
| C99                 | :heavy_check_mark: | Uses C11 `stdatomic.h` for optional backtrace |
| UBSAN               | :heavy_check_mark: | Only handler APIs |
| ASAN                | :x:                |       |


## Dependencies
* `<stdbool.h>`
* `<stdint.h>`
* `<string.h>` for `memcpy`
* GCC or LLVM
* Make
* Python3 (Optional)
  * Used to run and validate test cases.

## Optional Runtime Dependencies
* `<stdio.h>`
* `<stdarg.h>`
  * Used in the default logging module. Can be omitted by defining a custom function.
* `<stdlib.h>`
  * Used in the default termination module. Can be omitted by defining a custom function.
* `<stdatomic.h>`
* `<execinfo.h>`
  * Used to provide backtrace.

## Configuration options

The following options control sanitizer functionality:

* `SANITIZER_CONFIG_LOGGER_ENABLE`
  * This option is enabled by default.
  * Option controls whether the built-in logging functions are compiled for the sanitizers to use.
  * Disable with `-DSANITIZER_CONFIG_LOGGER_ENABLE=0`
  * If this option is not enabled, the sanitizer will compile with minimal stubs that prevent linking errors if appropriate definitions for the following functions are not provided by the application:
    * `__sanitizer_log_puts`
    * `__sanitizer_log_printf`
* `SANITIZER_CONFIG_DIE_ENABLE`
  * This option is enabled by default.
  * If the option is enabled, sanitizers will call `exit(1)` on abort if not overridden.
  * If the option is disabled, sanitizers will enter an infinite `while(1)` loop on abort if not overridden.
  * Disable with `-DSANITIZER_CONFIG_DIE_ENABLE=0`
* `SANITIZER_CONFIG_BACKTRACE_ENABLE`
  * This option is enabled by default on Linux and Apple platforms, where backtrace is generally available.
  * If the option is enabled, sanitizers will use the backtrace API in `<execinfo.h>` to display a best-effort callstack.
  * This option depends on `<stdatomic.h>` and `__attribute__((constructor))` because callstack printing can be dynamically enabled or disabled from multiple threads by calling `__sanitizer_enable_backtrace`.

All configuration defaults are set in `include/sanitizer/config.h`

## Integrating libfreesan into your project

  # Before you start

  When integrating libfreesan into your project, first consider whether you can
  make use of the sanitizers typically provided with your compiler. Toolchain-
  -supplied sanitizers are guaranteed to have full compatibility with the
  compiler version they ship with, a guarantee this project inherently cannot
  make.

  Demonstration projects showing how to integrate available sanitizers are
  provided in the `demo/` folder.

  # Steps

  1. Compile the relevant sanitizers for your project. The default settings are recommended, but check the documented [configuration options](#configuration-options)
  2. Compile your application with the appropriate `-fsanitize` settings. Refer to the documentation for your compiler version for details. The latest documentation is available [here for GCC](https://gcc.gnu.org/onlinedocs/gcc/Instrumentation-Options.html) and [here for clang](https://clang.llvm.org/docs/UsersManual.html).
  3. Link your application with the sanitizers built in the `lib/` folder. Take care to ensure that the linker correctly picks up the sanitizer libraries we've just built and not any built-in sanitizer runtimes your toolchain may ship with using `ldd` or similar.
  4. Run your application.