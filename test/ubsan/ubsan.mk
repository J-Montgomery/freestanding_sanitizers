TEST_CFLAGS=-ggdb3 -Wall -Wextra -pedantic -std=c99 -fsanitize=undefined
TEST_LDFLAGS=-fsanitize=undefined -Wl,-Llib -Wl,-l:libubsan.so.1

SRC_DIR = test/ubsan
TEST_SRC += $(wildcard $(SRC_DIR)/*.c)
UBSAN_TESTS := $(patsubst %.c, %, $(TEST_SRC))

%: %.c
	LIBRARY_PATH=./lib $(CC) $(TEST_CFLAGS) $(TEST_LDFLAGS) $< -o $@

build_ubsan_tests: $(UBSAN_TESTS)

run_ubsan_tests: $(UBSAN_TESTS)
	LD_LIBRARY_PATH=./lib python3 test/test_runner.py -c test/test_config.json $(UBSAN_TESTS)
