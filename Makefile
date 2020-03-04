CC = gcc
COM = $(CC) -c
LIN = $(CC) -lm
OBJDIR = -o ./bin/$@

SerialDelaunay: main.o display.o types.o
	cd bin && $(LIN) -o SerialDelaunay main.o display.o types.o

main.o: main.c types.h display.h 
	$(COM) main.c $(OBJDIR)

display.o: display.c display.h types.h
	$(COM) display.c $(OBJDIR)

types.o: types.c types.h
	$(COM) types.c $(OBJDIR)

clean:
	rm -rf ./bin/*.o

run:
	./bin/SerialDelaunay