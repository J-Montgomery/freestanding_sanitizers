TEST_CFLAGS=-ggdb3 -Wall -Wextra -pedantic -std=c99 -fsanitize=undefined
TEST_LDFLAGS=-rdynamic -Wl,-Llib -Wl,-l:libubsan.so.1

SRC_DIR = test/ubsan
TEST_SRC += $(SRC_DIR)/addition_overflow.c $(SRC_DIR)/shift_overflow.c
UBSAN_TESTS := $(patsubst %.c, %, $(TEST_SRC))

ABORT_TEST_SRC += $(SRC_DIR)/test_death_override.c
ABORT_UBSAN_TESTS := $(patsubst %.c, %, $(ABORT_TEST_SRC))


%: %.c
	LIBRARY_PATH=./lib $(CC) $(TEST_CFLAGS) $(TEST_LDFLAGS) $< -o $@

$(ABORT_UBSAN_TESTS):
	LIBRARY_PATH=./lib $(CC) -fno-sanitize-recover=all $(CFLAGS) $(TEST_CFLAGS) $(TEST_LDFLAGS) $(@:=.c) -o $@

build_ubsan_tests: $(UBSAN_TESTS) $(ABORT_UBSAN_TESTS)

run_ubsan_tests: $(UBSAN_TESTS) $(ABORT_UBSAN_TESTS)
	LD_LIBRARY_PATH=./lib python3 test/test_runner.py --verbose -c test/test_config.json $(UBSAN_TESTS) $(ABORT_UBSAN_TESTS)
