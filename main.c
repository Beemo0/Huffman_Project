#include "main.h"

int main(int argc, char const *argv[]) {

	int mod = 2;

	if (mod == 1) {

		Node node_v;
		Node* node = &node_v;

		node = FillList(node, "h2g2.txt");

		Table* table = NULL;
		Table** table_p = &table;

		node = MergeSort(node);
		//printNode(node);

		FILE* outFile = fopen("out.hcf", "w");

		fprintNode(node, outFile);

		node = MakeTree(node);
		//printNode(node);

		Code* buffer = NULL;

		treeprint(node, 5);

		ReadTree(node, buffer, table_p);

		printTable(table);

		ReplaceText("h2g2.txt", outFile, table);

		fclose(outFile);

	} else if (mod == 2) {

		Node* node = NULL;

		int countByte_v = 0;
		int* countByte = &countByte_v;

		FILE* inFile = fopen("out.hcf", "r");
		FILE* outFile = fopen("out.txt", "w");
		FILE* buffFile = fopen("buffer", "w");

		node = fscanNode(inFile, countByte);

		printf("countByte : %d\n", *countByte);

		ReverseNode(&node);

		//printNode(node);
		
		buffFile = MakeBinList(inFile, countByte, buffFile);

		fclose(buffFile);

		node = MakeTree(node);

		treeprint(node, 5);

		buffFile = fopen("buffer", "r");
		fseek(buffFile,0,SEEK_SET);

		WriteFile(outFile, node, node, buffFile, 0);

		fclose(buffFile);
		fclose(inFile);
		fclose(outFile);

		//printCodeList(binList);
	}



	return 0;
}
