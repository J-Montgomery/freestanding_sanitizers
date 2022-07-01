#include <stdint.h>
#include <stdio.h>

int main() {
  int64_t a = 0x1001;

  a <<= 65;
  printf("Test %lu\n", a);

  return 0;
}
