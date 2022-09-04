#include <stdint.h>
#include <stdio.h>
#include <float.h>

int main() {

  /* CHECK: cast of type 'float' is outside the range of representable values of type 'unsigned int' */
  /* CHECK: \(-1\.00.*?\) */
  float f = -1.0;
  unsigned u = (unsigned)f;
  printf("%u\n", u);

  /* CHECK: cast of type 'float' is outside the range of representable values of type 'int' */
  int i = FLT_MAX;
  printf("%i\n", i);
  return 0;
}
