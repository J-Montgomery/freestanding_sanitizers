#pragma once

#define ATTR_INTERFACE __attribute__((visibility("default")))
#define ATTR_WEAK __attribute__((weak))
#define ATTR_NORETURN __attribute__((noreturn))
#define ATTR_ALIAS(x) __attribute__((alias(x)))

#define SANITIZER_UNRECOVERABLE(sanitizer, fname, ...) \
    extern "C" ATTR_INTERFACE ATTR_NORETURN \
    void __ ## sanitizer ## _handle_ ## fname( __VA_ARGS__ );

#define SANITIZER_RECOVERABLE(sanitizer, fname, ...) \
    extern "C" ATTR_INTERFACE \
    void __ ## sanitizer ## _handle_ ## fname( __VA_ARGS__ ); \
    extern "C" ATTR_INTERFACE ATTR_NORETURN \
    void __ ## sanitizer ## _handle_ ## fname ## _abort( __VA_ARGS__ );