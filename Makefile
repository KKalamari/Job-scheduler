CC = g++
CFLAGS = -Wall -std=c++11 -Iinclude

SRC_DIR = src
INC_DIR = include
OBJ_DIR = build

SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SOURCES))

all: jobCommander jobExecutorServer

jobCommander: $(OBJ_DIR)/jobCommander.o
	$(CC) $(CFLAGS) -o jobCommander $(OBJ_DIR)/jobCommander.o

jobExecutorServer: $(OBJ_DIR)/jobExecutorServer.o $(OBJ_DIR)/issueJob.o $(OBJ_DIR)/poll.o $(OBJ_DIR)/setConcurrency.o $(OBJ_DIR)/stop.o $(OBJ_DIR)/triplet_to_string.o
	$(CC) $(CFLAGS) -o jobExecutorServer $(OBJ_DIR)/jobExecutorServer.o $(OBJ_DIR)/issueJob.o $(OBJ_DIR)/poll.o $(OBJ_DIR)/setConcurrency.o $(OBJ_DIR)/stop.o $(OBJ_DIR)/triplet_to_string.o

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR) pipe1 pipe2 jobCommander jobExecutorServer jobExecutorServer.txt

