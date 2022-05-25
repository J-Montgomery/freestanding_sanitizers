#include "common/sanitizer_common.h"
#include "ubsan_api.h"
#include <sanitizer/compiler_internals.h>

static void HandleTypeMismatchImpl(TypeMismatchData *Data, ValuePtr Pointer) {
  __sanitizer_log_puts(LOG_ERROR, "HandleTypeMismatchImpl");
}

// We know that all of these functions will be unused because they're called
// asynchronously by the compiler. Since we want to adhere to strict compiler
// warnings otherwise, we disable only the faulty warnings for as few
// functions as possible
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-function"

void __ubsan_handle_type_mismatch_v1(TypeMismatchData *Data, ValuePtr Pointer) {
  HandleTypeMismatchImpl(Data, Pointer);
}

void __ubsan_handle_type_mismatch_v1_abort(TypeMismatchData *Data,
                                           ValuePtr Pointer) {
  HandleTypeMismatchImpl(Data, Pointer);
  Die();
}
#pragma GCC diagnostic pop
