SerialDelaunay: main.o display.o types.o
	gcc -o SerialDelaunay main.o display.o types.o -lm

main.o: main.c types.h display.h robinhood.h
	gcc -c main.c

display.o: display.c display.h types.h
	gcc -c display.c

types.o: types.c types.h
	gcc -c types.c

clean:
	rm -rf *.o

run:
	./SerialDelaunay