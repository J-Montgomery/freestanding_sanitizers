#include <stdio.h>
#include <stdlib.h>

void __attribute__((noreturn)) Die(void) {
  fprintf(stderr, "Custom Death Message\n");
  printf("Test Successful");
  exit(1);
}

int main() {
  int *nullptr = (void *)0x0;

  /* CHECK: store to null pointer of type 'int' */
  /* CHECK: Custom Death Message\n */
  *nullptr = 1;

  return 0;
}
