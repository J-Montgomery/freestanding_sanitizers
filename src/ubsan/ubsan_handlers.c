#include "common/sanitizer_common.h"
#include "ubsan_api.h"
#include <sanitizer/compiler_internals.h>

static void HandleTypeMismatchImpl(TypeMismatchData *Data, ValuePtr Pointer) {
  __sanitizer_log_puts(LOG_ERROR, "HandleTypeMismatchImpl");
}

static void HandleAlignmentAssumptionImpl(AlignmentAssumptionData *Data,
                                          ValuePtr Pointer, ValuePtr Alignment,
                                          ValuePtr Offset) {
  __sanitizer_log_puts(LOG_ERROR, "HandleAlignmentAssumptionImpl");
}

static void HandleIntegerOverflowImpl(OverflowData *Data, ValuePtr LHS,
                                      const char *Op, ValuePtr RHS) {
  __sanitizer_log_puts(LOG_ERROR, "HandleIntegerOverflowImpl");
}

static void HandleNegationOverflowImpl(OverflowData *Data, ValuePtr OldVal) {
  __sanitizer_log_puts(LOG_ERROR, "HandleNegationOverflowImpl");
}

static void HandleDivremOverflowImpl(OverflowData *Data, ValuePtr LHS,
                                     ValuePtr RHS) {
  __sanitizer_log_puts(LOG_ERROR, "HandleDivremOverflowImpl");
}

/******************************************************************************
 * We know that all of these functions will be unused because they're called
 * asynchronously by the compiler. Since we want to adhere to strict compiler
 * warnings otherwise, we disable only the faulty warnings for as few
 * functions as possible
 ******************************************************************************/
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

/******************************************************************************/

void __ubsan_handle_alignment_assumption(AlignmentAssumptionData *Data,
                                         ValuePtr Pointer, ValuePtr Alignment,
                                         ValuePtr Offset) {
  HandleAlignmentAssumptionImpl(Data, Pointer, Alignment, Offset);
}

void __ubsan_handle_alignment_assumption_abort(AlignmentAssumptionData *Data,
                                               ValuePtr Pointer,
                                               ValuePtr Alignment,
                                               ValuePtr Offset) {
  HandleAlignmentAssumptionImpl(Data, Pointer, Alignment, Offset);
  Die();
}

/******************************************************************************/

void __ubsan_handle_add_overflow(OverflowData *Data, ValuePtr LHS,
                                 ValuePtr RHS) {
  HandleIntegerOverflowImpl(Data, LHS, "+", RHS);
}

void __ubsan_handle_add_overflow_abort(OverflowData *Data, ValuePtr LHS,
                                       ValuePtr RHS) {
  HandleIntegerOverflowImpl(Data, LHS, "+", RHS);
  Die();
}

void __ubsan_handle_sub_overflow(OverflowData *Data, ValuePtr LHS,
                                 ValuePtr RHS) {
  HandleIntegerOverflowImpl(Data, LHS, "-", RHS);
}

void __ubsan_handle_sub_overflow_abort(OverflowData *Data, ValuePtr LHS,
                                       ValuePtr RHS) {
  HandleIntegerOverflowImpl(Data, LHS, "-", RHS);
  Die();
}

void __ubsan_handle_mul_overflow(OverflowData *Data, ValuePtr LHS,
                                 ValuePtr RHS) {
  HandleIntegerOverflowImpl(Data, LHS, "*", RHS);
}

void __ubsan_handle_mul_overflow_abort(OverflowData *Data, ValuePtr LHS,
                                       ValuePtr RHS) {
  HandleIntegerOverflowImpl(Data, LHS, "*", RHS);
  Die();
}

/******************************************************************************/

void __ubsan_handle_negate_overflow(OverflowData *Data, ValuePtr OldVal) {
  HandleNegationOverflowImpl(Data, OldVal);
}

void __ubsan_handle_negate_overflow_abort(OverflowData *Data, ValuePtr OldVal) {
  HandleNegationOverflowImpl(Data, OldVal);
  Die();
}

/******************************************************************************/

void __ubsan_handle_divrem_overflow(OverflowData *Data, ValuePtr LHS,
                                    ValuePtr RHS) {
  HandleDivremOverflowImpl(Data, LHS, RHS);
}

void __ubsan_handle_divrem_overflow_abort(OverflowData *Data, ValuePtr LHS,
                                          ValuePtr RHS) {
  HandleDivremOverflowImpl(Data, LHS, RHS);
  Die();
}

/******************************************************************************/

#pragma GCC diagnostic pop
