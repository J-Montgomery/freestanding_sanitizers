__attribute__((returns_nonnull)) char *foo(char *a);

/* CHECK: null pointer returned from function declared to never return null */
char *foo(char *a) { return a; }

int main(int argc, char **argv) {
  // use the second element of argv as a null pointer the compiler can't see
  char *a = argv[1];

  foo(a);
  return 0;
}