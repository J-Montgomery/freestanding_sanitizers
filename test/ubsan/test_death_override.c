#include <stdio.h>
#include <stdlib.h>

void __attribute__((noreturn)) Die(void) {
  fprintf(stderr, "Custom Death Message\n");
  exit(1);
}

int main() {
  int *nullptr = (void *)0x0;
  *nullptr = 1;

  return 0;
}
