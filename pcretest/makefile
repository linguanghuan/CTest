all:
	gcc -g -o test.o -c test.c
	gcc -g -o test_2.o -c test_2.c
	gcc -o test test.o -lpcre
	gcc -o test_2 test_2.o -lpcre
clean:
	rm -rf  test.o test test_2.o test_2
