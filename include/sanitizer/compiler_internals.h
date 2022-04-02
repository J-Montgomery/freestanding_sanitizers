#pragma once

#include <stdint.h>

#define GET_RETURN_ADDR() __builtin_return_address(0)
#define GET_CURRENT_FRAME() __builtin_frame_address(0)

struct SourceLocation {
    char *Filename;
    uint32_t Line;
    uint32_t Column;
};

struct TypeDescriptor {
    uint16_t TypeKind; // Value will correspond to enum TK_Kind
    uint16_t TypeInfo;
    uint8_t TypeName[1];
};

enum TK_Kind {
    TK_Integer = 0x0,
    TK_Float = 0x1,
    TK_Unknown = 0xffff
};