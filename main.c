#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "tree.h"
#include "list.h"
#include "user.h"
#include "bitEdit.h"

FILE *srcFile = NULL;
char *path = NULL;        //Default path
short userChoice;           //Get what action the user want
List* li = NULL;
clock_t start_t, end_t;

int main(int argc, char *argv[]){

    userChoice = userArgument(argc, argv, &path);

    switch (userChoice)
    {
    case 0:             //Case exit the program
        
        return 0;
        break;

    case 1:
        
		start_t = clock();
        compression(path, NULL);
        end_t = clock();
        fputs("\033[A\033[2K",stdout);

		printf("Compression done :%g s\n",(double)(end_t - start_t)/CLOCKS_PER_SEC);

        return 0;
        break;
    
    case 2:

        srcFile = fopen(path, "r");    //Open the file

        if (!srcFile)
        {
            perror("Error: File not find\n");
            exit(1);
        }

        printf("File open\n");
        li = buildTree(srcFile);
        makeBinary(&(li->tree));

        return 0;

    default:
        perror("Error: incorrect argument");
        break;
    }
    
    return 0;
}
