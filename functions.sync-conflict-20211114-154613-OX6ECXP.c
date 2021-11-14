#include "functions.h"

void printNode(Node* node) {
	if (!node) return;
	printf("Character: %c", node->box.name);
	printf("Occurence: %d\n", node->box.freq);
	printNode(node->next);
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

		printf("char -> %c, freq -> %d\n",node->box.name, node->box.freq);
	
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

int Concatenate(int x, int y) {
    int pow = 10;
    while(y >= pow)
        pow *= 10;
    return x * pow + y;        
}

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

int tree_height(Node* root) {
    // Get the height of the tree
    if (!root)
        return 0;
    else {
        // Find the height of both subtrees
        // and use the larger one
        int left_height = tree_height(root->left);
        int right_height = tree_height(root->right);
        if (left_height >= right_height)
            return left_height + 1;
        else
            return right_height + 1;
    }
}

void ReadTree(Node* node, Node* root, int buffer) {

	printf("read node number : %d\n", node->box.freq);
	FILE* out = NULL;

	int again = 0;

	if (node->left != NULL) {
		if (node->left->left == NULL && node->left->right == NULL && node->left->isLeaf == 0) {
			node->left = NULL;
			if (root->left != NULL || root->right != NULL) ReadTree(root, root, 0);
		
		} else if (node->left->isLeaf == 1) {
			buffer = Concatenate(buffer,2);
			out = fopen("out.txt","r+");
			fseek(out,0,SEEK_END);
			fprintf(out, "char : %c, code : %d\n",node->left->box.name, buffer );
			printf("char : %c, code : %d\n",node->left->box.name, buffer);
			fclose(out);
			node->left = NULL;
			if (root->left != NULL || root->right != NULL) ReadTree(root, root, 0);
		}
	}

	if (node->right != NULL) {
		if (node->right->left == NULL && node->right->right == NULL && node->right->isLeaf == 0) {
			node->right = NULL;
			if (root->left != NULL || root->right != NULL) ReadTree(root, root, 0);
		
		} else if (node->right->isLeaf == 1) {
			buffer = Concatenate(buffer,1);
			out = fopen("out.txt","r+");
			fseek(out,0,SEEK_END);
			fprintf(out, "char : %c, code : %d\n",node->right->box.name, buffer );
			printf("char : %c, code : %d\n",node->right->box.name, buffer);
			fclose(out);
			node->right = NULL;
			if (root->left != NULL || root->right != NULL) ReadTree(root, root, 0);

		}
	}
	if (node->left != NULL) {
		buffer = Concatenate(buffer,2);
		ReadTree(node->left,root,buffer);
	} else if (node->right != NULL) {
		buffer = Concatenate(buffer,1);
		ReadTree(node->right,root,buffer);
	}
}
