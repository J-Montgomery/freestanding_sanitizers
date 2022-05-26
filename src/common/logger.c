#include <stdarg.h>
#include <stdio.h>

#include "logger.h"

// Declare our aliases
EXTERN_C ATTR_ALIAS("__sanitizer_log_puts_impl") void __sanitizer_log_puts(
    LogLevel level, const char *Message);

EXTERN_C __attribute__((format(printf, 2, 3)))
ATTR_ALIAS("__sanitizer_log_printf_impl") void __sanitizer_log_printf(
    LogLevel Level, const char *Format, ...);

static const char *LevelToStr(LogLevel Level) {
  switch (Level) {
  case LOG_ERROR:
    return "Error";
  case LOG_FATAL:
    return "Fatal";
  case LOG_UNKNOWN:
  default:
    return "Unknown";
  }
}

EXTERN_C void __sanitizer_log_puts_impl(LogLevel Level, const char *Message) {
  fprintf(stderr, "%s", LevelToStr(Level));
  fprintf(stderr, "%s", Message);
}

EXTERN_C void __sanitizer_log_printf_impl(LogLevel Level, const char *Format,
                                          ...) {
  va_list Args;
  va_start(Args, Format);
  fprintf(stderr, "%s", LevelToStr(Level));
  fprintf(stderr, Format, Args);
  va_end(Args);
}