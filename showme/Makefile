CC = gcc
CFLAGS = -g -Wall
SHOWFLAGS = -O -DLINUX -I/usr/X11R6/include -L/usr/X11R6/lib

SHODIR = src

.PHONY = clean

showme: $(SHODIR)/showme.c
	$(CC) $(SHOWFLAGS) $< -o $@ -lX11

clean:
	rm showme