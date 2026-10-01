CC = gcc
CFLAGS = -I include -Wall

SRC = $(shell find src -name "*.c")
OBJ = $(SRC:.c=.o)
TARGET = maze_program

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: clean