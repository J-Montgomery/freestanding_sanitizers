UBSAN_TEST_CFLAGS=-ggdb3 -Wall -Wextra -pedantic -std=c99 -fsanitize=undefined
UBSAN_TEST_LDFLAGS=-rdynamic -Wl,-Llib -Wl,-l:libubsan.so.1

UBSAN_SRC_DIR = test/ubsan
UBSAN_TEST_SRC += $(UBSAN_SRC_DIR)/signed_addition_overflow.c $(UBSAN_SRC_DIR)/shift_overflow.c $(UBSAN_SRC_DIR)/signed_invalid_division.c $(UBSAN_SRC_DIR)/unsigned_invalid_division.c  $(UBSAN_SRC_DIR)/nonnull_return.c $(UBSAN_SRC_DIR)/invalid_load_bool.c
UBSAN_TESTS := $(patsubst %.c, %, $(UBSAN_TEST_SRC))

UBSAN_UNUSUAL_TEST_SRC += $(UBSAN_SRC_DIR)/test_death_override.c $(UBSAN_SRC_DIR)/float_invalid_division.c
UBSAN_UNUSUAL_TESTS := $(patsubst %.c, %, $(UBSAN_UNUSUAL_TEST_SRC))
UBSAN_UNUSUAL_FLAGS := -fno-sanitize-recover=all -fsanitize=float-divide-by-zero

UBSAN_TEST_LIST_SRC = $(UBSAN_TEST_SRC) $(UBSAN_UNUSUAL_TEST_SRC)
UBSAN_TEST_LIST_EXE = $(UBSAN_TESTS) $(UBSAN_UNUSUAL_TESTS)


$(UBSAN_TESTS):
	LIBRARY_PATH=./lib $(CC) $(UBSAN_TEST_CFLAGS) $(UBSAN_TEST_LDFLAGS) $(@:=.c) -o $@

$(UBSAN_UNUSUAL_TESTS):
	LIBRARY_PATH=./lib $(CC) $(CFLAGS) $(UBSAN_UNUSUAL_FLAGS) $(UBSAN_TEST_CFLAGS) $(UBSAN_TEST_LDFLAGS) $(@:=.c) -o $@

build_ubsan_tests: $(UBSAN_TESTS) $(UBSAN_UNUSUAL_TESTS)

run_ubsan_tests: build_ubsan_tests
	LD_LIBRARY_PATH=./lib python3 test/test_runner.py -s $(UBSAN_TEST_LIST_SRC) -t $(UBSAN_TEST_LIST_EXE)