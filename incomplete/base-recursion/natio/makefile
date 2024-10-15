nat_dir = ../nat/
CC = gcc
CFLAGS = -std=c2x \
  -Wall -Wconversion -Werror -Wextra -Wpedantic -Wwrite-strings \
  -O2 \
  -I$(nat_dir)
vpath %.c $(nat_dir)
vpath %.h $(nat_dir)
objects = natio_test.o nat.o natio.o
executable = natio_test
makefile_indicator = .\#makefile\#

.PHONY: all clean

all: $(executable)

clean:
	$(RM) $(objects) $(executable)
	@$(RM) $(makefile_indicator)

$(executable): $(objects)
	$(CC) $(objects) -o $(executable)

natio_test.o: natio_test.c nat.h natio.h
nat.o: nat.c nat.h
natio.o: natio.c natio.h nat.h

include $(makefile_indicator)

$(makefile_indicator): makefile
	@touch $@
	@$(RM) $(objects) $(executable)
