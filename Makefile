CC = gcc
CFLAGS = -g -Wall
TARGETS = main
OBJECTS = main.c members.o
.SUFFIXES = .c .o

$(TARGETS) : $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

.c.o :
	$(CC) $(CFLAGS) -c $<

clean :
	rm *.o $(TARGETS)
