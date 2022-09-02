#include <stdio.h>

int main(int argv, char **argc) {
  printf("Hello, World!\n");

  int *nullptr = (void *)0x0;
  *nullptr = 1;

  return 0;
}
