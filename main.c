#include "main.h"

int main(int argc, char *argv[]) {

	//Choose task to do : 0 nothing / 1 compress / 2 decompress
	int mod = 0; 

/* ---------- Arguments management --------- */

	char* filesubj;
	char* filedest;

	if(argc == 4 && argv[1][0] == '-') {
 		
 		if (argv[1][1] == 'c' && argv[2] != NULL && argv[3] != NULL) {
 			
 			filesubj = argv[2];
 			filedest = argv[3];
 			printf("File to compress : %s, Destination : %s\n\n", filesubj, filedest);
 			mod = 1;
 		}

 		else if (argv[1][1] == 'd' &&  argv[2] != NULL && argv[3] != NULL) {
 			
 			filesubj = argv[2];
 			filedest = argv[3];
 			printf("File to decompress : %s, Destination : %s\n\n", filesubj, filedest);
 			mod = 2;
 			
 		} else printf("Bad arguments use -h for help\n");

	} else if (argc == 2 && argv[1][0] == '-' && argv[1][1] == 'h') {
		printf("Usage : \n\n-c <your file> to compress \n-d <your file.hcf> to decompress \n-h to print this help\n");
		return 0;
		
	} else {
		printf("Bad arguments use -h for help\n");
		return 0;
	}

/* ---------- Compressing ---------- */
	if (mod == 1) {

		// ----- Vars -----

		clock_t start_t, end_t;
		start_t = clock();

		int totalChar = 0;

		Node node_v;
		Node* node = &node_v;

		Table* table = NULL;
		Table** table_p = &table;

		Code* buffer = NULL;

		FILE* outFile = fopen(filedest, "w");
		FILE* inFile = fopen(filesubj, "r");
		
		// ----- Errors -----

		if (!inFile || !outFile) {
			printf("Error : File not found\n");
			exit(1);
		} 

		char lonelyChar = fgetc(inFile);
		lonelyChar = fgetc(inFile);

		if (lonelyChar == EOF) {
			printf("Error : Can't compress empty / 1 char file\n");
			exit(1);
		}

		fseek(inFile, 0, SEEK_SET);

		// ----- Read file -----

		node = FillList(node, inFile);
		
		fseek(inFile, 0, SEEK_SET);

		// ----- Sort -----

		node = MergeSort(node);
		//printNode(node);

		// ----- Head -----

		fprintNode(node, outFile);

		// ----- Tree -----

		node = MakeTree(node);
		//treeprint(node, 5);

		totalChar = node->box.freq;

		ReadTree(node, buffer, table_p);
		//printTable(table);

		// ----- Replacing -----

		ReplaceText(inFile, outFile, table, totalChar);

		// ----- Ending -----

		fclose(inFile);
		fclose(outFile);

		struct stat oldStat;
		struct stat newStat;

		stat(filesubj, &oldStat);
		stat(filedest, &newStat);

		end_t = clock();

		fputs("\033[A\033[2K",stdout);
		printf("Compression done :%g s\n",(double)(end_t - start_t)/CLOCKS_PER_SEC);
		printf("%f kb compressed to %f kb, (%f%)\n", 
			(float)(oldStat.st_size)/1000,
			(float)(newStat.st_size)/1000,
			(float)(newStat.st_size)/(float)(oldStat.st_size)*100);

		freeNodeList(node);
		freeCodeList(buffer);

	} else if (mod == 2) {

		clock_t start_t, end_t;
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

		//printTree(node, 5);

		buffFile = fopen("buffer", "r");
		fseek(buffFile,0,SEEK_SET);

		WriteFile(node, outFile, buffFile);

		fclose(buffFile);
		fclose(inFile);
		fclose(outFile);

		remove("buffer");

		
		fputs("\033[A\033[2K",stdout);

		end_t = clock();
		printf("Decompression done :%g s\n",(double)(end_t - start_t)/CLOCKS_PER_SEC);

		//printCodeList(binList);
	}

	return 0;
}