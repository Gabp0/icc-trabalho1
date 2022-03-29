# Makefile

CC = gcc
CFLAGS = --std=c99 -Wall 
CPPFLAGS = -I/usr/local/include 
LDFLAGS = -L/usr/local/lib 
LDLIBS = -lm -lmatheval
objects = main.o functions.o newtonIndexado.o newtonModificado.o newtonPadrao.o

# default
all: newtonPC

# ligacao
newtonPC: $(objects)
	$(CC) -o newtonPC $(objects) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) $(LDLIBS)

# compilacao
main.o: main.c functions.h
functions.o: functions.c functions.h	
newtonIndexado.o: newtonIndexado.c newtonIndexado.h
newtonModificado.o: newtonModificado.c newtonModificado.h
newtonPadrao.o: newtonPadrao.c newtonPadrao.h

# remove tudo que nao for codigo fonte
clean:
	-rm -f $(objects) *~ newtonPC