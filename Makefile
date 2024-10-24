# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -g 

# Dependencies (header files)
DEPS = src/graph.h

# Object files
OBJ = src/graph.o src/hash_table.o src/miris.o

# Default target: Build the executable
all: miris

# Link the object files to create the final executable
miris: $(OBJ)
	$(CC) $(OBJ) -o $@

# Compile .o files for each .c file
%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up object files and executable
clean:
	rm -f src/*.o miris

.PHONY: clean
