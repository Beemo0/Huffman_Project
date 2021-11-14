#include "functions.h"

void printNode(Node* node) {
	if (!node) return;
	printf("Character: %c, Occurence: %d\n", node->box.name,  node->box.freq);
	printNode(node->next);
}

void printTable(Table* table) {
	if (!table) return;
	printf("Character: %c, Code: %llu\n", table->name,  table->code);
	printTable(table->next);
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


/* internet inspired function */
llui Concatenate(llui x, llui y) {
    llui pow = 10;
    while(y >= pow)
        pow *= 10;
    return x * pow + y;        
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

void ReadTree(Node* node, Node* root, llui buffer, Table** table) {

	if (node->left != NULL) {
		if (node->left->left == NULL && node->left->right == NULL && node->left->isLeaf == 0) {
			node->left = NULL;
			if (root->left != NULL || root->right != NULL) ReadTree(root, root, 0, table);
		
		} else if (node->left->isLeaf == 1) {
			buffer = Concatenate(buffer,2);
			*table = AddCharTable(*table,node->left->box.name, buffer);
			node->left = NULL;
			if (root->left != NULL || root->right != NULL) ReadTree(root, root, 0, table);
		}
	}

	if (node->right != NULL) {
		if (node->right->left == NULL && node->right->right == NULL && node->right->isLeaf == 0) {
			node->right = NULL;
			if (root->left != NULL || root->right != NULL) ReadTree(root, root, 0, table);
		
		} else if (node->right->isLeaf == 1) {
			buffer = Concatenate(buffer,1);
			*table = AddCharTable(*table,node->right->box.name, buffer);
			node->right = NULL;
			if (root->left != NULL || root->right != NULL) ReadTree(root, root, 0, table);

		}
	}
	if (node->left != NULL) {
		buffer = Concatenate(buffer,2);
		ReadTree(node->left,root,buffer, table);
	} else if (node->right != NULL) {
		buffer = Concatenate(buffer,1);
		ReadTree(node->right,root,buffer, table);
	}
}

Table* AddCharTable(Table* table, char name, llui code) {

	Table* new = malloc(sizeof(*new));

	new->name = name;
	new->code = code;
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

	if (!inFile || !outFile) exit(1);
	
	fseek(inFile,0,SEEK_SET);
	fseek(outFile,0,SEEK_SET);

	char buffer = fgetc(inFile);

	while (buffer != EOF) {
		fprintf(outFile, "%llu ", Encode(buffer,table) );
		buffer = fgetc(inFile);
	}

	fclose(inFile);
	fclose(outFile);
}

void Replace2(char* filename) {

	FILE* file = fopen(filename, "r+");

}

/* internet function */
llui replace(llui number){
   if (number == 0)
   return 0;
   //check last digit and change it if needed
   llui digit = number % 10;
   if (digit == 2)
   digit = 0;
   // Convert remaining digits and append to its last digit
   return replace(number/10) * 10 + digit;
}

llui Encode(char name, Table* table) {
	

	while(name != table->name) {
		table = table->next;
		if (!table) exit(EXIT_FAILURE);
	}

	llui result = replace(table->code);


	return result;

}




















