#ifndef TREE_H
#define TREE_H

#include <stdio.h>
#include <stdlib.h>
#include "listBinary.h"

typedef struct Tree
{
    char character;             //Character of the node
    unsigned int occurence;     //Occurences of the character
    ListBinary* binary;         //Huffman binary code of the character

    struct Tree* right;
    struct Tree* left;

}Tree;

Tree* init(char character, unsigned int occurence);
Tree* mergeTree(Tree* t1, Tree* t2);

void makeBinary(Tree** tree);
void makeBinaryHide(Tree** tree, ListBinary* code, short binary);

Tree* maxTree(Tree* tree);
Tree* minTree(Tree* tree);
Tree* next(Tree* tree);
Tree* previous(Tree* tree);

int depth(Tree* tree);

void freeTree(Tree* tree);

void printRootTree(Tree* tree);
void printInfixTree(Tree* tree);
void printPrefixTree(Tree* tree);
void printPostfixTree(Tree* tree);

#endif
