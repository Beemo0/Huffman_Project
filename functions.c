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

Node* Fusion(Node* a,Node* b) {
	
	Node* result = NULL;	
	
	if (a == NULL) return (b);
	else if (b == NULL) return (a);

	if (a->box.freq <= b->box.freq) {
		result = a;
		result->next = Fusion(a->next, b);
	}
	else {
		result = b;
		result->next = Fusion(b->next, a);
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

Node* FSort(Node* node) {

	if (!node) return;

	int lenght = LenghtList(node);
	Node* a = NULL;
	Node* b = NULL;


	if (lenght >= 2) {
				
		Split(node, &a, &b);



		a = FSort(a);
		b = FSort(b);

		return node = Fusion(a,b);

  
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