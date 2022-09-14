__attribute__((returns_nonnull, nonnull(1))) char *foo(char *a);

char *foo(char *a) { return a; }

int main(int argc, char **argv) {
  char *a = 0x0;

  /* CHECK: null pointer passed as argument 1, which is declared to never be null */
  /* CHECK: null pointer returned from function declared to never return null */
  foo(a);
  return 0;
}