OUTPUT_DIR = build
INCLUDE_DIR = include
CFLAGS = Wall
LIBS = pthread 
INCLUDE_FILES =channel.h crypto.h datatypes.h lookup.h
CC = gcc


.PHONY: all clean

CSRCS= channel.c main.c lookup.c crypto.c

clean: 
	rm -f $(OUTPUT_DIR)/*.o

all:
	$(CC)  -c $(CSRCS) -I $(INCLUDE_DIR) -l $(LIBS)
	mv *.o $(OUTPUT_DIR)
	make -f $(OUTPUT_DIR)/Makefile all
	
	
