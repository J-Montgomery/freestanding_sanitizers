#include <stdarg.h>
#include <stdio.h>

#include "logger.h"

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
  puts(Message);
}

EXTERN_C void __sanitizer_log_printf_impl(LogLevel Level, const char *Format,
                                          ...) {
  va_list Args;
  va_start(Args, Format);
  fprintf(stderr, "%s", LevelToStr(Level));
  fprintf(stderr, Format, Args);
  va_end(Args);
}