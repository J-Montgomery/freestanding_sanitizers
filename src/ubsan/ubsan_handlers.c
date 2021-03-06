#include <sanitizer/compiler_internals.h>

#include "common/backtrace.h"
#include "common/sanitizer_common.h"
#include "ubsan_api.h"

const char *TypeCheckKinds[] = {"load of",
                                "store to",
                                "reference binding to",
                                "member access within",
                                "member call on",
                                "constructor call on",
                                "downcast of",
                                "downcast of",
                                "upcast of",
                                "cast to virtual base of",
                                "_Nonnull binding to",
                                "dynamic operation on"};

#define EmitError(Loc, ...)                                                    \
  if (LocIsValid(Loc)) {                                                       \
    __sanitizer_log_printf(LOG_SILENT, "%s:%u:%u: ", (Loc)->Filename,          \
                           (Loc)->Line, (Loc)->Column);                        \
  } else {                                                                     \
    __sanitizer_log_printf(LOG_SILENT, "Unknown:N/A:N/A: ");                   \
  }                                                                            \
  __sanitizer_log_printf(LOG_SILENT, __VA_ARGS__)

static bool LocIsValid(SourceLocation *Loc) {
  return (Loc->Filename != 0) && (Loc->Column != 0);
}

void PrintValue(TypeDescriptor Type, ValuePtr Val) {
  if (isSignedIntegerType(Type)) {
    __sanitizer_log_printf(LOG_SILENT, "(%li)\n", getSIntValue(Type, Val));
  } else if (isIntegerType(Type)) {
    __sanitizer_log_printf(LOG_SILENT, "(%li)\n", getUIntValue(Type, Val));
  } else if (isFloatType(Type)) {
    __sanitizer_log_printf(LOG_SILENT, "(%Le)\n", getFPValue(Type, Val));
  } else {
    __sanitizer_log_printf(LOG_SILENT, "unknown value\n");
  }
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

static void HandleTypeMismatchImpl(TypeMismatchData *Data, ValuePtr Pointer) {
  ValuePtr alignment = (ValuePtr)1 << Data->Alignment;

  if (!Pointer) {
    EmitError(&Data->Loc, "%s null pointer of type %s\n",
              TypeCheckKinds[Data->Kind], getTypeName(Data->Type));
  } else if (Pointer & (alignment - 1)) {
    EmitError(&Data->Loc,
              "%s misaligned address %p for type %s which requires %li byte "
              "alignment\n",
              TypeCheckKinds[Data->Kind], (void *)Pointer,
              getTypeName(Data->Type), alignment);
  } else {
    EmitError(
        &Data->Loc,
        "%s address %p with insufficient space for an object of type %s\n",
        TypeCheckKinds[Data->Kind], (void *)Pointer, getTypeName(Data->Type));
  }
}

static void HandleAlignmentAssumptionImpl(AlignmentAssumptionData *Data,
                                          ValuePtr Pointer, ValuePtr Alignment,
                                          ValuePtr Offset) {
  sys_uptr BasePointer = Pointer - Offset;
  sys_uptr AlignmentOffset = BasePointer & (Alignment - 1);

  __sanitizer_print_backtrace();

  EmitError(&Data->Loc,
            "assumption of %li byte alignment for pointer of type %s failed:\n",
            Alignment, getTypeName(Data->Type));

  __sanitizer_log_printf(LOG_SILENT, "\tbase address: (%li)\n", BasePointer);
  __sanitizer_log_printf(LOG_SILENT, "\talignment offset: (%li)\n",
                         AlignmentOffset);

  EmitError(&Data->AssumptionLoc, "alignment assumption was specified here\n");
}

static void HandleIntegerOverflowImpl(OverflowData *Data, ValuePtr LHS,
                                      const char *Op, ValuePtr RHS) {
  bool isSigned = isSignedIntegerType(*Data->Type);

  __sanitizer_print_backtrace();

  if (isSigned) {
    EmitError(
        &Data->Loc,
        "signed integer overflow: value cannot be represented in type %s:\n",
        getTypeName(Data->Type));
    __sanitizer_log_printf(LOG_SILENT, "\t(%li %s %li)\n",
                           getSIntValue(*(Data->Type), LHS), Op, RHS);
  } else {
    EmitError(
        &Data->Loc,
        "unsigned integer overflow: value cannot be represented in type %s:\n",
        getTypeName(Data->Type));
    __sanitizer_log_printf(LOG_SILENT, "\t(%lu %s %lu)\n",
                           getUIntValue(*(Data->Type), LHS), Op, RHS);
  }
}

static void HandleNegationOverflowImpl(OverflowData *Data, ValuePtr Val) {
  __sanitizer_print_backtrace();

  EmitError(&Data->Loc, "negation cannot be represented in type %s:\n",
            getTypeName(Data->Type));

  __sanitizer_log_printf(LOG_SILENT, "\t");
  PrintValue(*Data->Type, Val);
}

static void HandleDivremOverflowImpl(OverflowData *Data, ValuePtr LHS,
                                     ValuePtr RHS) {
  __sanitizer_print_backtrace();

  EmitError(&Data->Loc, "division cannot be represented in type %s:\n",
            getTypeName(Data->Type));

  __sanitizer_log_printf(LOG_SILENT, "\tdividend: ");
  PrintValue(*Data->Type, LHS);

  __sanitizer_log_printf(LOG_SILENT, "\tdivisor: ");
  PrintValue(*Data->Type, RHS);
}

static void HandleShiftOutOfBoundsImpl(ShiftOutOfBoundsData *Data, ValuePtr LHS,
                                       ValuePtr RHS) {
  __sanitizer_print_backtrace();

  EmitError(&Data->Loc, "invalid shift for types %s, %s:\n",
            getTypeName(Data->LHSType), getTypeName(Data->RHSType));

  __sanitizer_log_printf(LOG_SILENT, "\tshift base: ");
  PrintValue(*Data->LHSType, LHS);

  __sanitizer_log_printf(LOG_SILENT, "\tshift exponent: ");
  PrintValue(*Data->RHSType, RHS);
}

static void HandleOutOfBoundsImpl(OutOfBoundsData *Data, ValuePtr Index) {
  __sanitizer_print_backtrace();

  EmitError(&Data->Loc, "index out of bounds for type %s:\n",
            getTypeName(Data->ArrayType));

  __sanitizer_log_printf(LOG_SILENT, "\t");
  PrintValue(*Data->IndexType, Index);
}

static void HandleBuiltinUnreachableImpl(UnreachableData *Data) {
  __sanitizer_print_backtrace();

  EmitError(&Data->Loc, "execution reached an unreacheable program point\n");
}

static void HandleMissingReturnImpl(UnreachableData *Data) {
  __sanitizer_print_backtrace();

  EmitError(&Data->Loc, "execution returned from value-returning function "
                        "without returning a value\n");
}

static void HandleVLABoundNotPositive(VLABoundData *Data, ValuePtr Bound) {
  __sanitizer_print_backtrace();

  EmitError(&Data->Loc,
            "variable length array bound of type %s is non-positive value:\n",
            getTypeName(Data->Type));

  __sanitizer_log_printf(LOG_SILENT, "\t");
  PrintValue(*Data->Type, Bound);
}

static void HandleFloatCastOverflow(void *DataPtr, ValuePtr From,
                                    CallerData CData) {
  uint8_t Descriptor[2];

  __sanitizer_print_backtrace();

  memcpy(&Descriptor, DataPtr, 2);

  // Horrible hack to determine whether this is a v1 or a v2 event.
  // If this is v1, DataPtr will point to type descriptors, which can be
  // either TK_Integer, TK_Float, or TK_Unknown.
  // If this is a v2 event, the first bytes will be a filename that *probably*
  // won't collide with the enum values
  if ((Descriptor[0] + Descriptor[1]) < 2 || (Descriptor[0] == 0xFF) ||
      (Descriptor[1] == 0xFF)) {
    // FloatCastOverflowV1
    // The correct thing to do here is to get the SourceLocation from the caller
    // PC available in CData. However, this would require us to do runtime
    // Symbolization, which would add a lot of code-size and complexity.
    // This library takes the easier, best-effort approach of letting you know
    // that an error occurred. If you want to know where, you can enable
    // backtrace.
    FloatCastOverflowDataV1 Data = *(FloatCastOverflowDataV1 *)DataPtr;
    __sanitizer_log_printf(LOG_SILENT,
                           "cast of type %s is outside the range of "
                           "representable values of type %s:\n\t",
                           getTypeName(Data.FromType),
                           getTypeName(Data.ToType));
    PrintValue(*Data.FromType, From);
  } else {
    // FloatCastOverflowV2
    FloatCastOverflowDataV2 Data = *(FloatCastOverflowDataV2 *)DataPtr;
    EmitError(&Data.Loc,
              "cast of type %s is outside the range of representable values of "
              "type %s:\n\t",
              getTypeName(Data.FromType), getTypeName(Data.ToType));
    PrintValue(*Data.FromType, From);
  }
}

static void HandleLoadInvalidValue(InvalidValueData *Data, ValuePtr Val) {
  __sanitizer_print_backtrace();

  EmitError(&Data->Loc, "invalid value to load in type %s:\n",
            getTypeName(Data->Type));

  __sanitizer_log_printf(LOG_SILENT, "\t");
  PrintValue(*Data->Type, Val);
}

static void HandleImplicitConversion(ImplicitConversionData *Data, ValuePtr Src,
                                     ValuePtr Dst) {
  __sanitizer_print_backtrace();

  EmitError(&Data->Loc,
            "implicit conversion from type %s to type %s changed value:\n",
            getTypeName(Data->FromType), getTypeName(Data->ToType));

  __sanitizer_log_printf(LOG_SILENT, "\tFrom: ");
  PrintValue(*Data->FromType, Src);

  __sanitizer_log_printf(LOG_SILENT,
                         "\t %i-bit:", getIntegerBitWidth(*Data->ToType));
  PrintValue(*Data->ToType, Dst);
}

static void HandleInvalidBuiltin(InvalidBuiltinData *Data) {
  __sanitizer_print_backtrace();
  EmitError(&Data->Loc, "passing invalid value zero to %s\n",
            ((Data->Kind) == CTZPassedZero) ? "ctz" : "clz");
}

static void HandleNonNullReturn(NonNullReturnData *Data, SourceLocation *LocPtr,
                                bool IsAttr) {
  __sanitizer_print_backtrace();
  EmitError(
      LocPtr,
      "null pointer returned from function declared to never return null\n");
}

static void HandleNonNullArg(NonNullArgData *Data, bool IsAttr) {
  __sanitizer_print_backtrace();
  EmitError(&Data->Loc,
            "null pointer passed as argument %i, which is declared to never be "
            "null\n",
            Data->ArgIndex);
}

static void HandlePointerOverflowImpl(PointerOverflowData *Data, ValuePtr Base,
                                      ValuePtr Result) {
  __sanitizer_print_backtrace();

  if (Base == 0) {
    EmitError(&Data->Loc, "applying offset %lx to null pointer\n", Result);
  } else {
    EmitError(&Data->Loc, "pointer 0x%lx overflowed to base 0x%lx\n", Base,
              Result);
  }
}

#pragma GCC diagnostic pop

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
  HandleFloatCastOverflow(Data, From, GET_CALLER_DATA());
}

void __ubsan_handle_float_cast_overflow_abort(void *Data, ValuePtr From) {
  HandleFloatCastOverflow(Data, From, GET_CALLER_DATA());
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
