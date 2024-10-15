slower_dir = ../slower/
CC = gcc
CFLAGS = -std=c2x \
  -Wall -Wconversion -Werror -Wextra -Wpedantic -Wwrite-strings \
  -O2 \
  -I$(slower_dir)
vpath %.c $(slower_dir)
vpath %.h $(slower_dir)
objects = main.o lslower.o lslower_ext.o slower.o
executable = lslower
makefile_indicator = .\#makefile\#

.PHONY: all clean

all: $(executable)

clean:
	$(RM) $(objects) $(executable)
	@$(RM) $(makefile_indicator)

$(executable): $(objects)
	$(CC) $(objects) -o $(executable)

main.o: main.c lslower.h lslower_ext.h slower.h
lslower.o: lslower.c lslower.h slower.h
lslower_ext.o: lslower_ext.c lslower_ext.h lslower.h slower.h
slower.o: slower.c slower.h

include $(makefile_indicator)

$(makefile_indicator): makefile
	@touch $@
	@$(RM) $(objects) $(executable)
