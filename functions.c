#include "functions.h"

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

void printByteList(ByteList* bList) {
	if (!bList) return;
	printf("%" PRIu8, bList->Byt);
	printByteList(bList->next);
}

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

uint8_t BitAdd(uint8_t x, uint8_t y) {
    x <<= 1;
		x |= y;
		return x;
}

/* internet function */
void treeprint(Node* root, int space)
{
    // Base case
    if (root == NULL)
        return;

    // Increase distance between levels
    space += 10;

    // Process right child first
    treeprint(root->right, space);

    // Print current node after space
    // count
    printf("\n");
    for (int i = 10; i < space; i++)
        printf(" ");
    printf("%d\n", root->box.freq);

    // Process left child
    treeprint(root->left, space);
}

int tree_height(Node* node) {

    if (!node) return 0;
    else {
        int left_height = tree_height(node->left);
        int right_height = tree_height(node->right);

        if (left_height >= right_height) return left_height + 1;

        else return right_height + 1;
    }
}

void ReadTree(Node* node, Node* root, Code* buffer, Table** table) {

	if (node->left != NULL) {
		if (node->left->left == NULL && node->left->right == NULL && node->left->isLeaf == 0) {
			node->left = NULL;
			if (root->left != NULL || root->right != NULL) ReadTree(root, root, NULL, table);

		} else if (node->left->isLeaf == 1) {
			buffer = AddIntToBuffer(buffer, 0);
			*table = AddCharTable(*table,node->left->box.name, buffer);
			node->left = NULL;
			if (root->left != NULL || root->right != NULL) ReadTree(root, root, NULL, table);
		}
	}

	if (node->right != NULL) {
		if (node->right->left == NULL && node->right->right == NULL && node->right->isLeaf == 0) {
			node->right = NULL;
			if (root->left != NULL || root->right != NULL) ReadTree(root, root, NULL, table);

		} else if (node->right->isLeaf == 1) {
			buffer = AddIntToBuffer(buffer, 1);
			*table = AddCharTable(*table,node->right->box.name, buffer);
			node->right = NULL;
			if (root->left != NULL || root->right != NULL) ReadTree(root, root, NULL, table);

		}
	}
	if (node->left != NULL) {
		buffer = AddIntToBuffer(buffer, 0);
		ReadTree(node->left,root,buffer, table);
	} else if (node->right != NULL) {
		buffer = AddIntToBuffer(buffer, 1);
		ReadTree(node->right,root,buffer, table);
	}
}

Code* AddIntToBuffer(Code* buffer, int value) {

	Code* new = malloc(sizeof(*new));

	new->code = value;
	new->next = buffer;

	return new;
}


Table* AddCharTable(Table* table, char name, Code* code) {

	Table* new = malloc(sizeof(*new));

	new->name = name;
	new->listcode = code;
	new->next = table;

	return new;
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

void ReplaceText(char* filename, Table* table) {

	FILE* inFile = fopen(filename, "r");
	FILE* outFile = fopen("out", "w");

	if (!inFile || !outFile) exit(EXIT_FAILURE);

	fseek(inFile,0,SEEK_SET);
	fseek(outFile,0,SEEK_SET);
	char charbuffer = fgetc(inFile);

	ByteList* bList = malloc(sizeof(*bList));
	bList->count = 0;
	bList->Byt = 0;
	bList->next = NULL;

	Code* codeList = NULL;

	while (charbuffer != EOF) {
		codeList = Encode(charbuffer,table);
		Bytify(bList, codeList);
		charbuffer = fgetc(inFile);
	}


	printf("ByteList : ");
	printByteList(bList);

	printByte(bList, outFile);



	fclose(inFile);
	fclose(outFile);
}

void printByte(ByteList* bList, FILE* outFile) {
	if (!bList) return;
	fwrite(&bList->Byt,1,1,outFile);
	printByte(bList->next, outFile);

}

void Bytify(ByteList* bList, Code* codeList) {

	if (!bList) return;
	else if (codeList->code != 1 && codeList->code != 0) exit(3);
	else if (bList->count == 8 && bList->next != NULL) Bytify(bList->next, codeList);
	else if (!bList->next) {
			ByteList* new = malloc(sizeof(*new));

			new->count = 1;
			new->Byt = BitAdd(bList->Byt, 0);
			printf("Byt = : %" PRIu8 "\n" ,bList->Byt);
			new->next = NULL;

			bList->next = new;
	}
	else if (bList->count < 8) {
		printf("we add %d to ",codeList->code);
		printf("%" PRIu8 "\n" ,bList->Byt);
		bList->Byt = BitAdd(bList->Byt, codeList->code);
		bList->count ++;
	}

}

Code* Encode(char name, Table* table) {

	while(name != table->name) {
		table = table->next;
		if (!table) exit(EXIT_FAILURE);
	}

	return table->listcode;

}
