#include "die.h"
#include <sanitizer/config.h>

EXTERN_C void ATTR_NORETURN ATTR_ALIAS("__sanitizer_die_impl") Die(void);

#if SANITIZER_CONFIG_DIE_ENABLE == 1

#include <stdlib.h>

#define EXIT_FAILURE_CODE (1)

EXTERN_C void ATTR_NORETURN __sanitizer_die_impl(void) {
  exit(EXIT_FAILURE_CODE);
}

#else

/* This function *looks* trivial, but we have to be careful to avoid a compiler
 * bug affecting LLVM versions < 12 where infinite loops are not always
 * generated as infinite loops if they're inlineable.
 */
EXTERN_C void ATTR_NORETURN __sanitizer_die_impl(void) {
  while (1) {
  };
}

#endif /* SANITIZER_CONFIG_DIE_ENABLE */
