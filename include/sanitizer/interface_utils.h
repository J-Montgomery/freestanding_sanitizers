#pragma once

#define ATTR_INTERFACE __attribute__((visibility("default")))
#define ATTR_WEAK __attribute__((weak))
#define ATTR_NORETURN __attribute__((noreturn))
#define ATTR_ALIAS(x) __attribute__((alias(x)))

#ifdef __cplusplus
#define EXTERN_C extern "C"
#else
#define EXTERN_C
#endif

#define SANITIZER_UNRECOVERABLE(sanitizer, fname, ...) \
    EXTERN_C ATTR_INTERFACE ATTR_NORETURN \
    void __ ## sanitizer ## _handle_ ## fname( __VA_ARGS__ );

#define SANITIZER_RECOVERABLE(sanitizer, fname, ...) \
    EXTERN_C ATTR_INTERFACE \
    void __ ## sanitizer ## _handle_ ## fname( __VA_ARGS__ ); \
    EXTERN_C ATTR_INTERFACE ATTR_NORETURN \
    void __ ## sanitizer ## _handle_ ## fname ## _abort( __VA_ARGS__ );

// This macro exists because the compiler APIs are defined by a
// a C++ API for various good reasons. Unfortunately, references
// do not exist in C, but we still want to communicate the
// semantic information in the types. Thus, this trivial
// wrapper
#define REFERENCE(expr) expr *
