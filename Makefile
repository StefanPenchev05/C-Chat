CC = gcc
CFLAGS = -Wall -Wextra -Iinclude /opt/homebrew/opt/mysql-client/include
SRC = src
OBJ = build
BIN = bin
SOURCES = $(wildcard $(SRC)/*.c)
OBJECTS = $(SOURCES:$(SRC)/%.c=$(OBJ)/%.o)
TARGET_SERVER = $(BIN)/server
TARGET_CLIENT = $(BIN)/client
LIBS = -lmysqlclient

all: $(TARGET_SERVER) $(TARGET_CLIENT)  

$(TARGET_SERVER): $(OBJECTS)
    @mkdir -p $(BIN)
    $(CC) $(CFLAGS) -o $@ $^ $(LIBS)

$(TARGET_CLIENT): $(OBJECTS)
    @mkdir -p $(BIN)
    $(CC) $(CFLAGS) -o $@ $^ $(LIBS)

$(OBJ)/%.o: $(SRC)/%.c
    @mkdir -p $(OBJ)
    $(CC) $(CFLAGS) -c -o $@ $<

clean:
    rm -rf $(OBJ) $(BIN)

.PHONY: all clean
