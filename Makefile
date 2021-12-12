CFLAGS = -Wall -g

clean:
	rm -f *.o stringProg

all: stringProg

stringProg: main.o
	gcc $(CFLAGS) -o stringProg main.o
main.o: main.c
	gcc $(CFLAGS) -c main.c