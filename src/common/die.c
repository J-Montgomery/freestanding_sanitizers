#include "die.h"
#include <stdlib.h>

#define EXIT_FAILURE_CODE (1)

// Declare our alias
EXTERN_C void ATTR_NORETURN ATTR_ALIAS("__sanitizer_die_impl") __sanitizer_die(void);

EXTERN_C void ATTR_NORETURN __sanitizer_die_impl(void) { exit(EXIT_FAILURE_CODE); }