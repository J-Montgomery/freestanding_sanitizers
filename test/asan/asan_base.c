#include <stdio.h>
#include <stdlib.h>

int main() {
  int *nullptr = (void *)0x0;
  *nullptr = 1;

  return 0;
}
