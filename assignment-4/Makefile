CC      = gcc
CFLAGS  = -O3 -Wall -std=c99
LDFLAGS = -lm
TARGET  = sum_test

SRC = main.c sum_algorithms.c
HDR = sum_algorithms.h
OBJ = $(SRC:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET) $(LDFLAGS)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all run clean
