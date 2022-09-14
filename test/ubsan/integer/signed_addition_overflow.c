#include <stdint.h>
#include <stdio.h>

int main() {
  int64_t a = INT64_MAX;

  /* CHECK: signed integer overflow: value cannot be represented in type 'long int' */
  a += 1;

  return 0;
}
