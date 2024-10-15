CC = gcc
CFLAGS = -std=c2x \
  -Wall -Wconversion -Werror -Wextra -Wpedantic -Wwrite-strings \
  -O2 \
  -D_POSIX_C_SOURCE=200809L
LDFLAGS = -lX11
objects = sg_test.o sg.o
executable = sg_test

.PHONY: all clean

all: $(executable)

clean:
	$(RM) $(objects) $(executable)

$(executable): $(objects)
	$(CC) $(objects) $(LDFLAGS) -o $(executable)

sg_test.o: sg_test.c sg.h
sg.o: sg.c sg.h
