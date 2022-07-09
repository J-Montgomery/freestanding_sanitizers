TEST_CFLAGS=-ggdb3 -Wall -Wextra -pedantic -std=c99 -fsanitize=undefined
TEST_LDFLAGS=-rdynamic -Wl,-Llib -Wl,-l:libubsan.so.1

SRC_DIR = test/ubsan
TEST_SRC += $(SRC_DIR)/signed_addition_overflow.c $(SRC_DIR)/shift_overflow.c $(SRC_DIR)/signed_invalid_division.c $(SRC_DIR)/unsigned_invalid_division.c 
UBSAN_TESTS := $(patsubst %.c, %, $(TEST_SRC))

UNUSUAL_TEST_SRC += $(SRC_DIR)/test_death_override.c $(SRC_DIR)/float_invalid_division.c $(SRC_DIR)/invalid_load_bool.c
UNUSUAL_UBSAN_TESTS := $(patsubst %.c, %, $(UNUSUAL_TEST_SRC))
UNUSUAL_FLAGS := -fno-sanitize-recover=all -fsanitize=float-divide-by-zero -fsanitize=bool


%: %.c
	LIBRARY_PATH=./lib $(CC) $(TEST_CFLAGS) $(TEST_LDFLAGS) $< -o $@

$(UNUSUAL_UBSAN_TESTS):
	LIBRARY_PATH=./lib $(CC) $(CFLAGS) $(UNUSUAL_FLAGS) $(TEST_CFLAGS) $(TEST_LDFLAGS) $(@:=.c) -o $@

build_ubsan_tests: $(UBSAN_TESTS) $(UNUSUAL_UBSAN_TESTS)

run_ubsan_tests: $(UBSAN_TESTS) $(UNUSUAL_UBSAN_TESTS)
	LD_LIBRARY_PATH=./lib python3 test/test_runner.py --verbose -c test/test_config.json $(UBSAN_TESTS) $(UNUSUAL_UBSAN_TESTS)
