CC = gcc
CFLAGS = -Wall -g #-Werror 
DEPS = graph.h
OBJ = graph.o miris.o

# Default target
all: miris

# Compile the graph program
miris: $(OBJ)
	$(CC) -o $@ $(OBJ)

# Compile .o files for each .c file
%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

# Clean up generated files
clean:
	rm -f *.o miris

.PHONY: clean
