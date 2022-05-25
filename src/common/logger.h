#pragma once

#include <sanitizer/interface_utils.h>

typedef enum { LOG_ERROR, LOG_FATAL, LOG_UNKNOWN } LogLevel;

EXTERN_C void __sanitizer_log_puts(LogLevel level, const char *Message);

EXTERN_C __attribute__((format(printf, 2, 3))) void
__sanitizer_log_printf(LogLevel Level, const char *Format, ...);
