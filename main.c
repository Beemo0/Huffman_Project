#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#include "list.h"
#include "user.h"

char *path = "text";        //Default path
short userChoice;           //Get what action the user want

int main(int argc, char *argv[]){ 

    userChoice = userArgument(argc, argv, path);
    /*
    FILE *file = NULL;
    List* list = NULL;

    file = fopen(path, "r+");    //Open the file

    if (file)
    {
        printf("File open\n");

        int c;
        
        while ((c = fgetc(file)) != EOF)
        {
            list = addToList(list, (char)c);
        }

        createHuffmanTree(&list);
        
        makeBinary(&(list->tree));
        
        printf("----------------\n");
        printList(list);
        
        fclose(file);
        freeList(list);

    } else {
        perror("Error: File not find\n");
    }

    return 0;

    */
}