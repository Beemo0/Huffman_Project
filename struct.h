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
	struct Node* son_l;
	struct Node* son_r;
} Node;

#endif