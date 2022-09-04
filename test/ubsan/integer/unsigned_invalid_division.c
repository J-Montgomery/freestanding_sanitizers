#include <stdint.h>
#include <stdio.h>

int main() {
  unsigned a = 314159;

  /* CHECK: division cannot be represented in type 'unsigned int' */
  /* CHECK: dividend: \(314159\) */
  /* CHECK: divisor: \(0\) */
  unsigned b = a / 0;

  return 0;
}
