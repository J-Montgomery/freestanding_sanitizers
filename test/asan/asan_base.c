#include <stdio.h>
#include <stdlib.h>

int main() {
  int *nullptr = (void *)0x0;

  // Stub this check while the ASAN runtime is being implemented
  /* CHECK: .*? */
  *nullptr = 1;

  return 0;
}
