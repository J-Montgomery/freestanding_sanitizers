#include <stdint.h>
#include <stdio.h>

int main() {
  double a = 3.14159f;

  /* CHECK: division cannot be represented in type 'double' */
  /* CHECK: dividend: \(3\.14159.*?\) */
  /* CHECK: divisor: \(0\.0.*?\) */
  printf("Test %f\n", a / 0.0f);

  return 0;
}
