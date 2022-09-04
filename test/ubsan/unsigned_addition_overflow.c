#include <stdint.h>
#include <stdio.h>

/* This test requires -fsanitize=unsigned-integer-overflow, which GCC doesn't
 * support (yet?) */
int main() {
  uint64_t a = UINT64_MAX;

  /* CHECK: (.*)overflow\.c:.*: unsigned integer overflow: value cannot be represented in type 'long int' */
  a += 1;

  return 0;
}
