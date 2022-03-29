# Makefile

CFLAGS = --std=c99 -Wall 
LDFLAGS = -Wall -I/usr/local/include -L/usr/local/lib -lmatheval -lm
objects = main.o functions.o

# default
all: newtonPC

# ligacao
newtonPC: $(objects)
	gcc -o newtonPC $(objects) $(LDFLAGS)	

# compilacao
main.o: main.c functions.h
functions.o: functions.c functions.h

# remove tudo que nao for codigo fonte
clean:
	-rm -f $(objects) *~ newtonPC