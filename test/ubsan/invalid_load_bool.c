#include <stdbool.h>
#include <stdio.h>

unsigned char NotABool = 123;

int main() {
  bool *p = (bool *)&NotABool;

  printf("Test %i\n", *p);

  return 0;
}