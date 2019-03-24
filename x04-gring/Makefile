all: gring

gring: g-ring.c g-ring.h Makefile main.c
	$(CC) -o $@ -g -Wall -Werror g-ring.c main.c $(shell pkg-config --libs --cflags gobject-2.0)

