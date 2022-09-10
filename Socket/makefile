CC=gcc
CFLAGS=-c -Wall -g
FLAGS=-o
INCLUDE=-I../include/
SRC=../src/
OBJ=../obj/
HEADER=../include/
OUTPUT=../bin/

ALL: $(OUTPUT)client $(OUTPUT)server

$(OUTPUT)client: $(OBJ)my_client.o $(OBJ)function.o
	$(CC) $(FLAGS) client $(OBJ)my_client.o $(OBJ)function.o
	mv client $(OUTPUT)

$(OBJ)my_client.o: $(SRC)my_client.c $(HEADER)header.h
	$(CC) $(INCLUDE) $(CFLAGS) $(SRC)my_client.c
	mv my_client.o $(OBJ)

$(OBJ)function.o: $(SRC)function.c $(HEADER)header.h
	$(CC) $(INCLUDE) $(CFLAGS) $(SRC)function.c
	mv function.o $(OBJ)

$(OUTPUT)server: $(OBJ)my_server.o $(OBJ)function.o
	$(CC) $(FLAGS) server $(OBJ)my_server.o $(OBJ)function.o
	mv server $(OUTPUT)

$(OBJ)my_server.o: $(SRC)my_server.c $(HEADER)header.h
	$(CC) $(INCLUDE) $(CFLAGS) $(SRC)my_server.c
	mv my_server.o $(OBJ)

clean:
	rm $(OBJ)*.o
	rm $(OUTPUT)client $(OUTPUT)server
