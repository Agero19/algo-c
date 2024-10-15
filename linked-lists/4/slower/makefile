CC = gcc
CFLAGS = -std=c2x \
  -Wall -Wconversion -Werror -Wextra -Wpedantic -Wwrite-strings \
  -O2 \
  -DLOWER_CARD=8 -DSLOWER_LENGTH=6 -DSLOWER_COMPAR_LENGTH=2
objects = slower_test.o slower.o
executable = slower_test
makefile_indicator = .\#makefile\#

.PHONY: all clean

all: $(executable)

clean:
	$(RM) $(objects) $(executable)
	@$(RM) $(makefile_indicator)

$(executable): $(objects)
	$(CC) $(objects) -o $(executable)

slower_test.o: slower_test.c slower.h
slower.o: slower.c slower.h

include $(makefile_indicator)

$(makefile_indicator): makefile
	@touch $@
	@$(RM) $(objects) $(executable)
