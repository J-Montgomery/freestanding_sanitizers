TEST_ASAN_CFLAGS=-ggdb3 -Wall -Wextra -pedantic -std=c99 -fsanitize=address
TEST_ASAN_LDFLAGS=-rdynamic -Wl,-Llib -Wl,-l:libasan.so.1

ASAN_SRC_DIR = test/asan
ASAN_TEST_SRC += $(ASAN_SRC_DIR)/asan_base.c
ASAN_TESTS := $(patsubst %.c, %, $(ASAN_TEST_SRC))

UNUSUAL_ASAN_TEST_SRC += $(ASAN_SRC_DIR)/asan_base.c
UNUSUAL_ASAN_TESTS := $(patsubst %.c, %, $(UNUSUAL_ASAN_TEST_SRC))
UNUSUAL_FLAGS := -fno-sanitize-recover=all


#%: %.c
#	LIBRARY_PATH=./lib $(CC) $(TEST_ASAN_CFLAGS) $(TEST_ASAN_LDFLAGS) $< -o $@

$(UNUSUAL_ASAN_TESTS):
	LIBRARY_PATH=./lib $(CC) $(CFLAGS) $(UNUSUAL_FLAGS) $(TEST_ASAN_CFLAGS) $(TEST_ASAN_LDFLAGS) $(@:=.c) -o $@

build_asan_tests: $(ASAN_TESTS) $(UNUSUAL_ASAN_TESTS)

run_asan_tests: build_asan_tests
	LD_LIBRARY_PATH=./lib python3 test/test_runner.py --verbose -c test/test_config_asan.json $(ASAN_TESTS) $(UNUSUAL_ASAN_TESTS)
