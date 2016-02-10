ASSIGNMENT = csc425phase1
CC = gcc
AR = ar
COBJS = client.o server.o
CSRCS = ${COBJS:.o=.c}
INCLUDE = 
LIBS = 

HDRS = *.h

CFLAGS = -Wall -g -std=gnu99 -I.

UNAME := $(shell uname -s)

$(TARGET):	$(COBJS)
		$(AR) -r $@ $(COBJS) 

all:$(COBJS)
	$(CC) $(CFLAGS) $(INCLUDE) -o $@ $(COBJS) $(LIBS)

clean:
	rm -f $(COBJS) $(TARGET)
              
submit: $(CSRCS) $(HDRS)
	tar cvzf $(ASSIGNMENT).tgz $(CSRCS) $(HDRS) Makefile
