#include <stdint.h>
#include <stdio.h>

int main() {
  int64_t a = 1024;

  /* CHECK: (.*)overflow\.c:.*: invalid shift for types */
  /* CHECK: shift base: \(1024\) */
  /* CHECK: shift exponent: \(65\) */
  a <<= 65;

  return 0;
}
