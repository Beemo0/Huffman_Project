#ifndef FUNCTIONS
#define FUNCTIONS

#include "main.h"
#include <inttypes.h>
#define llui long long unsigned int


/* ---------- Printing ---------- */

void printNode(Node* node);
//node : linked list and tree;

void printTable(Table* table);
//table : verity table make link between 
//character and his code

void printCodeList(Code* codeList);
//codelist :  store binary code of all char

void printByteList(ByteList* bList);
//bList : list of final bytes to be written

void printTree(Node* root, int level);

/* ---------- Merge sort ---------- */

int LenghtList(Node* node);

Node* Merge(Node* a,Node* b);

void Split(Node* node, Node** A, Node** B);

Node* MergeSort(Node* node);

/* ---------- Compressing ---------- */

Node* FillList(Node* node, char* filename);

void AddChar(Node* node, char name);

void fprintNode(Node* node, FILE* outFile);

Node* MakeTree(Node* node);

void ReadTree(Node* node, Code* buffer, Table** table);

void ReadTreeRec(Node* node, Node* root, Code* buffer, Table** table);

Code* AddIntToBuffer(Code* buffer, Code* root, uint8_t value);

Table* AddCharTable(Table* table, char name, Code* code);

void ReplaceText(FILE* inFile, FILE* outFile, Table* table, int totalChar);

void Bytify(ByteList* bList, Code* codeList, int* countByte);

uint8_t BitAdd(uint8_t x, uint8_t y);

Code* Encode(char name, Table* table);

void WriteByte(ByteList* bList, FILE* outFile);

/* ---------- Decompressing ---------- */

Node* fscanNode(FILE* inFile, int* countByte);

int concatenate(int x, int y);

void ReverseNode(Node** node);

void ReverseNodeRec(Node* node, Node* buffer, Node** root);

FILE* MakeBinList(FILE* inFile, int* countByte, FILE* buffFile);

void WriteFile(Node* node, FILE* outFile, FILE* inFile);

void WriteFileRec(FILE* outFile, Node* node, Node* root, FILE* buffFile, int* exitvalue, char* charbuffer );

/*Free function*/

void freeWayList(Way* wayList);

void freeByteList(ByteList* bList);

void freeTableList(Table* tabList);

void freeNodeList(Node* node);

void freeCodeList(Code* codeList);

#endif
