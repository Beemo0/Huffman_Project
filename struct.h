#ifndef STRUCT
#define STRUCT

#include "main.h"
#include <inttypes.h>
#define llui long long unsigned int

typedef struct Box {
	char name;
	int freq;
} Box;

typedef struct Code {
	int code;
	struct Code* next;
}Code;

typedef struct Table {
	char name;
	Code* listcode;
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

typedef struct ByteList {
	uint8_t Byt;
	uint8_t count;
	struct ByteList* next;
}ByteList;



#endif
