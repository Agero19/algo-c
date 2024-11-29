stack_dir = ../stack/
CC = gcc
CFLAGS = -std=c2x \
  -Wall -Wconversion -Werror -Wextra -Wpedantic -Wwrite-strings \
  -O2 -DWANT_STACK_EXT \
  -I$(stack_dir)
vpath %.c $(stack_dir)
vpath %.h $(stack_dir)
objects = main.o stack.o
executable = sortwords
makefile_indicator = .\#makefile\#

.PHONY: all clean

all: $(executable)

clean:
	$(RM) $(objects) $(executable)
	@$(RM) $(makefile_indicator)

$(executable): $(objects)
	$(CC) $(objects) -o $(executable)

main.o: main.c stack.h stack_ip.h
stack.o: stack.c stack.h stack_ip.h

include $(makefile_indicator)

$(makefile_indicator): makefile
	@touch $@
	@$(RM) $(objects) $(executable)
