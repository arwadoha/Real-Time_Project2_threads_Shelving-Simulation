CC = gcc
CFLAGS = -lpthread
LIBS_INTERFACE = -lglut -lGLU -lGL -lm -lpthread

main: main.c
	$(CC) -o $@ $^ $(CFLAGS)

interface: interface.c
	$(CC) -o $@ $^ $(LIBS_INTERFACE)

clean:
	rm -f main interface

