#include <sanitizer/compiler_internals.h>

#include "asan_api.h"
#include "common/backtrace.h"
#include "common/sanitizer_common.h"

void __asan_init(void) { __sanitizer_log_printf(LOG_ERROR, "%s\n", __func__); }

void __asan_unregister_globals(void) {
  __sanitizer_log_printf(LOG_ERROR, "%s\n", __func__);
}

void __asan_register_globals(void) {
  __sanitizer_log_printf(LOG_ERROR, "%s\n", __func__);
}

void __asan_version_mismatch_check_v8(void) {
  __sanitizer_log_printf(LOG_ERROR, "%s\n", __func__);
}

void __asan_report_load8(void) {
  __sanitizer_log_printf(LOG_ERROR, "%s\n", __func__);
}

void __asan_report_load1(void) {
  __sanitizer_log_printf(LOG_ERROR, "%s\n", __func__);
}

void __asan_report_store4(void) {
  __sanitizer_log_printf(LOG_ERROR, "%s\n", __func__);
}

void __asan_handle_no_return(void) {
  __sanitizer_log_printf(LOG_ERROR, "%s\n", __func__);
}