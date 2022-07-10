#include <sanitizer/compiler_internals.h>

#include "common/backtrace.h"
#include "common/sanitizer_common.h"
#include "asan_api.h"


void __asan_init(void) {}

void __asan_unregister_globals(void) {}

void __asan_register_globals(void) {}

void __asan_version_mismatch_check_v8(void) {}

void __asan_report_load8(void) {}

void __asan_report_load1(void) {}

void __asan_report_store4(void) {}

void __asan_handle_no_return(void) {}