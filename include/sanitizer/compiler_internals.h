#pragma once

#include <sanitizer/platform.h>
#include <string.h>

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

TK_Kind getTypeKind(const TypeDescriptor desc) {
  return (TK_Kind)desc.TypeKind;
}

char *getTypeName(const TypeDescriptor *desc) { return (char *)desc->TypeName; }

int getIntegerBitWidth(const TypeDescriptor desc) {
  return 1 << (desc.TypeInfo >> 1);
}

int getFloatBitWidth(const TypeDescriptor desc) { return desc.TypeInfo; }

bool isIntegerType(const TypeDescriptor desc) {
  return getTypeKind(desc) == TK_Integer;
}

bool isFloatType(const TypeDescriptor desc) {
  return getTypeKind(desc) == TK_Float;
}

bool isSignedIntegerType(const TypeDescriptor desc) {
  return isIntegerType(desc) && (desc.TypeInfo & 1);
}

bool isUnsignedIntegerType(const TypeDescriptor desc) {
  return isIntegerType(desc) && !(desc.TypeInfo & 1);
}

bool isInlineInt(const TypeDescriptor desc) {
  const unsigned InlineSize = sizeof(ValuePtr) * 8;
  const unsigned TypeWidth = getIntegerBitWidth(desc);
  return TypeWidth <= InlineSize;
}

bool isInlineFloat(const TypeDescriptor desc) {
  const unsigned InlineSize = sizeof(ValuePtr) * 8;
  const unsigned TypeWidth = getFloatBitWidth(desc);
  return TypeWidth <= InlineSize;
}

uintmax_t getSIntValue(const TypeDescriptor desc, ValuePtr val) {
  // TODO: handle isUnsignedIntegerType(desc) == false

  if (isInlineInt(desc)) {
    const unsigned offset = sizeof(intmax_t) * 8 - getIntegerBitWidth(desc);
    return ((intmax_t)val << offset) >> offset;
  } else // let the compiler zero-extend the value
    return *(intmax_t *)val;
}

intmax_t getUIntValue(const TypeDescriptor desc, ValuePtr val) {
  if (isInlineInt(desc))
    return val;
  else
    return *(uintmax_t *)val;
}

floatmax_t getFPValue(const TypeDescriptor desc, ValuePtr val) {

  if (isInlineFloat(desc)) {
    switch (getFloatBitWidth(desc)) {
    default:
    case 32: {
      float value;
#if defined(__BYTE_ORDER__) && (__BYTE_ORDER__ == __ORDER_BIG_ENDIAN__)
      memcpy(&value, ((const char *)(&val + 1)) - 4, 4);
#else
      memcpy(&value, &val, 4);
#endif
      return value;
    }
    case 64: {
      double value;
      memcpy(&value, &val, 8);
      return value;
    }
    }
  } else {
    switch (getFloatBitWidth(desc)) {
    case 32:
      return *(float *)val;
    case 64:
      return *(double *)val;
    default:
      return *(floatmax_t *)val;
    }
  }
}
