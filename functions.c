#include "functions.h"

/* ---------- Printing functions ---------- */

void printNode(Node* node) {
	if (!node) return;
	printf("Character: %c, Occurence: %d\n", node->box.name,  node->box.freq);
	printNode(node->next);
}

void printTable(Table* table) {
	if (!table) return;
	printf("Character : %c codé : ", table->name);
	printCodeList(table->listcode);
	printf("\n");
	printTable(table->next);
}

void printCodeList(Code* codeList) {
	if (!codeList) return;
	printf("%" PRIu8, codeList->code);
	printCodeList(codeList->next);
}

void freeCodeList(Code* codeList) {
	if (!codeList) return;
	freeCodeList(codeList->next);
	free(codeList);
}

void printByteList(ByteList* bList) {
	if (!bList) return;
	printf("%" SCNd8, bList->Byt);
	printByteList(bList->next);
}

/* internet function */
void printTree(Node* root, int space)
{
    // Base case
    if (root == NULL)
        return;

    // Increase distance between levels
    space += 10;

    // Process right child first
    printTree(root->right, space);

    // Print current node after space
    // count
    printf("\n");
    for (int i = 10; i < space; i++)
        printf(" ");
    printf("%c%d\n", root->box.name, root->box.freq);

    // Process left child
    printTree(root->left, space);
}

/* ---------- Merge Sort functions ---------- */

int LenghtList(Node* node) {
	if (!node) return 0;
	return LenghtList(node->next)+1;
}

Node* Merge(Node* a,Node* b) {

	Node* result = NULL;

	if (a == NULL) return (b);
	else if (b == NULL) return (a);

	if (a->box.freq <= b->box.freq) {
		result = a;
		result->next = Merge(a->next, b);
	}
	else {
		result = b;
		result->next = Merge(b->next, a);
	}

	return result;

}

void Split(Node* node, Node** A, Node** B) {
	Node* fast = node->next;
	Node* slow = node;

	while (fast != NULL) {
		fast = fast->next;
		if (fast != NULL) {
			slow = slow->next;
			fast = fast->next;
		}
	}

	*A = node;
	*B = slow->next;
	slow->next = NULL;

}

Node* MergeSort(Node* node) {

	if (!node) return;

	int lenght = LenghtList(node);
	Node* a = NULL;
	Node* b = NULL;


	if (lenght >= 2) {

		Split(node, &a, &b);



		a = MergeSort(a);
		b = MergeSort(b);

		return node = Merge(a,b);


	} else if (lenght == 2) {
		if (node->box.freq > node->next->box.freq) {
			node->next->next = node;
			node = node->next;
			node->next->next = NULL;
			return node;
		}
	}

	return node;
}

/* ---------- Compressing ---------- */

void delay(int milli_seconds) {
	int milli = milli_seconds *1000;
    clock_t start_time = clock();
    while (clock() < start_time + milli);
}

Node* FillList(Node* node, char* filename) {

	FILE* file = NULL;
	file = fopen(filename,"r");

	if (file != NULL) {

		fseek(file,0,SEEK_SET); //set cursor to the beginning

		char buffer;
		buffer = fgetc(file); //get the first char

		node->box.name = buffer;
		node->box.freq = 0;
		node->next = NULL;
		node->isLeaf = 1;
		node->left = NULL;
		node->right = NULL;


		while(buffer != EOF){
			AddChar(node, buffer);
			buffer = fgetc(file);
		}

		fclose(file);

		return node;

	} else printf("Error : file not found\n");
}

void AddChar(Node* node, char name) {
	if (node != NULL) {

		//printf("char -> %c, freq -> %d\n",node->box.name, node->box.freq);

		if (node->box.name == name) node->box.freq ++;

		else {
			if (node->next == NULL) {
				Node* new = malloc(sizeof(*new));

				if (!node || !new) exit(EXIT_FAILURE);

				new->box.name = name;
				new->box.freq = 1;
				new->isLeaf = 1;

				node->next = new;

			} else AddChar(node->next, name);
		}
	}
}

void fprintNode(Node* node, FILE* outFile) {
	if (!node) return;
	fprintf(outFile,"%c%d ", node->box.name,  node->box.freq);
	fprintNode(node->next, outFile);
}

Node* MakeTree(Node* node) {

	if  (LenghtList(node) == 1) return node;

	node = MergeSort(node);

	Node* new = malloc(sizeof(*new));

	if (!node || !new) exit(EXIT_FAILURE);

	new->box.freq = node->box.freq + node->next->box.freq;
	new->next = node->next->next;
	new->isLeaf = 0;
	new->left = node;
	new->right = node->next;
	node->next->next = NULL;
	node->next = NULL;

	MakeTree(new);

}

void ReadTree(Node* node, Code* buffer, Table** table) {
	if (!node->left & !node->right) {
		buffer = AddIntToBuffer(buffer, buffer, 0);
		*table = AddCharTable(*table, node->box.name, buffer);
	} else ReadTreeRec(node, node, buffer, table);
}

void ReadTreeRec(Node* node, Node* root, Code* buffer, Table** table) {

	if (node->left != NULL) {
		if (node->left->left == NULL && node->left->right == NULL && node->left->isLeaf == 0) {
			node->left = NULL;
			if (root->left != NULL || root->right != NULL) ReadTreeRec(root, root, NULL, table);

		} else if (node->left->isLeaf == 1) {
			
			buffer = AddIntToBuffer(buffer, buffer, 0);
			*table = AddCharTable(*table,node->left->box.name, buffer);
			node->left = NULL;
			if (root->left != NULL || root->right != NULL) ReadTreeRec(root, root, NULL, table);
		
		} else {
			buffer = AddIntToBuffer(buffer, buffer, 0);
			ReadTreeRec(node->left,root,buffer, table);
		}
	}

	if (node->right != NULL) {
		if (node->right->left == NULL && node->right->right == NULL && node->right->isLeaf == 0) {
			node->right = NULL;
			if (root->left != NULL || root->right != NULL) ReadTreeRec(root, root, NULL, table);

		} else if (node->right->isLeaf == 1) {
			buffer = AddIntToBuffer(buffer, buffer, 1);
			*table = AddCharTable(*table,node->right->box.name, buffer);
			node->right = NULL;
			if (root->left != NULL || root->right != NULL) ReadTreeRec(root, root, NULL, table);
		
		} else {
			buffer = AddIntToBuffer(buffer, buffer, 1);
			ReadTreeRec(node->right,root,buffer, table);
		}
	}

}

Code* AddIntToBuffer(Code* buffer, Code* root, uint8_t value) {
	if (!buffer) {
		Code* new = malloc(sizeof(*new));
		new->code = value;
		new->next = NULL;
		return new;
	
	} else if (buffer->next != NULL) AddIntToBuffer(buffer->next,root, value);
	
	else {
		Code* new = malloc(sizeof(*new));
		new->code = value;
		new->next = NULL;
		buffer->next = new;
		return root;
	} 
	return;
}


Table* AddCharTable(Table* table, char name, Code* code) {

	Table* new = malloc(sizeof(*new));

	new->name = name;
	new->listcode = code;
	new->next = table;

	return new;
}

void ReplaceText(FILE* inFile, FILE* outFile, Table* table, int totalChar) {


	int countByte_v = 1;
	int* countByte = &countByte_v;

	int countLoop = 0;
	int percent = 0;

	if (!inFile || !outFile) exit(EXIT_FAILURE);

	char charbuffer = fgetc(inFile);

	Code* codeList = NULL;

	ByteList* bList = malloc(sizeof(*bList));

	bList->count = 0;
	bList->Byt = 0;
	bList->next = NULL;
//Filling Byte list
	while (charbuffer != EOF) {
		codeList = Encode(charbuffer,table);
		Bytify(bList, codeList, countByte);
		charbuffer = fgetc(inFile);
		if (countLoop % (totalChar / 100) == 0) {
			fputs("\033[A\033[2K",stdout);
			printf("Compressing [ %d% ]\n", percent);
			percent += 1;
		}
		countLoop += 1;

		
	}

	fprintf(outFile, "$%d $$ ", *countByte);

	WriteByte(bList, outFile);

}

void Bytify(ByteList* bList, Code* codeList, int* countByte) {

	if (!bList) return;
	else if (codeList->code != 1 && codeList->code != 0) exit(3);
	else if (bList->count == 8 && bList->next != NULL) Bytify(bList->next, codeList, countByte);
	else if (bList->count < 8) {

		bList->Byt = BitAdd(bList->Byt, codeList->code);
		bList->count ++;
		if (codeList->next != NULL) Bytify(bList, codeList->next, countByte);
	
	} else if (!bList->next) {

		*countByte += 1;
		ByteList* new = malloc(sizeof(*new));

		new->count = 1;
		new->Byt = BitAdd(bList->Byt, codeList->code);
		
		new->next = NULL;

		bList->next = new;

		if (codeList->next != NULL) Bytify(bList->next, codeList->next, countByte);
	}
	

}

uint8_t BitAdd(uint8_t x, uint8_t y) {
    x <<= 1;
	x |= y;
	return x;
}

Code* Encode(char name, Table* table) {
	
	if (!table) exit(1);
	while(name != table->name) {
		table = table->next;
		if (!table) exit(2);
	}

	return table->listcode;

}

void WriteByte(ByteList* bList, FILE* outFile) {
	if (!bList) return;
	fwrite(&bList->Byt,1,1,outFile);
	WriteByte(bList->next, outFile);

}

/* ---------- Decompressing ---------- */

Node* fscanNode(FILE* inFile, int* countByte) {
	
	fseek(inFile,0,SEEK_SET);
	char charbuffer;
	int intbuffer = 0;
	Node* oldNode = NULL;

	while (1) {

		charbuffer = fgetc(inFile);

		Node* new = malloc(sizeof(*new));
		new->next = oldNode;
		new->isLeaf = 1;
		new->box.name = charbuffer;

		charbuffer = fgetc(inFile);

		while(charbuffer != ' ') {
			intbuffer = concatenate(intbuffer, (int)(charbuffer)-48);
			charbuffer = fgetc(inFile);
		}
		new->box.freq = intbuffer;
		intbuffer = 0;
		if (new->box.freq == -12) {
			*countByte = new->next->box.freq;
			return new->next->next;
		}
		oldNode = new;
	}
	
}

int concatenate(int x, int y) {
    int pow = 10;
    while(y >= pow)
        pow *= 10;
    return x * pow + y;        
}

void ReverseNode(Node** node){
   
   if (!node) return;
   ReverseNodeRec(*node, NULL, node);
}

void ReverseNodeRec(Node* node, Node* buffer, Node** root) {

	if (!node->next) {
   		*root = node;
		node->next = buffer;
		return;
	}
	Node* next = node->next;
	node->next = buffer;
	ReverseNodeRec(next, node, root);
}

FILE* MakeBinList(FILE* inFile, int* countByte, FILE* buffFile) {

	char charbuffer = fgetc(inFile);
	uint8_t bytebuffer[8];
	uint8_t mask = 254;
	int count = 0;

	if (!buffFile) exit(11);


	while (count < *countByte) {

		for (int i=0; i<8; i++) {
			if ((mask | (uint8_t)(charbuffer)) == 254) bytebuffer[i] = 0;
			else if ((mask | ((uint8_t)(charbuffer)) == 255)) bytebuffer[i] = 1;
			charbuffer >>= 1;
		}

		for (int i=7; i>=0; i--) fprintf(buffFile,"%d",bytebuffer[i]);

		//if (count % 100 == 0) fprintf(buffFile,"\n");
		
		charbuffer = fgetc(inFile);
		count++;
	}

	return buffFile;
}

void WriteFile(Node* node, FILE* outFile, FILE* buffFile) {
	
	int exitvalue_v = 0;
	int* exitvalue = &exitvalue_v;

	char charbuffer_v = 0;
	char* charbuffer = &charbuffer_v;

	while (*charbuffer != EOF) {
		WriteFileRec(outFile, node, node, buffFile, exitvalue, charbuffer);
		*exitvalue = 0;
	}
}

void WriteFileRec(FILE* outFile, Node* node, Node* root, FILE* buffFile, int* exitvalue, char* charbuffer ) {

	if (!outFile) exit(10);

	if (!node) {
		printf("Error : end of branch reached");
		exit(1);
	}

	*exitvalue += 1;
	//printf("exit : %d\n", *exitvalue);

	//printf("leaf : %d, node : %c, freq : %d\n", node->isLeaf, node->box.name, node->box.freq);
	if (node->isLeaf == 1) {
		fputc((int)(node->box.name),outFile);
		if(*exitvalue >= 1000) return;
		return WriteFileRec(outFile, root, root, buffFile, exitvalue, charbuffer);
		
	}

	else {
		*charbuffer = fgetc(buffFile);

		if (charbuffer == EOF) return;

		else if ((int)(*charbuffer)-48 == 0) {
			return WriteFileRec(outFile, node->left, root, buffFile, exitvalue, charbuffer);
		
		} else if ((int)(*charbuffer)-48 == 1) {
			return WriteFileRec(outFile, node->right, root, buffFile, exitvalue, charbuffer);
		}
	}
}





























