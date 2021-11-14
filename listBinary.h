#ifndef LISTBINARY_H
#define LISTBINARY_H

#include <stdio.h>
#include <stdlib.h>

typedef struct ListBinary
{
    short data;
    struct ListBinary* next;
}ListBinary;

ListBinary* insertListBinary(ListBinary* bin, short value);

void printListBinary(ListBinary* bin);

void freeListBinary(ListBinary* bin);

#endif