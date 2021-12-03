#include "listBinary.h"

/**
 * @brief Insert an element in a binary list
 * 
 * @param bin 
 * @param value 
 * @return ListBinary* 
 */
ListBinary* insertListBinary(ListBinary* bin, short value)
{
    if (!bin)
    {
        bin = (ListBinary*)malloc(sizeof(ListBinary));
        if (!bin){
            printf("Error: Allocation in insertListBinary\n");
            exit(1);
        }

        if (value != 0 && value != 1)
        {
            perror("Error: in insertListBinary: value not binary\n");
            exit(1);
        }

        bin->data = value;
        bin->next = NULL;
        return bin;

    } else {
        
        ListBinary* tmp = NULL;
        tmp = (ListBinary*)malloc(sizeof(ListBinary));
        if (!tmp){
            printf("Error: Allocation in insertListBinary\n");
            exit(1);
        }

        if (value != 0 && value != 1)
        {
            perror("Error: in insertListBinary: value not binary\n");
            exit(1);
        }

        tmp->data = value;
        tmp->next = bin;
        return tmp;
    }
}

/**
 * @brief Print a Binary List
 * 
 * @param bin 
 */
void printListBinary(ListBinary* bin){

    if (!bin)
        return;

    printf("%d", bin->data);

    printListBinary(bin->next);
}

/**
 * @brief Free a ListBinary
 * 
 * @param bin 
 */
void freeListBinary(ListBinary* bin){

    if (!bin)
        return;

    freeListBinary(bin->next);

    free(bin);
}