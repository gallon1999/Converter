include .config

CC = gcc
CFLAGS = -Wall -IPROJECT/INCLUDE -O3
LDFLAGS = $(shell pkg-config --libs libgpiod) 
OBJ_DIR = obj
SRC_DIR = PROJECT
INC_DIR = PROJECT/INCLUDE


# Files
SRCS = $(SRC_DIR)/main.c \
        $(SRC_DIR)/inc.c

OBJS = $(OBJ_DIR)/main.o \
       $(OBJ_DIR)/inc.o
EXEC = $(PROJNAME)_program

all: $(EXEC)

# Linking main
$(EXEC): $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)

# Compiling source files into object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean object files and executable
clean:
	rm -rf $(OBJ_DIR)/*.o $(EXEC)

# Create object directory if it does not exist
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

.PHONY: all clean
