#ifndef FUNCTIONS
#define FUNCTIONS

#include "main.h"
#include <inttypes.h>
#define llui long long unsigned int

void printNode(Node* node);

void fprintNode(Node* node, FILE* outFile);

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

Code* AddIntToBuffer(Code* buffer, Code* root, uint8_t value);

Table* AddCharTable(Table* table, char name, Code* code);

Node* FillList(Node* node, char* filename);

void ReplaceText(char* filename, FILE* outFile, Table* table);

void WriteByte(ByteList* bList, FILE* outFile);

ByteList* InitByteList(Code* codeList);

void Bytify(ByteList* bList, Code* codeList, int* countByte);

Code* Encode(char name, Table* table);

FILE* MakeBinList(FILE* inFile, int* countByte, FILE* buffFile);

Node* fscanNode(FILE* inFile, int* countByte);

void WriteFile(Node* node, FILE* outFile, FILE* inFile);

void WriteFileRec(FILE* outFile, Node* node, Node* root, FILE* buffFile, int* exitvalue, char* charbuffer );

void ReverseNodeRec(Node* node, Node* buffer, Node** root);

void ReverseNode(Node** node);


#endif
