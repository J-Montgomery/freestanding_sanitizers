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
* stdbool.h
* stdint.h
* GCC or LLVM