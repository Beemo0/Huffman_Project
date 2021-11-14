#include "main.h"

int main(int argc, char const *argv[]) {
	FILE* file = NULL;
	file = fopen("test.txt","r");


	char in[50] = "freq : ";
	char out[50] = "0";


	printf("strcat test : %s\n",strcat(in, out));

	if (file != NULL) {

		fseek(file,0,SEEK_SET); //set cursor to the beginning

		char buffer;
		buffer = fgetc(file); //get the first char

		Node node_v;
		node_v.box.name = buffer;
		node_v.box.freq = 0;
		node_v.next = NULL;
		node_v.isLeaf = 1;
		node_v.left = NULL;
		node_v.right = NULL;

		Node* node = &node_v;

		while(buffer != EOF){
			AddChar(node, buffer);
			buffer = fgetc(file);
		}
		fclose(file);
		MergeSort(node);
		printNode(node);

		node = MakeTree(node);
		printNode(node);
		printf("le a c'est : %c\n",node->left->box.name);
		treeprint(node, 0);

		ReadTree(node,node, 0);
		int level = tree_height(node);
		treeprint(node, 0);
		

	} else printf("Error : file not found\n");

	return 0;
}
