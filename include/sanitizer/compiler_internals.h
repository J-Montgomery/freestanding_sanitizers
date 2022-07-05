#pragma once

#include <sanitizer/platform.h>

#if !(defined(__clang__) || defined(__GNUC__) || defined(__GNUG__))
#error "Compiler not supported"
#endif

#define GET_RETURN_ADDR() __builtin_return_address(0)
#define GET_CURRENT_FRAME() __builtin_frame_address(0)

typedef struct {
  char *Filename;
  uint32_t Line;
  uint32_t Column;
} SourceLocation;

typedef struct {
  uint16_t TypeKind; // Value will correspond to enum TK_Kind
  uint16_t TypeInfo;
  uint8_t TypeName[1];
} TypeDescriptor;

typedef enum { TK_Integer = 0x0, TK_Float = 0x1, TK_Unknown = 0xffff } TK_Kind;

TK_Kind getTypeKind(TypeDescriptor desc) {
  return (TK_Kind)desc.TypeKind;
}

char *getTypeName(TypeDescriptor desc) {
  return (char *)desc.TypeName;
}

bool isIntegerType(TypeDescriptor desc) {
  return getTypeKind(desc) == TK_Integer;
}

bool isFloatType(TypeDescriptor desc) {
  return getTypeKind(desc) == TK_Float;
}

bool isSignedIntegerType(TypeDescriptor desc) {
  return isIntegerType(desc) && (desc.TypeInfo & 1);
}

bool isUnsignedIntegerType(TypeDescriptor desc) {
  return isIntegerType(desc) && !(desc.TypeInfo & 1);
}