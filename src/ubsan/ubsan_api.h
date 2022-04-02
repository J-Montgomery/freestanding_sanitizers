#pragma once

#include <sanitizer/interface_utils.h>

#define UNRECOVERABLE(fname, ...)
    SANITIZER_UNRECOVERABLE(ubsan, fname, __VA_ARGS__)

#define RECOVERABLE(fname, ...)
    SANITIZER_RECOVERABLE(ubsan, fname, __VA_ARGS__)