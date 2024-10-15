point_dir = ../point/
sg_dir = ../sg/
CC = gcc
CFLAGS = -std=c2x \
  -Wall -Wconversion -Werror -Wextra -Wpedantic -Wwrite-strings \
  -O2 \
  -D_POSIX_C_SOURCE=200809L -I$(point_dir) -I$(sg_dir)
LDFLAGS = -lX11 -lm
vpath %.c $(point_dir):$(sg_dir)
vpath %.h $(point_dir):$(sg_dir)
objects = main.o fractal.o point.o sg.o
executable = fractal

.PHONY: all clean

all: $(executable)

clean:
	$(RM) $(objects) $(executable)
	@$(RM) $(makefile_indicator)

$(executable): $(objects)
	$(CC) $(objects) $(LDFLAGS) -o $(executable)

main.o: main.c fractal.h sg.h
fractal.o: fractal.c fractal.h point.h sg.h
point.o: point.c point.h sg.h
sg.o: sg.c sg.h
