#include <stdint.h>
#include <stdio.h>
#include <assert.h>
#include <stdalign.h>

int main() {
  char buf[64] __attribute__((aligned (16))) = {0};
  assert(alignof(uint32_t) != 17);

  /* CHECK: load of misaligned address 0x[0-9a-f]+ for type 'uint32_t' which requires [0-9]+ byte alignment */
  uint32_t *u32_ptr = buf + 17;
  printf("%u\n", *u32_ptr);

  /* CHECK: store to misaligned address 0x[0-9a-f]+ for type 'uint32_t' which requires [0-9]+ byte alignment */
  *u32_ptr = 123;

  return 0;
}
