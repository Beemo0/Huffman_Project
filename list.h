#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

typedef struct List
{
    Tree* tree;
    struct List* next;

}List;

List* addToList(List* list, char character);
List* insertList(List* list, Tree* tree);

List* fSort(List* list);
List* fSortHide(List* list);
void splitList(List* source, List** front, List** back);
List* mergeList(List* n1, List* n2);


void printList(List* list);
int lenghtList(List* list);
void freeList(List* list);

#endif
