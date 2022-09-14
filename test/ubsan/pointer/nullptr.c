#include <stdint.h>
#include <stdio.h>
#include <limits.h>


char *foo(char *a) { return a; }

int main(int argc, char **argv) {

  char *base = (char *)0x0;
  base = base + 1;

  // I have no idea why GCC fails to invoke these, as v9+ all seem to generate
  // the underlying calls to __ubsan_handle_pointer_overflow
  /* CHECK: applying offset 1 to null pointer */
  printf("%p\n", base);

  base = (char *)0x1;
  base = base - 1;

  /* CHECK: pointer 0x[0-9a-f]+ overflowed to base 0x[0-9a-f]+ */
  printf("%p\n", base);

  return 0;
  
}