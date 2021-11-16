all: main.o
	gcc -o main.out main.c

main.o: main.c
	gcc -c main.c

run:
	./main.out

comprun: all
	./main.out

clean:
	rm *.o
	rm *.out

