#pragma once

#include "ubsan_types.h"
#include <sanitizer/interface_utils.h>

#define UNRECOVERABLE(fname, ...)                                              \
  SANITIZER_UNRECOVERABLE(ubsan, fname, __VA_ARGS__)

#define RECOVERABLE(fname, ...) SANITIZER_RECOVERABLE(ubsan, fname, __VA_ARGS__)

RECOVERABLE(type_mismatch_v1, TypeMismatchData *Data, ValuePtr Pointer)

RECOVERABLE(alignment_assumption, AlignmentAssumptionData *Data,
            ValuePtr Pointer, ValuePtr Alignment, ValuePtr Offset)

// Integer arithmetic overflows
RECOVERABLE(add_overflow, OverflowData *Data, ValuePtr Lhs, ValuePtr Rhs)
RECOVERABLE(sub_overflow, OverflowData *Data, ValuePtr Lhs, ValuePtr Rhs)
RECOVERABLE(mul_overflow, OverflowData *Data, ValuePtr Lhs, ValuePtr Rhs)
RECOVERABLE(negate_overflow, OverflowData *Data, ValuePtr Val)
RECOVERABLE(divrem_overflow, OverflowData *Data, ValuePtr Lhs, ValuePtr Rhs)

RECOVERABLE(shift_out_of_bounds, ShiftOutOfBoundsData *Data, ValuePtr Lhs,
            ValuePtr Rhs)

RECOVERABLE(out_of_bounds, OutOfBoundsData *Data, ValuePtr Index)

RECOVERABLE(vla_bound_not_positive, VLABoundData *Data, ValuePtr Bound)

RECOVERABLE(load_invalid_value, InvalidValueData *Data, ValuePtr Val)

RECOVERABLE(implicit_conversion, ImplicitConversionData *Data, ValuePtr Src,
            ValuePtr Dst)

RECOVERABLE(invalid_builtin, InvalidBuiltinData *Data)

RECOVERABLE(nonnull_return_v1, NonNullReturnData *Data, SourceLocation *Loc)
RECOVERABLE(nullability_return_v1, NonNullReturnData *Data, SourceLocation *Loc)

RECOVERABLE(nonnull_arg, NonNullArgData *Data)
RECOVERABLE(nullability_arg, NonNullArgData *Data)

RECOVERABLE(pointer_overflow, PointerOverflowData *Data, ValuePtr Base,
            ValuePtr Result)

RECOVERABLE(float_cast_overflow, void *Data, ValuePtr From)

UNRECOVERABLE(builtin_unreachable, UnreachableData *Data)
UNRECOVERABLE(missing_return, UnreachableData *Data)

/* C++ APIs that are not fully implemented */
RECOVERABLE(cfi_check_fail, CFICheckFailData *Data, ValuePtr Value,
            sys_uptr ValidVtable)
UNRECOVERABLE(cfi_bad_type, CFICheckFailData *Data, ValuePtr Vtable,
              bool ValidVtable)

RECOVERABLE(function_type_mismatch_v1, FunctionTypeMismatchData *Data,
            ValuePtr Function, ValuePtr calleeRTTI, ValuePtr fnRTTI)

typedef enum UB_Type {
  Err_Unknown,
  Err_NullPtrUse,
  Err_NullPtrWithOffset,
  Err_NullPtrWithNonZeroOffset,
  Err_NullPtrAfterNonZeroOffset,
  Err_PointerOverflowData,
  Err_MisalignedPtrUse,
  Err_AlignmentAssumption,
  Err_InsufficientObjSize,
  Err_SignedIntegerOverflow,
  Err_UnsignedIntegerOverflow,
  Err_IntegerDivByZero,
  Err_InvalidBuiltin,
  Err_ImplicitUnsignedIntegerTruncation,
  Err_ImplicitSignedIntegerTruncation,
  Err_ImplicitIntegerSignChange,
  Err_ImplicitSignedIntegerTruncationOrSignChange,
  Err_InvalidShiftBase,
  Err_InvalidShiftExponent,
  Err_IndexOutOfBounds,
  Err_UnreachableCall,
  Err_MissingReturn,
  Err_NonPositiveVlaIndex,
  Err_FloatCastOverflow,
  Err_InvalidBoolLoad,
  Err_InvalidEnumLoad,
  Err_FunctionTypeMismatch,
  Err_InvalidNullReturn,
  Err_InvalidNullArgument
} UB_Type;
