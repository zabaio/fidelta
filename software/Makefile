CC = g++
CFLAGS = -g -Wall 
SHOWFLAGS = -O -DLINUX -I/usr/X11R6/include -L/usr/X11R6/lib

OBJDIR = bin
SRCDIR = src
SHODIR = ../showme
OBJ = $(addprefix $(OBJDIR)/,fidelta.o types.o display.o)
OUT = fidelta
INC = $(SRCDIR)/*.h

RESPATHNOEXT = result
MAXQUERY = 30
PTSLIM = 1000000
$(OBJDIR)/fidelta.o: DEFS = -DMAXQUERY=$(MAXQUERY) -DPTSLIM=$(PTSLIM)
$(OBJDIR)/display.o: DEFS = -DRESPATHNOEXT=\"$(RESPATHNOEXT)\" -DPTSLIM=$(PTSLIM)

.PHONY = clean reset draw run

$(OUT): $(OBJ)
	$(CC) -o $@ $^

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(INC) | $(OBJDIR)
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
