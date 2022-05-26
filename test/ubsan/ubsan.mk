TEST_CFLAGS=-ggdb3 -Wall -Wextra -pedantic -std=c99 -fsanitize=undefined
TEST_LDFLAGS=-fsanitize=undefined -Wl,-Llib -Wl,-l:libubsan.a

SRC_DIR = test/ubsan
TEST_SRC += $(wildcard $(SRC_DIR)/*.c)
UBSAN_TESTS := $(patsubst %.c, %, $(TEST_SRC))

%: %.c
	LIBRARY_PATH=./lib $(CC) $(TEST_CFLAGS) $(TEST_LDFLAGS) $< -o $@

ubsan_test: $(UBSAN_TESTS)
	echo '$(UBSAN_TESTS)' '$(TEST_SRC)'