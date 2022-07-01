#include <sanitizer/compiler_internals.h>

#include "common/sanitizer_common.h"
#include "ubsan_api.h"

static bool LocIsValid(SourceLocation *Loc) {
  return (Loc->Filename != 0) && (Loc->Column != 0);
}

static void EmitError(SourceLocation *Loc, const char *string) {
  if (LocIsValid(Loc)) {

    __sanitizer_log_printf(LOG_SILENT, "Loc %s:%u:%u: %s\n", Loc->Filename,
                           Loc->Line, Loc->Column, string);

  } else {
    __sanitizer_log_printf(LOG_SILENT, "Unknown:N/A:N/A: %s\n", string);
  }
}

static void HandleTypeMismatchImpl(TypeMismatchData *Data, ValuePtr Pointer) {
  EmitError(&Data->Loc, "HandleTypeMismatchImpl");
}

static void HandleAlignmentAssumptionImpl(AlignmentAssumptionData *Data,
                                          ValuePtr Pointer, ValuePtr Alignment,
                                          ValuePtr Offset) {
  EmitError(&Data->Loc, "HandleAlignmentAssumptionImpl");
}

static void HandleIntegerOverflowImpl(OverflowData *Data, ValuePtr LHS,
                                      const char *Op, ValuePtr RHS) {
  EmitError(&Data->Loc, "HandleIntegerOverflowImpl");
  __sanitizer_print_backtrace();
}

static void HandleNegationOverflowImpl(OverflowData *Data, ValuePtr Val) {
  EmitError(&Data->Loc, "HandleNegationOverflowImpl");
}

static void HandleDivremOverflowImpl(OverflowData *Data, ValuePtr LHS,
                                     ValuePtr RHS) {
  EmitError(&Data->Loc, "HandleDivremOverflowImpl");
}

static void HandleShiftOutOfBoundsImpl(ShiftOutOfBoundsData *Data, ValuePtr LHS,
                                       ValuePtr RHS) {
  EmitError(&Data->Loc, "HandleShiftOutOfBoundsImpl");
}

static void HandleOutOfBoundsImpl(OutOfBoundsData *Data, ValuePtr Index) {
  EmitError(&Data->Loc, "HandleOutOfBoundsImpl");
}

static void HandleBuiltinUnreachableImpl(UnreachableData *Data) {
  EmitError(&Data->Loc, "HandleBuiltinUnreachableImpl");
}

static void HandleMissingReturnImpl(UnreachableData *Data) {
  EmitError(&Data->Loc, "HandleMissingReturnImpl");
}

static void HandleVLABoundNotPositive(VLABoundData *Data, ValuePtr Bound) {
  EmitError(&Data->Loc, "HandleVLABoundNotPositive");
}

static void HandleFloatCastOverflow(void *DataPtr, ValuePtr From) {
  // TODO HandleFloatCastOverflow
  EmitError(0, "HandleFloatCastOverflow");
}

static void HandleLoadInvalidValue(InvalidValueData *Data, ValuePtr Vals) {
  EmitError(&Data->Loc, "HandleLoadInvalidValue");
}

static void HandleImplicitConversion(ImplicitConversionData *Data, ValuePtr Src,
                                     ValuePtr Dst) {
  EmitError(&Data->Loc, "HandleImplicitConversion");
}

static void HandleInvalidBuiltin(InvalidBuiltinData *Data) {
  EmitError(&Data->Loc, "HandleInvalidBuiltin");
}

static void HandleNonNullReturn(NonNullReturnData *Data, SourceLocation *LocPtr,
                                bool IsAttr) {
  EmitError(LocPtr, "HandleNonNullReturn");
}

static void HandleNonNullArg(NonNullArgData *Data, bool IsAttr) {
  EmitError(&Data->Loc, "HandleNonNullArg");
}

static void HandlePointerOverflowImpl(PointerOverflowData *Data, ValuePtr Base,
                                      ValuePtr Result) {
  EmitError(&Data->Loc, "HandlePointerOverflowImpl");
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

void __ubsan_handle_negate_overflow(OverflowData *Data, ValuePtr Val) {
  HandleNegationOverflowImpl(Data, Val);
}

void __ubsan_handle_negate_overflow_abort(OverflowData *Data, ValuePtr Val) {
  HandleNegationOverflowImpl(Data, Val);
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

void __ubsan_handle_shift_out_of_bounds(ShiftOutOfBoundsData *Data,
                                        ValuePtr LHS, ValuePtr RHS) {
  HandleShiftOutOfBoundsImpl(Data, LHS, RHS);
}

void __ubsan_handle_shift_out_of_bounds_abort(ShiftOutOfBoundsData *Data,
                                              ValuePtr LHS, ValuePtr RHS) {
  HandleShiftOutOfBoundsImpl(Data, LHS, RHS);
  Die();
}

/******************************************************************************/

void __ubsan_handle_out_of_bounds(OutOfBoundsData *Data, ValuePtr Index) {
  HandleOutOfBoundsImpl(Data, Index);
}

void __ubsan_handle_out_of_bounds_abort(OutOfBoundsData *Data, ValuePtr Index) {
  HandleOutOfBoundsImpl(Data, Index);
  Die();
}

/******************************************************************************/

void __ubsan_handle_vla_bound_not_positive(VLABoundData *Data, ValuePtr Bound) {
  HandleVLABoundNotPositive(Data, Bound);
}

void __ubsan_handle_vla_bound_not_positive_abort(VLABoundData *Data,
                                                 ValuePtr Bound) {
  HandleVLABoundNotPositive(Data, Bound);
  Die();
}

/******************************************************************************/

void __ubsan_handle_float_cast_overflow(void *Data, ValuePtr From) {
  HandleFloatCastOverflow(Data, From);
}

void __ubsan_handle_float_cast_overflow_abort(void *Data, ValuePtr From) {
  HandleFloatCastOverflow(Data, From);
  Die();
}

/******************************************************************************/

void __ubsan_handle_load_invalid_value(InvalidValueData *Data, ValuePtr Val) {
  HandleLoadInvalidValue(Data, Val);
}

void __ubsan_handle_load_invalid_value_abort(InvalidValueData *Data,
                                             ValuePtr Val) {
  HandleLoadInvalidValue(Data, Val);
  Die();
}

/******************************************************************************/

void __ubsan_handle_implicit_conversion(ImplicitConversionData *Data,
                                        ValuePtr Src, ValuePtr Dst) {
  HandleImplicitConversion(Data, Src, Dst);
}

void __ubsan_handle_implicit_conversion_abort(ImplicitConversionData *Data,
                                              ValuePtr Src, ValuePtr Dst) {
  HandleImplicitConversion(Data, Src, Dst);
  Die();
}

/******************************************************************************/

void __ubsan_handle_invalid_builtin(InvalidBuiltinData *Data) {
  HandleInvalidBuiltin(Data);
}

void __ubsan_handle_invalid_builtin_abort(InvalidBuiltinData *Data) {
  HandleInvalidBuiltin(Data);
  Die();
}

/******************************************************************************/

void __ubsan_handle_nonnull_return_v1(NonNullReturnData *Data,
                                      SourceLocation *LocPtr) {
  HandleNonNullReturn(Data, LocPtr, true);
}

void __ubsan_handle_nonnull_return_v1_abort(NonNullReturnData *Data,
                                            SourceLocation *LocPtr) {
  HandleNonNullReturn(Data, LocPtr, true);
  Die();
}

/******************************************************************************/

void __ubsan_handle_nullability_return_v1(NonNullReturnData *Data,
                                          SourceLocation *LocPtr) {
  HandleNonNullReturn(Data, LocPtr, false);
}

void __ubsan_handle_nullability_return_v1_abort(NonNullReturnData *Data,
                                                SourceLocation *LocPtr) {
  HandleNonNullReturn(Data, LocPtr, false);
  Die();
}

/******************************************************************************/

void __ubsan_handle_nonnull_arg(NonNullArgData *Data) {
  HandleNonNullArg(Data, true);
}

void __ubsan_handle_nonnull_arg_abort(NonNullArgData *Data) {
  HandleNonNullArg(Data, true);
  Die();
}

/******************************************************************************/

void __ubsan_handle_pointer_overflow(PointerOverflowData *Data, ValuePtr Base,
                                     ValuePtr Result) {
  HandlePointerOverflowImpl(Data, Base, Result);
}

void __ubsan_handle_pointer_overflow_abort(PointerOverflowData *Data,
                                           ValuePtr Base, ValuePtr Result) {
  HandlePointerOverflowImpl(Data, Base, Result);
  Die();
}
/******************************************************************************/

void __ubsan_handle_builtin_unreachable(UnreachableData *Data) {
  HandleBuiltinUnreachableImpl(Data);
  Die();
}

void __ubsan_handle_missing_return(UnreachableData *Data) {
  HandleMissingReturnImpl(Data);
  Die();
}

/******************************************************************************/

#pragma GCC diagnostic pop
