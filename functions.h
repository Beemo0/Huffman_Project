#ifndef FUNCTIONS
#define FUNCTIONS

#include "main.h"
#define llui long long unsigned int

void printNode(Node* node);

int LenghtList(Node* node);

void Split(Node* node, Node** A, Node** B);

Node* MergeSort(Node* node);

void AddChar(Node* node, char name);

Node* MakeTree(Node* node);

void ReadTree(Node* node, Node* root,llui buffer);

void treeprint(Node* root, int level);

int tree_height(Node* root);

#endif