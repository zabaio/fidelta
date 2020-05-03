CC = gcc
CFLAGS = -g -Wall
SHOWFLAGS = -O -DLINUX -I/usr/X11R6/include -L/usr/X11R6/lib

OBJDIR = bin
SRCDIR = src
SHODIR = ../showme
RESPATHNOEXT = result
OBJ = $(addprefix $(OBJDIR)/,main.o types.o display.o)
OUT = serial
INC = $(SRCDIR)/*.h
$(OBJDIR)/main.o: DEFS = -DLOG
$(OBJDIR)/display.o: DEFS = -DPTSLIM=300000 -DRESPATHNOEXT=\"$(RESPATHNOEXT)\" 

.PHONY = clean reset draw run

$(OUT): $(OBJ)
	$(CC) -o $@ $^

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(INC) | $(OBJDIR)
	$(CC) $(CFLAGS) $(DEFS) -c $< -o $@ 

$(OBJDIR):
	mkdir $@

clean:
	rm -rf $(OBJDIR) $(OUT)

reset: clean
	rm -f *.node *.ele

draw:
	$(SHODIR)/showme $(RESPATHNOEXT).ele

#Customize frequently used recipe. Example: ./$(OUT) -r 3 4
run:
	@echo Customize in Makefile 
