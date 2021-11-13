#ifndef STRUCT
#define STRUCT

#include "main.h"

typedef struct Box {
	char name;
	int freq;
} Box;

typedef struct Node {
	Box box;
	struct Node* next;
} Node;

#endif