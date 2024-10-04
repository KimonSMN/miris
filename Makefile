CC = gcc
CFLAGS = -Wall -g
DEPS = graph.h
OBJ = graph.o main.o

# Default target
all: main

# Compile the graph program
main: $(OBJ)
	$(CC) -o $@ $(OBJ)

# Compile .o files for each .c file
%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

# Clean up generated files
clean:
	rm -f *.o main

.PHONY: clean
