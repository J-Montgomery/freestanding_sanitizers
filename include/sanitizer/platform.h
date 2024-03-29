#pragma once

#include <stdbool.h>
#include <stdint.h>

typedef unsigned long sys_uptr;
typedef signed long sys_sptr;

// Some systems differentiate this from sys_uptr, it's a reasonable default
typedef sys_uptr sys_uhwptr;
typedef sys_uptr ValuePtr;

#if defined(__x86_64__) || defined(__x86_32__) || defined(__i386)

// Long doubles shouldn't exist, so let's pretend they don't
typedef double floatmax_t;

#define SIntFormat "%li"
#define UIntFormat "%lu"
#define FloatFormat "%lE"
#define LineFormat "%u"
#elif defined(__ARM_ARCH_7R__)
typedef double floatmax_t;
#define SIntFormat "%llu"
#define UIntFormat "%llu"
#define FloatFormat "%lE"
#define LineFormat "%lu"
#else
#error "Define format specifiers for your architecture"
#endif
