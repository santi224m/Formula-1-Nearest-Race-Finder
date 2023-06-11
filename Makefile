# Variables
CC=g++
CFLAGS=-g -I ./include/

# Variables for main program
MAIN_SRCS=./src/main.cpp ./src/data_import.cpp
MAIN_EXEC=main.out

# Variables for tests
TEST_SRCS=./test/sandbox.cpp ./src/data_import.cpp
TEST_EXEC=main-tests.out

# Default target
all: $(MAIN_EXEC) $(TEST_EXEC)

# Building main program
main: $(MAIN_EXEC)

$(MAIN_EXEC): $(MAIN_SRCS)
	$(CC) $(CFLAGS) $(MAIN_SRCS) -o $(MAIN_EXEC)

# Running main program
run: $(MAIN_EXEC)
	./$(MAIN_EXEC)

# Building and running tests
tests: $(TEST_EXEC)
	./$(TEST_EXEC)

$(TEST_EXEC): $(TEST_SRCS)
	$(CC) $(CFLAGS) $(TEST_SRCS) -o $(TEST_EXEC)

# 'make clean' will remove both executables
clean:
	rm -f $(MAIN_EXEC) $(TEST_EXEC)
