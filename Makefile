CC = gcc
COM = $(CC) -c -g
LIN = $(CC)
OBJDIR = -o ./bin/$@
PTS_FILE_NAME = random
TRIANGLE_EXE = ../triangle/triangle
TRIANGLE_INPUT = ./files/$(PTS_FILE_NAME).node
SHOWME_EXE = ../triangle/showme
SHOWME_INPUT = ./files/$(PTS_FILE_NAME).1.ele


SerialDelaunay: main.o display.o types.o
	cd bin && $(LIN) -o SerialDelaunay main.o display.o types.o -lm

main.o: main.c types.h display.h 
	$(COM) main.c $(OBJDIR)

display.o: display.c display.h types.h
	$(COM) display.c $(OBJDIR)

types.o: types.c types.h
	$(COM) types.c $(OBJDIR)

clean:
	rm -rf ./bin/*.o

all:
	make clean && make && make run

run:
	./bin/SerialDelaunay

compare: files/sede.node files/sede.ele
	../triangle/triangle ../serial_delaunay/files/sede.node && ../triangle/showme ../serial_delaunay/files/sede.ele ../serial_delaunay/files/sede.1.ele
