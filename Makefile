build:
	gcc test.c ezTimer.c -o test

clean:
	rm -f test
	rm -f *.o
