#pragma once

#include <sanitizer/config.h>
#include <sanitizer/interface_utils.h>

EXTERN_C void ATTR_NORETURN __sanitizer_die(void);
