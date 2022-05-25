#include <stdio.h>

// Include to test that everything compiles
#include "ubsan_api.h"

int hello(void) {
  printf("Hello, World!\n");
  return 0;
}