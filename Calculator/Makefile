CC=gcc
CFLAGS=-Wall
TARGET=build/app.exe

SRC_DIR=src
OBJ_DIR=build

SRC=$(wildcard $(SRC_DIR)/*.c) $(wildcard $(SRC_DIR)/model/*.c) $(wildcard $(SRC_DIR)/view/*.c) $(wildcard $(SRC_DIR)/controller/*.c)

OBJ=$(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC))

all: compile run

compile: $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@mkdir $(subst /,\,$(@D)) 2> nul || echo off
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir $(OBJ_DIR) 2> nul || echo off

clean:
	del /Q /F $(subst /,\,$(OBJ)) 2> nul
	del /Q $(TARGET).exe 2> nul
	@rmdir /Q /S $(OBJ_DIR) 2> nul || echo off

run: $(TARGET)
	$(TARGET)
