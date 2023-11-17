CFLAGS := --std=c11 -g -Wall -Werror -Wpedantic $(shell pkg-config --cflags ncurses)
LDFLAGS := $(shell pkg-config --libs ncurses)
SRCS := $(wildcard *.c)
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)

.PHONY: all
all: clean linux

linux:
	gcc ${CFLAGS} ${SRCS} -o at ${LDFLAGS}

.PHONY: clean
clean:
	rm *.o ./at || true

test-memory: linux
	valgrind ./at

.PHONY: docs
docs:
	doxygen

windows:
	x86_64-w64-mingw32-gcc *.c -o test.exe -lcurses -l:libgcc_eh.a  -l:libstdc++.a
