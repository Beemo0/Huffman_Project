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

/*Insert function*/
List* addToList(List* list, char character);
List* insertList(List* list, Tree* tree);

/*Merge sort*/
List* fSort(List* list);
List* fSortHide(List* list);
void splitList(List* source, List** front, List** back);
List* mergeList(List* n1, List* n2);

/*Utility function*/
void createHuffmanTree(List** list);
void printList(List* list);
int lenghtList(List* list);

/*Free function*/
void freeList(List* list);
void popList(List** list);

#endif