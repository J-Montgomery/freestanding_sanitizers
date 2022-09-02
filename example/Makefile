CFLAGS+=-Werror -Wextra -fsanitize=undefined
LDFLAGS+=-Wl,-l:libubsan.so.1
UBSAN_CFLAGS=CFLAGS="-DSANITIZER_CONFIG_BACKTRACE_ENABLE=0 -nodefaultlibs"

DEMO_SRC += ubsan_demo.c
DEMO_OBJ := $(patsubst %.c, %.o, $(DEMO_SRC))

LIBUBSAN_OBJ = $(../lib/libubsan.so.1)
.PHONY: clean all run

all: ubsan_demo

run: ubsan_demo
	LD_LIBRARY_PATH=../lib ./ubsan_demo

clean:
	rm -f $(DEMO_OBJ) ubsan_demo

%.o: %.c
	$(CC) $(CFLAGS) $(INC_DIR) -c $< -o $@

libubsan: $(LIBUBSAN_OBJ)
	cd .. && $(UBSAN_CFLAGS) $(MAKE) ubsan

ubsan_demo: $(DEMO_OBJ) libubsan
	LIBRARY_PATH=$(realpath ../lib) $(CC) $(CFLAGS) $(LDFLAGS) -o $@ $(DEMO_OBJ)
