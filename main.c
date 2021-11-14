#include "main.h"

int main(int argc, char const *argv[]) {

		Node node_v;
		Node* node = &node_v;

		node = FillList(node, "h2g2.txt");

		Table* table = NULL;
		Table** table_p = &table;
		
		node = MergeSort(node);
		//printNode(node);

		node = MakeTree(node);
		//printNode(node);

		ReadTree(node,node, 0, table_p);
		printTable(table);
		
		ReplaceText("h2g2.txt", table);

	

	return 0;
}
