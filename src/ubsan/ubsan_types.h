#pragma once

#include <sanitizer/compiler_internals.h>
#include <sanitizer/interface_utils.h>
#include <sanitizer/platform.h>

typedef struct {
  SourceLocation Loc;
  REFERENCE(const TypeDescriptor) Type;
  unsigned char Alignment;
  unsigned char Kind; // TypeKind
} TypeMismatchData;

typedef struct {
  SourceLocation Loc;
  SourceLocation AssumptionLoc;
  REFERENCE(const TypeDescriptor) Type;
} AlignmentAssumptionData;

typedef struct {
  SourceLocation Loc;
  REFERENCE(const TypeDescriptor) Type;
} OverflowData;

typedef struct {
  SourceLocation Loc;
  REFERENCE(const TypeDescriptor) LHSType;
  REFERENCE(const TypeDescriptor) RHSType;
} ShiftOutOfBoundsData;

typedef struct {
  SourceLocation Loc;
  REFERENCE(const TypeDescriptor) ArrayType;
  REFERENCE(const TypeDescriptor) IndexType;
} OutOfBoundsData;

typedef struct {
  SourceLocation Loc;
} UnreachableData;

typedef struct {
  SourceLocation Loc;
  REFERENCE(const TypeDescriptor) Type;
} VLABoundData;

typedef struct {
  REFERENCE(const TypeDescriptor) FromType;
  REFERENCE(const TypeDescriptor) ToType;
} FloatCastOverflowDataV1;

typedef struct {
  SourceLocation Loc;
  REFERENCE(const TypeDescriptor) FromType;
  REFERENCE(const TypeDescriptor) ToType;
} FloatCastOverflowDataV2;

typedef struct {
  SourceLocation Loc;
  REFERENCE(const TypeDescriptor) Type;
} InvalidValueData;

typedef struct {
  SourceLocation Loc;
  REFERENCE(const TypeDescriptor) FromType;
  REFERENCE(const TypeDescriptor) ToType;
  unsigned char Kind; // ImplicitConversionKind
} ImplicitConversionData;

enum BuiltinCheckKind {
  CTZPassedZero,
  CLZPassedZero,
};

typedef struct {
  SourceLocation Loc;
  unsigned char Kind; // BuiltinKind
} InvalidBuiltinData;

typedef struct {
  SourceLocation LocAttr;
} NonNullReturnData;

typedef struct {
  SourceLocation Loc;
  SourceLocation LocAttr;
  int ArgIndex;
} NonNullArgData;

typedef struct {
  SourceLocation Loc;
} PointerOverflowData;

typedef struct {
  unsigned char Kind; // CFITypeKind
  SourceLocation Loc;
  REFERENCE(const TypeDescriptor) Type;
} CFICheckFailData;

typedef struct {
  SourceLocation Loc;
  REFERENCE(const TypeDescriptor) Type;
} FunctionTypeMismatchData;

typedef struct {
  SourceLocation Loc;
  REFERENCE(const TypeDescriptor) Type;
  void *TypeInfo;
  unsigned char Kind;
} DynamicTypeCacheMissData;
