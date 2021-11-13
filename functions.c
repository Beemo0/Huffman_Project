#include "functions.h"

void printNode(Node* node) {
	if (!node) return;
	printf("Character: %c, Occurence: %d\n", node->box.name, node->box.freq);
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
	
		if (node->box.name == name) node->box.freq ++;
	
		else {
			if (node->next == NULL) {
				Node* new = malloc(sizeof(*new));

				if (!node || !new) exit(EXIT_FAILURE);

				new->box.name = name;
				new->box.freq = 1;

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
	new->son_l = node;
	new->son_r = node->next;
	node->next->next = NULL;
	node->next = NULL;

	MakeTree(new); 

}