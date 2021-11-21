main : main.c functions.c
	gcc -c functions.c -o functions.o -Wall -Wextra -Og -ggdb
	gcc main.c functions.o -o exe -Wall -Wextra -Og -ggdb 

	rm *.o
