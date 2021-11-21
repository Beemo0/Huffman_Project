#include "main.h"

int main(int argc, char *argv[]) {

	int mod = 0;

	char* filesubj;

	char filedest_v[128];
	char* filedest = &filedest_v;

	if(argc==3) {
 		
 		if (argv[1][1] == 'c') {
 			
 			filesubj = argv[2];
 			int lenght = strlen(filesubj);
 			for (int i=0; i<lenght-4; i++) {
 				filedest[i] = filesubj[i];
 			}
 			strcat(filedest,".hcf");
 			printf("File to compress : %s, Destination : %s\n\n", filesubj, filedest);
 			mod = 1;
 		}

 		else if (argv[1][1] == 'd') {
 			
 			filesubj = argv[2];
 			int lenght = strlen(filesubj);
 			for (int i=0; i<lenght-4; i++) {
 				filedest[i] = filesubj[i];
 			}
 			strcat(filedest,".txt");
 			printf("File to decompress : %s, Destination : %s\n\n", filesubj, filedest);
 			mod = 2;
 			
 			
 		}
 		else if (argv[1][1] == 'h') {
			printf("usage : \n\n-c <your file> to compress \n-d <your file.hcf> to decompress \n-h to print this help\n");
			return 0;
		
		} else printf("Bad arguments use -h for help\n");



	} else printf("Bad arguments use -h for help\n");

	if (mod == 1) {

		clock_t start_t, end_t, total_t;
		start_t = clock();

		Node node_v;
		Node* node = &node_v;

		int totalChar = 0;

		node = FillList(node, filesubj);

		Table* table = NULL;
		Table** table_p = &table;

		node = MergeSort(node);
		//printNode(node);

		FILE* outFile = fopen(filedest, "w");
		FILE* inFile = fopen(filesubj, "r");
		if (!inFile || !outFile) {
			printf("Error : File not found\n");
			exit(1);
		}

		fprintNode(node, outFile);

		node = MakeTree(node);
		//printNode(node);

		totalChar = node->box.freq;

		Code* buffer = NULL;

		//treeprint(node, 5);

		ReadTree(node, buffer, table_p);

		//printTable(table);

		ReplaceText(inFile, outFile, table, totalChar);

		fclose(outFile);

		end_t = clock();

		fputs("\033[A\033[2K",stdout);
		printf("Compression done :%g s\n",(double)(end_t - start_t)/CLOCKS_PER_SEC);


	} else if (mod == 2) {

		clock_t start_t, end_t, total_t;
		start_t = clock();

		Node* node = NULL;

		int countByte_v = 0;
		int* countByte = &countByte_v;

		FILE* inFile = fopen(filesubj, "r");
		FILE* outFile = fopen(filedest, "w");
		if (!inFile || !outFile) {
			printf("Error : File not found\n");
			exit(1);
		}
		FILE* buffFile = fopen("buffer", "w");

		node = fscanNode(inFile, countByte);

		//&printf("countByte : %d\n", *countByte);

		ReverseNode(&node);

		//printNode(node);
		
		buffFile = MakeBinList(inFile, countByte, buffFile);

		fclose(buffFile);

		node = MakeTree(node);

		//treeprint(node, 5);

		buffFile = fopen("buffer", "r");
		fseek(buffFile,0,SEEK_SET);

		WriteFile(node, outFile, buffFile);

		fclose(buffFile);
		fclose(inFile);
		fclose(outFile);

		end_t = clock();
		fputs("\033[A\033[2K",stdout);
		printf("Decompression done :%g s\n",(double)(end_t - start_t)/CLOCKS_PER_SEC);

		//printCodeList(binList);
	}



	return 0;
}
