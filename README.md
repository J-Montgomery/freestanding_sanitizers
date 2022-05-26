# Introduction

This is a freestanding implementation of the Undefined Behavior Sanitizer (UBSAN)
and AddressSanitizer (ASAN), compatible with ambiguous, recent versions of LLVM
and GCC. The main use case is for running sanitizers on unusual systems,
particularly embedded platforms where traditional sanitizers may not be
available.

## Features
| Feature             | Implemented        |
|---------------------|--------------------|
| C99                 | :heavy_check_mark: |
| UBSAN               | Partially          |
| ASAN                | :x:                |


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