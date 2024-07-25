CC = gcc
CFLAGS = -Wall -Wextra -Iinclude
SRC = src
OBJ = build

SOURCES = $(wildcard $(SRC)/*.c)
OBJECTS = $(SOURCES:$(SRC)/%.c=$(OBJ)/%.o)
TARGET = c_chat

all: $(TARGET)

$(TARGET): $(OBJECTS)
    $(CC) $(CFLAGS) -o $@ $^

$(OBJ)/%.o: $(SRC)/%.c
    @mkdir -p $(OBJ)
    $(CC) $(CFLAGS) -c -o $@ $<

clean:
    rm -rf $(OBJ) $(TARGET)

.PHONY: all clean
