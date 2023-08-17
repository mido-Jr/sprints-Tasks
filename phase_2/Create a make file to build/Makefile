# Makefile for building main.cpp

# Compiler and compiler flags
CXX := g++
CXXFLAGS := -Wall -Wextra -std=c++11

# Directories
BUILD_DIR := build
INSTALL_DIR := $(BUILD_DIR)/usr/bin

# Source file and target executable
SRC := main.cpp
OBJ := $(BUILD_DIR)/main.o
TARGET := myapp

# Targets
all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(TARGET)

$(OBJ): $(SRC)
	mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $(SRC) -o $(OBJ)

clean:
	rm -rf $(BUILD_DIR)/*

install: $(TARGET)
	mkdir -p $(INSTALL_DIR)
	cp $(TARGET) $(INSTALL_DIR)/$(TARGET)

.PHONY: all clean install
