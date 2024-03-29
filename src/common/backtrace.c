#include <sanitizer/config.h>

#include "backtrace.h"

EXTERN_C void ATTR_ALIAS("__sanitizer_enable_backtrace_impl")
    __sanitizer_enable_backtrace(bool enable);
EXTERN_C bool ATTR_ALIAS("__sanitizer_backtrace_enabled_impl")
    __sanitizer_backtrace_enabled(void);
EXTERN_C void ATTR_ALIAS("__sanitizer_print_backtrace_impl")
    __sanitizer_print_backtrace(void);

#if SANITIZER_CONFIG_BACKTRACE_ENABLE == 1

#include <execinfo.h>

#include <stdatomic.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "logger.h"

#ifdef __STDC_NO_ATOMICS__
#error "Atomics not available on target platform"
#endif

volatile atomic_bool __sanitizer_backtrace_flag;

void ATTR_CONSTRUCTOR __sanitizer_backtrace_init(void) {
  __sanitizer_backtrace_flag =
      ATOMIC_VAR_INIT(SANITIZER_CONFIG_BACKTRACE_RUNTIME_DEFAULT_STATE);
}

EXTERN_C void __sanitizer_enable_backtrace_impl(bool enable) {
  atomic_store_explicit(&__sanitizer_backtrace_flag, enable,
                        memory_order_relaxed);
}

EXTERN_C bool __sanitizer_backtrace_enabled_impl(void) {
  return atomic_load_explicit(&__sanitizer_backtrace_flag,
                              memory_order_relaxed);
}

static void staggered_write(const char *buf, size_t len) {
  while (len > 0) {
    int ret = __sanitizer_log_puts(LOG_SILENT, buf);

    buf += (size_t)ret;
    len -= (size_t)ret;
  }
}

EXTERN_C void __sanitizer_print_backtrace_impl(void) {
  void *bt_ptrs[SANITIZER_CONFIG_BACKTRACE_DEPTH];
  size_t bt_size;
  char **bt_syms;
  unsigned i;

  if (!__sanitizer_backtrace_enabled())
    return;

  bt_size = backtrace(bt_ptrs, SANITIZER_CONFIG_BACKTRACE_DEPTH);
  bt_syms = backtrace_symbols(bt_ptrs, bt_size);

  __sanitizer_log_puts(LOG_SILENT, "Backtrace:\n");
  for (i = SANITIZER_CONFIG_BACKTRACE_START_DEPTH; i < bt_size; i++) {
    size_t len = strlen(bt_syms[i]);

    staggered_write(bt_syms[i], len);
    __sanitizer_log_puts(LOG_SILENT, "\n");
  }

  // backtrace_symbols implicitly mallocs, so we must free()
  free(bt_syms);

  return;
}

#else
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

EXTERN_C void __sanitizer_enable_backtrace_impl(bool enable) { return; }
EXTERN_C bool __sanitizer_backtrace_enabled_impl(void) { return false; }
EXTERN_C void __sanitizer_print_backtrace_impl(void) { return; }

#pragma GCC diagnostic pop
#endif /* SANITIZER_CONFIG_BACKTRACE_ENABLE == 1 */
