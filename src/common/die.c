#include "die.h"
#include <stdlib.h>
#include <stdio.h>

#define EXIT_FAILURE_CODE (1)

// Declare our alias
EXTERN_C void ATTR_NORETURN ATTR_ALIAS("__sanitizer_die_impl") Die(void);

EXTERN_C void ATTR_NORETURN __sanitizer_die_impl(void) { printf("died\n"); exit(EXIT_FAILURE_CODE); }