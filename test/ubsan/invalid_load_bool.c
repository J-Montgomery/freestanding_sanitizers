#include <stdbool.h>
#include <stdio.h>

unsigned char NotABool = 123;

int main() {
  bool *p = (bool *)&NotABool;

  /* CHECK: invalid value to load in type '_Bool' */
  /* CHECK: \(123\) */
  printf("Test %i\n", *p);

  return 0;
}