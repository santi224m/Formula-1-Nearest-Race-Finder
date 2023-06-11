# Variables
CC=g++
CFLAGS=-g -I ./include/
SRCS=./test/sandbox.cpp ./src/data_import.cpp
EXEC=main-tests.out

# Default target
all: $(EXEC)

# Linking the final executable
$(EXEC): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $(EXEC)
    
# 'make tests' will compile and then run the tests
tests: $(EXEC)
	./$(EXEC)

# 'make clean' will remove the executable
clean:
	rm -f $(EXEC)
