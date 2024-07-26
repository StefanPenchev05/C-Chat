#!/bin/bash

# Variables
CC=gcc
CFLAGS="-Wall -Wextra -Iinclude -I/opt/homebrew/opt/mysql-client/include"
LDFLAGS="-L/opt/homebrew/opt/mysql-client/lib"
SRC=src
SERVER_SRC=$SRC/server
GROUPS_SRC=$SRC/groups
BIN=bin
LIBS="-lmysqlclient"

# Source files
SERVER_FILES="$SRC/main.c $SERVER_SRC/server_utils.c $SERVER_SRC/server_network.c $SERVER_SRC/server_commands.c"
GROUP_FILES="$GROUPS_SRC/group.c"  # Add any group-related source files here

# Create bin directory if it doesn't exist
mkdir -p $BIN

# Compile and link the server executable
$CC $CFLAGS $LDFLAGS -o $BIN/server $SERVER_FILES $LIBS

# Compile and link the client executable (if applicable)
# $CC $CFLAGS $LDFLAGS -o $BIN/client $CLIENT_FILES $LIBS

echo "Compilation finished. Executables are in the $BIN directory."