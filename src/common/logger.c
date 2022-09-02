#include <stdarg.h>
#include <stdio.h>

#include "logger.h"

// Declare our aliases
EXTERN_C ATTR_ALIAS("__sanitizer_log_puts_impl") int __sanitizer_log_puts(
    LogLevel level, const char *Message);

EXTERN_C __attribute__((format(printf, 2, 3)))
ATTR_ALIAS("__sanitizer_log_printf_impl") int __sanitizer_log_printf(
    LogLevel Level, const char *Format, ...);

#if SANITIZER_CONFIG_LOGGER_ENABLE == 1

static const char *LevelToStr(LogLevel Level) {
  switch (Level) {
  case LOG_SILENT:
    return "";
  case LOG_ERROR:
    return "Error: ";
  case LOG_FATAL:
    return "Fatal: ";
  case LOG_UNKNOWN:
  default:
    return "Unknown: ";
  }
}

EXTERN_C int __sanitizer_log_puts_impl(LogLevel Level, const char *Message) {
  fprintf(stderr, "%s", LevelToStr(Level));
  return fprintf(stderr, "%s", Message);
}

EXTERN_C int __sanitizer_log_printf_impl(LogLevel Level, const char *Format,
                                         ...) {
  int bytes;
  va_list Args;
  va_start(Args, Format);
  fprintf(stderr, "%s", LevelToStr(Level));
  bytes = vfprintf(stderr, Format, Args);
  va_end(Args);

  return bytes;
}

#else

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

EXTERN_C int __sanitizer_log_puts_impl(LogLevel Level, const char *Message) {
  return 0;
}
EXTERN_C int __sanitizer_log_printf_impl(LogLevel Level, const char *Format,
                                         ...) {
  return 0;
}

#pragma GCC diagnostic pop

#endif /* SANITIZER_CONFIG_LOGGER_ENABLE */
