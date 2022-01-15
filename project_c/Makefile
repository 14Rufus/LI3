CC = gcc
INCLUDE = -I headers
CFLAGS = -Wall -g

SRC := src
OBJ := obj

SOURCES := $(wildcard $(SRC)/*.c)

NAME = program

OBJECTS := $(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SOURCES))

all: $(OBJECTS)
	$(CC) $(CFLAGS) $(INCLUDE) -o $(NAME) $(OBJECTS)

.PHONY: clean
clean:
	rm -r $(OBJ)

.PHONY: help
help:
	@echo "src: $(SOURCES)"
	@echo "obj: $(OBJECTS)"

$(OBJ)/%.o: $(SRC)/%.c
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(shell mkdir -p $(OBJ))
