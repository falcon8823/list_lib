TARGET = list_lib.a
SRCS = double_list.c
HEADERS = double_list.h
OBJS = ${SRCS:.c=.o}

INCLUDES = 
LIBS =

CC = gcc
CCFLAGS = -g -Wall

LD = gcc
LDFLAGS =

AR = ar -qc

#$(TARGET): $(OBJS)
#	$(LD) $(OBJS) $(LDFLAGS) -o $(TARGET) $(LIBS)

$(TARGET): $(OBJS)
	$(RM) $@
	$(AR) $@ $(OBJS)

.c.o:
	$(CC) $(CCFLAGS) $(INCLUDES) -c $<

$(OBJS): $(HEADERS) Makefile

doc: $(SRCS) $(HEADERS)
	cd doc; doxygen

clean:
	rm -f $(TARGET) $(OBJS) core *~ *.a
