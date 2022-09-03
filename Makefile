include test/ubsan/ubsan.mk
include test/asan/asan.mk
SRC_DIR=src

CFLAGS+=-fPIC -Wall -Wextra -pedantic -std=c99 -Werror -Os
LDFLAGS+=-shared
INC_DIR=-Iinclude -I$(SRC_DIR)

COMMON_SRC += $(wildcard $(addsuffix /*.c, $(SRC_DIR)/common))

UBSAN_SRC += $(wildcard $(addsuffix /*.c, $(SRC_DIR)/ubsan))
UBSAN_SRC += $(COMMON_SRC)
UBSAN_OBJ := $(patsubst %.c, %.o, $(UBSAN_SRC))

ASAN_SRC += $(wildcard $(addsuffix /*.c, $(SRC_DIR)/asan))
ASAN_SRC += $(COMMON_SRC)
ASAN_OBJ := $(patsubst %.c, %.o, $(ASAN_SRC))

OUT_DIR=lib

.PHONY: clean run_ubsan_tests run_new_ubsan_tests format py-format

all: ubsan asan

%.o: %.c
	$(CC) $(CFLAGS) $(INC_DIR) -c $< -o $@

libubsan.so.1: $(UBSAN_OBJ)
	$(CC) $(CFLAGS) $(UBSAN_OBJ) $(LDFLAGS) -o $(OUT_DIR)/$@

libasan.so.5: $(ASAN_OBJ)
	$(CC) $(CFLAGS) $(ASAN_OBJ) $(LDFLAGS) -o $(OUT_DIR)/$@

#libubsan.a: $(UBSAN_OBJ)
#	ar rcs $(OUT_DIR)/$@ $^

ubsan: output_dir libubsan.so.1

# $(CC) $(CFLAGS) $(ASAN_OBJ) $(LDFLAGS) -o $(OUT_DIR)/$@
#libasan.a: $(ASAN_OBJ)
#	ar rcs $(OUT_DIR)/$@ $^

asan: output_dir libasan.so.5

output_dir:
	@mkdir -p $(OUT_DIR)

format:
	find . -iname *.h -o -iname *.c -not -path "./test/*" | xargs clang-format -i

py-format:
	black test/test_runner.py

test: ubsan asan run_ubsan_tests run_asan_tests

clean:
	rm -f $(UBSAN_OBJ) $(ASAN_OBJ)
	rm -rf $(OUT_DIR)