#include <stdint.h>
#include <stdio.h>

int main() {
  double a = 3.14159f;

  printf("Test %f\n", a / 0.0f);

  return 0;
}
