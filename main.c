#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#include "list.h"

int main(int argc, char *argv[]){

    FILE *file = NULL;
    List* list = NULL;

    file = fopen("text", "r");

    if (file)
    {
        printf("File open\n");

        int c;
        
        while ((c = fgetc(file)) != EOF)
        {
            list = addToList(list, (char)c);
        }

        list = fSort(list);
        printList(list);


        
        fclose(file);
        freeList(list);

    } else {
        perror("Error: File not open\n");
    }

    return 0;
}