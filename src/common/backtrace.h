#pragma once

#include <stdbool.h>
#include <sanitizer/config.h>
#include <sanitizer/interface_utils.h>

EXTERN_C void __sanitizer_enable_backtrace(bool enable);
EXTERN_C bool __sanitizer_backtrace_enabled(void);
EXTERN_C void __sanitizer_print_backtrace(void);
