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
RECOVERABLE(addition_overflow, OverflowData *Data, ValuePtr Lhs, ValuePtr Rhs)
RECOVERABLE(sub_overflow, OverflowData *Data, ValuePtr Lhs, ValuePtr Rhs)
RECOVERABLE(mul_overflow, OverflowData *Data, ValuePtr Lhs, ValuePtr Rhs)
RECOVERABLE(negate_overflow, OverflowData *Data, ValuePtr OldVal)
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

RECOVERABLE(cfi_check_fail, CFICheckFailData *Data, ValuePtr Function,
            sys_uptr VtableIsValid)

// Don't handle until the version compatibility issues are sorted
// RECOVERABLE(float_cast_overflow, void *Data, ValuePtr From)

UNRECOVERABLE(builtin_unreachable, UnreachableData *Data)
UNRECOVERABLE(missing_return, UnreachableData *Data)