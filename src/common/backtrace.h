#pragma once

#include <sanitizer/interface_utils.h>
#include <stdbool.h>

EXTERN_C void __sanitizer_enable_backtrace(bool enable);
EXTERN_C bool __sanitizer_backtrace_enabled(void);
EXTERN_C void __sanitizer_print_backtrace(void);
