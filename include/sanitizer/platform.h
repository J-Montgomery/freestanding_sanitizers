#pragma once

#include <stdbool.h>
#include <stdint.h>

typedef unsigned long sys_uptr;
typedef signed long sys_sptr;

// Some systems differentiate this from sys_uptr, it's a reasonable default
typedef sys_uptr sys_uhwptr;
typedef sys_uptr ValuePtr;

