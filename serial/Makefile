CC = gcc
CFLAGS = -g -Wall
SHOWFLAGS = -O -DLINUX -I/usr/X11R6/include -L/usr/X11R6/lib

OBJDIR = bin
SRCDIR = src
SHODIR = showsrc
RESPATHNOEXT = result
OBJ = $(addprefix $(OBJDIR)/,main.o types.o display.o)
OUT = serial
INC = $(SRCDIR)/*.h
$(OBJDIR)/main.o: DEFS = -DLOG
$(OBJDIR)/display.o: DEFS = -DPTSLIM=300000 -DRESPATHNOEXT=\"$(RESPATHNOEXT)\" 

.PHONY = clean reset draw run

all: $(OUT) showme

$(OUT): $(OBJ)
	$(CC) -o $@ $^

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(INC) | $(OBJDIR)
	$(CC) $(CFLAGS) $(DEFS) -c $< -o $@ 

$(OBJDIR):
	mkdir $@

showme: $(SHODIR)/showme.c
	$(CC) $(SHOWFLAGS) $< -o $@ -lX11

clean:
	rm -f $(OBJDIR)/*.o $(OUT) showme 

reset:
	rm -rf $(OBJDIR) *.node *.ele $(OUT) showme

draw:
	./showme $(RESPATHNOEXT).ele

#Customize recipe. Example: ./$(OUT) -r 3 4
run:
	echo customize in Makefile 
