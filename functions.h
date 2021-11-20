#ifndef FUNCTIONS
#define FUNCTIONS

#include "main.h"
#include <inttypes.h>
#define llui long long unsigned int

void printNode(Node* node);

void printTable(Table* table);

void printCodeList(Code* codeList);

void printByteList(ByteList* bList);

int LenghtList(Node* node);

void Split(Node* node, Node** A, Node** B);

Node* MergeSort(Node* node);

void AddChar(Node* node, char name);

Node* MakeTree(Node* node);

void ReadTree(Node* node, Code* buffer, Table** table);

void ReadTreeRec(Node* node, Node* root, Code* buffer, Table** table);

void treeprint(Node* root, int level);

int tree_height(Node* root);

Code* AddIntToBuffer(Code* buffer, Code* root, int value);

Table* AddCharTable(Table* table, char name, Code* code);

Node* FillList(Node* node, char* filename);

void ReplaceText(char* filename, Table* table);

void WriteByte(ByteList* bList, FILE* outFile);

ByteList* InitByteList(Code* codeList);

void Bytify(ByteList* bList, Code* codeList, int* countByte);

Code* Encode(char name, Table* table);


#endif
