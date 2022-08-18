# OUTPUT_DIR = build
INCLUDE_DIR = include
LIBS = pthread 
INCLUDE_FILES =channel.h crypto.h datatypes.h lookup.h
CC = gcc


.PHONY: all clean


clean: 
	rm -f *.o


all:
	$(CC) -o server  *.o -l $(LIBS)  