#ifndef TREE_H
#define TREE_H

#include <stdio.h>
#include <stdlib.h>

typedef struct Tree
{
    char character;
    int occurence;
    struct Tree* right;
    struct Tree* left;

}Tree;


Tree* init(char character, int occurence);
Tree* fusionTree(Tree* t1, Tree* t2);

Tree* maxTree(Tree* tree);
Tree* minTree(Tree* tree);
Tree* next(Tree* tree);
Tree* previous(Tree* tree);

int depth(Tree* tree);

void freeTree(Tree* tree);

void printInfixTree(Tree* tree);
void printPrefixTree(Tree* tree);
void printPostfixTree(Tree* tree);

#endif
