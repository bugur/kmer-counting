
CC		= g++
SRC_DIR		= src
EXEC_DIR	= bin
SRC		= FileReader.cpp
EXEC		= FileReader
CFLAGS		= -Wno-unused-result -std=c++11 -O3
CLINK		= -lz 

all: FileReader

FileReader:
	mkdir -p bin
	$(CC) $(CFLAGS) $(SRC_DIR)/$(SRC) -o $(EXEC_DIR)/$(EXEC) $(CLINK)
	
clean:
	rm -f $(EXEC_DIR)/$(EXEC)


