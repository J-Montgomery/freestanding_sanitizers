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

// ignore FloatCastOverflowData for now

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
  bool FromUnrecoverableLoc;
  sys_uptr pc;
  sys_uptr bp;
} ReportOptions;