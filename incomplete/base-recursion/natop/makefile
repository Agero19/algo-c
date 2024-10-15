nat_dir = ../nat/
natio_dir = ../natio/
CC = gcc
CFLAGS = -std=c2x \
  -Wall -Wconversion -Werror -Wextra -Wpedantic -Wwrite-strings \
  -O2 \
  -I$(nat_dir) -I$(natio_dir)
vpath %.c $(nat_dir):$(natio_dir)
vpath %.h $(nat_dir):$(natio_dir)
objects = natop_test.o nat.o natio.o natop.o
executable = natop_test
makefile_indicator = .\#makefile\#

.PHONY: all clean

all: $(executable)

clean:
	$(RM) $(objects) $(executable)
	@$(RM) $(makefile_indicator)

$(executable): $(objects)
	$(CC) $(objects) -o $(executable)

natop_test.o: natop_test.c nat.h natio.h natop.h
nat.o: nat.c nat.h
natio.o: natio.c natio.h nat.h
natop.o: natop.c natop.h nat.h

include $(makefile_indicator)

$(makefile_indicator): makefile
	@touch $@
	@$(RM) $(objects) $(executable)
