# Usage:
# make         # compile all binary and executes
# make clean   # remove all binaries, *~ files and objects

.PHONY: all run $(TARGET) clean

all: $(TARGET) run

CC = gcc

# The CFLAGS variable sets compile flags for gcc:
#  -g        compile with debug information
#  -Wall     give verbose compiler warnings
#  -O0       do not optimize generated code
#  -std=c99  use the C99 standard language definition
CFLAGS = -g -Wall -O0 -std=c99

LDFLAGS = -lm

SOURCES =  ../../lib/decode.c hex_decoder.c

# Changes sources.c to sources.o
OBJECTS = $(SOURCES:.c=.o)

TARGET = hex_decoder

$(TARGET) : $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

run: $(TARGET)
	./$(TARGET)


clean:
	rm -vf *~
	rm -vf $(OBJECTS)
	rm -vf $(TARGET)
