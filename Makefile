CFLAGS+=-fPIC -ggdb3 -Wall -Wextra -pedantic -std=c99
LDFLAGS+=-shared
INC_DIR=-Iinclude

SRC_DIR=src
COMMON_SRC += $(wildcard $(addsuffix /*.c, $(SRC_DIR)/common))

UBSAN_SRC += $(wildcard $(addsuffix /*.c, $(SRC_DIR)/ubsan))
UBSAN_SRC += $(COMMON_SRC)
UBSAN_OBJ := $(patsubst %.c, %.o, $(UBSAN_SRC))

ASAN_SRC += $(wildcard $(addsuffix /*.c, $(SRC_DIR)/asan))
ASAN_SRC += $(COMMON_SRC)
ASAN_OBJ := $(patsubst %.c, %.o, $(ASAN_SRC))

OUT_DIR=lib

.PHONY: clean

all: ubsan asan

%.o: %.c
	$(CC) $(CFLAGS) $(INC_DIR) -c $< -o $@

libubsan.so: $(UBSAN_OBJ)
	$(CC) $(CFLAGS) $(UBSAN_OBJ) $(LDFLAGS) -o $(OUT_DIR)/$@

ubsan: output_dir libubsan.so

libasan.so: $(ASAN_OBJ)
	$(CC) $(CFLAGS) $(ASAN_OBJ) $(LDFLAGS) -o $(OUT_DIR)/$@

asan: output_dir libasan.so

output_dir:
	@mkdir -p $(OUT_DIR)

format:
	find . -iname *.h -o -iname *.c | xargs clang-format -i

clean:
	rm -f $(UBSAN_OBJ) $(ASAN_OBJ)
	rm -rf $(OUT_DIR)