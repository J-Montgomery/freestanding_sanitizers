#include <stdint.h>
#include <stdio.h>

int main() {
  unsigned a = 314159;

  printf("Test %u\n", a / 0);

  return 0;
}
