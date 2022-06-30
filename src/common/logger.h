#pragma once

#include <sanitizer/config.h>
#include <sanitizer/interface_utils.h>

typedef enum { LOG_SILENT, LOG_ERROR, LOG_FATAL, LOG_UNKNOWN } LogLevel;

EXTERN_C int __sanitizer_log_puts(LogLevel level, const char *Message);

EXTERN_C __attribute__((format(printf, 2, 3))) int
__sanitizer_log_printf(LogLevel Level, const char *Format, ...);
