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
