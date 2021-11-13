main : main.c functions.c
	gcc -c functions.c -o functions.o -Wall -Wextra
	gcc main.c functions.o -o exe -Wall -Wextra
	rm *.o
	./exe
