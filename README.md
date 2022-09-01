# Introduction

Sanitizers are one of the most important modern tools for writing high-quality code in C and C++. Unfortunately developers working on platforms where code quality is the most important like safety-critical devices often lack access to sanitizers. This library provides freestanding sanitizer implementations that can be used in situations where the sanitizers normally shipped with compiler toolchains are either unavailable or unsupported.

This project currently provides a freestanding implementation of the Undefined Behavior Sanitizer (UBSAN) and an in-progress implementation of AddressSanitizer (ASAN), both implemented in C99 and compatible with ambiguous, recent versions of LLVM and GCC.

## Features
| Feature             | Implemented        | Notes |
|---------------------|--------------------|-------|
| C99                 | :heavy_check_mark: |       |
| UBSAN               | :heavy_check_mark: | Only handler APIs |
| ASAN                | :x:                |       |


## Dependencies
* <stdbool.h>
* <stdint.h>
* <stdarg.h>
* GCC or LLVM
* Make
* Python3 (Optional)
  * Used to run and validate test cases.

## Optional Runtime Dependencies
* <stdio.h>
  * Used in the default logging module. Can be omitted by defining a custom function.
* <stdlib.h>
  * Used in the default termination module. Can be omitted by defining a custom function.

## Dev Dependencies