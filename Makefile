ASSIGNMENT = csc425phase1
CC = gcc
AR = ar
COBJS = client.o Server.o
CSRCS = ${COBJS:.o=.c}
TARGET = ${COBJS:.o=}
README = README.txt

HDRS = *.h

CFLAGS = -Wall -g -std=gnu99 -I.

UNAME := $(shell uname -s)

all: $(COBJS)
	$(CC) $(CFLAGS) $(INCLUDE) -c $(CSRCS)
	$(CC) $(CFLAGS) $(INCLUDE) client.o -o client
	$(CC) $(CFLAGS) $(INCLUDE) Server.o -o server
	
clean:
	rm -f $(COBJS) $(TARGET)
              
submit: $(CSRCS) $(HDRS)
	tar cvzf $(ASSIGNMENT).tgz $(CSRCS) $(HDRS) Makefile $(README)
