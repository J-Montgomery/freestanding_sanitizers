#include <stdbool.h>
#include <stdio.h>


unsigned char NotABool = 123;

int main() {
  bool *p = (bool*)&NotABool;

  printf("Test %p\n", (void *)p);

  return 0;
}

#pragma GCC diagnostic pop