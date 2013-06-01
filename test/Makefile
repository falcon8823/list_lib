TARGET = list_test
SRCS = list_test.c
HEADERS = 
OBJS = ${SRCS:.c=.o}

LIBS = ../list_lib.a
INCLUDES = -I../

CC = gcc
CCFLAGS = -g -Wall

LD = gcc
LDFLAGS = 

$(TARGET): $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS) -o $(TARGET) $(LIBS)


.c.o:
	$(CC) $(CCFLAGS) $(INCLUDES) -c $<

$(OBJS): $(HEADERS) Makefile

clean:
	rm -f $(TARGET) $(OBJS) core *~
