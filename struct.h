#ifndef STRUCT
#define STRUCT

#include "main.h"

typedef struct Box {
	char name;
	int freq;
} Box;

typedef struct Table {
	char name;
	int code;
	struct Table* next;
} Table;

typedef struct Way {
	int value;
	struct Way* next;
} Way;

typedef struct Node {
	Box box;
	struct Node* next;
	struct Node* left;
	struct Node* right;
	int isLeaf;
	Way* way;
} Node;

#endif