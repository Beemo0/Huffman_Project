#include "main.h"

int main(int argc, char const *argv[]) {
	FILE* file = NULL;
	file = fopen("test.txt","r");
	if (file != NULL) {

		fseek(file,0,SEEK_SET); //set cursor to the beginning

		char buffer;
		buffer = fgetc(file); //get the first char

		Node node_v;
		node_v.box.name = buffer;
		node_v.box.freq = 0;
		node_v.next = NULL;

		Node* node = &node_v;

		while(buffer != EOF){
			AddChar(node, buffer);
			buffer = fgetc(file);
		}
		fclose(file);
		FSort(node);
		printNode(node);
	
	} else printf("Error : file not found\n");

	return 0;
}
