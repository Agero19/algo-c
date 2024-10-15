sg_dir = ../sg/
CC = gcc
CFLAGS = -std=c2x \
  -Wall -Wconversion -Werror -Wextra -Wpedantic -Wwrite-strings \
  -O2 \
  -D_POSIX_C_SOURCE=200809L -I$(sg_dir)
LDFLAGS = -lX11 -lm
vpath %.c $(sg_dir)
vpath %.h $(sg_dir)
objects = point_test.o point.o sg.o
executable = point_test

.PHONY: all clean

all: $(executable)

clean:
	$(RM) $(objects) $(executable)

$(executable): $(objects)
	$(CC) $(objects) $(LDFLAGS) -o $(executable)

point_test.o: point_test.c point.h sg.h
point.o: point.c point.h sg.h
sg.o: sg.c sg.h
