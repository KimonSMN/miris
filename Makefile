# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -g 

# Dependencies (header files)
DEPS = graph.h hashtable.h

# Object files
OBJ = graph.o miris.o hashtable.o

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
	rm -f *.o miris

.PHONY: clean
