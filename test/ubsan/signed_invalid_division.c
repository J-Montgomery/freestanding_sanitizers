#include <stdint.h>
#include <stdio.h>

int main() {
  int a = -314159;

  /* CHECK: division cannot be represented in type 'int' */
  int b = a / 0;

  return 0;
}
