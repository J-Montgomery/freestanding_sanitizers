#include <stdint.h>
#include <stdio.h>

/* This test requires -fsanitize=unsigned-integer-overflow, which GCC doesn't
 * support (yet?) */
int main() {
  uint64_t a = UINT64_MAX;

  a += 1;
  printf("Test %lu\n", a);

  return 0;
}
