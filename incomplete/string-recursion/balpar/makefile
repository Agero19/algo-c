CC = gcc
CFLAGS = -std=c2x \
  -Wall -Wconversion -Werror -Wextra -Wpedantic -Wwrite-strings \
  -O2
objects = main.o balpar.o
executable = balpar

.PHONY: all clean

all: $(executable)

clean:
	$(RM) $(objects) $(executable)

$(executable): $(objects)
	$(CC) $(objects) -o $(executable)

main.o: main.c balpar.h
balpar.o: balpar.c balpar.h
