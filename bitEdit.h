#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#include "list.h"


void writeBits(FILE* src, FILE* dest, Tree* tree);
void writeTree(FILE* dest, Tree* tree);
void compression(const char* srcPath, const char* destPath);

List* buildTree(FILE* src);

int concatenate(int x, int y);
int getNextChar(FILE* src);