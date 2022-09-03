ASAN_TEST_CFLAGS=-ggdb3 -Wall -Wextra -pedantic -std=c99 -fsanitize=address
ASAN_TEST_LDFLAGS=-rdynamic -Wl,-Llib -Wl,-l:libasan.so.1

ASAN_SRC_DIR = test/asan
ASAN_TEST_SRC += $(ASAN_SRC_DIR)/asan_base.c
ASAN_TESTS := $(patsubst %.c, %, $(ASAN_TEST_SRC))

ASAN_UNUSUAL_TEST_SRC += $(ASAN_SRC_DIR)/asan_base.c
ASAN_UNUSUAL_TESTS := $(patsubst %.c, %, $(ASAN_UNUSUAL_TEST_SRC))
ASAN_UNUSUAL_FLAGS := -fno-sanitize-recover=all


ASAN_TEST_LIST_SRC = $(ASAN_TEST_SRC) $(ASAN_UNUSUAL_TEST_SRC)
ASAN_TEST_LIST_EXE = $(ASAN_TESTS) $(ASAN_UNUSUAL_TESTS)

$(ASAN_UNUSUAL_TEST_SRC):
	LIBRARY_PATH=./lib $(CC) $(ASAN_TEST_CFLAGS) $(ASAN_TEST_LDFLAGS) $(@:=.c) -o $@

$(ASAN_UNUSUAL_TESTS):
	LIBRARY_PATH=./lib $(CC) $(CFLAGS) $(ASAN_UNUSUAL_FLAGS) $(ASAN_TEST_CFLAGS) $(ASAN_TEST_LDFLAGS) $(@:=.c) -o $@

build_asan_tests: $(ASAN_TESTS) $(ASAN_UNUSUAL_TESTS)

run_asan_tests: build_asan_tests
	LD_LIBRARY_PATH=./lib python3 test/test_runner.py --verbose -s $(ASAN_TEST_LIST_SRC) -t $(ASAN_TEST_LIST_EXE)
