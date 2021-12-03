#include "bitEdit.h"

/**
 * @brief Write the compress file
 * 
 * @param src 
 * @param dest 
 * @param tree 
 */
void writeBits(FILE* src, FILE* dest, Tree* tree)
{
    /*Verify source file is open*/
    if (!src)
        return;

    /*Verify destination file is open else create one*/
    if (!dest)
    {
        dest = fopen("compressedText", "w");
        if (!dest)
            perror("Error: destination file not created\n");
        else
            printf("Destination file created\n");
        
    }

    /*Write all the character associeted with their code*/
    fseek(dest, 0, SEEK_SET);
    writeTree(dest, tree);
    fprintf(dest, "$$");

    int character;
    unsigned char writeBuffer = 0x00;
    ListBinary* bin = NULL;
    short count = 0;

    fseek(src, 0, SEEK_SET);    //Return to the start of src file

    /*For every character in the text*/
    while ((character = fgetc(src)) != EOF)
    {
        char* c = (char*)&character;
        char tmp;

        bin = getBinaryCode(c, tree);   //Get his binary code from the tree

        if (!bin)
            perror("Error: character not found in tree 1\n");
        
        /*Encode it in bits*/
        while (bin)
        {
            /*Associete bool to octet*/
            if (bin->data == 1)
                tmp = 0x01;     //00000001
            else 
                tmp = 0x00;     //00000000

            if (count < 8)
            {
                tmp = tmp << count;
                writeBuffer |= tmp;
                count++;
                bin = bin->next;
            } else {
                fprintf(dest, "%c", writeBuffer);
                writeBuffer = 0x00;
                count = 0;
                
            }
        }
        
        bin = NULL;
    }

    /*Encode the EOF*/
    /*char e = EOF;
    char* c = (char*)&e;
    char tmp;
    bin = NULL;

    bin = getBinaryCode(c, tree);

    if (!bin)
        perror("Error: character not found in tree 2\n");
        
    while (bin)
    {*/
        /*Associete bool to octet*//*
        if (bin->data == 1)
            tmp = 0x01;     //00000001
        else 
            tmp = 0x00;     //00000000

        if (count < 8)
        {
            tmp = tmp << count;
            writeBuffer |= tmp;
            count++;
            bin = bin->next;
        } else {
            fprintf(dest, "%c", writeBuffer);
            writeBuffer = 0x00;
            count = 0;
                
        }
    }
    */
    /*If the last bit isn't full*/
    if (count != 0)
    {
        fprintf(dest, "%c", writeBuffer);
        writeBuffer = 0x00;
    }
    

    fclose(dest);
}

/**
 * @brief Write the character associate with their code in a file
 * 
 * @param dest 
 * @param tree 
 */
void writeTree(FILE* dest, Tree* tree)
{
    if (!dest)
        return;
    
    if (!tree)
        return;

    if (!tree->left && !tree->right)
    {
        //Put the character
        fprintf(dest, "%c", tree->character);   

        /*
        //Put his binary code
        ListBinary* headBinaryList = tree->binary;
        while (tree->binary)
        {
            fprintf(dest, "%d", tree->binary->data);
            tree->binary = tree->binary->next;
        }
        tree->binary = headBinaryList;
        */

        fprintf(dest, "%d", tree->occurence); // Put his occurences

        fprintf(dest, " ");    //Separation
    }

    if (tree->left)
        writeTree(dest, tree->left);
    
    if (tree->right)
        writeTree(dest, tree->right);
}


void compression(const char* srcPath, const char* destPath)
{
    FILE *srcFile = NULL;
    FILE *fileDest = NULL;
    List* list = NULL;

    srcFile = fopen(srcPath, "r");    //Open the file

    if (!srcFile)
    {
        perror("Error: File not find\n");
        exit(1);
    }
    printf("File open\n");

    /* Add each character in a list*/
    int character;
    while ((character = fgetc(srcFile)) != EOF)
        list = addToList(list, (char)character);

    list = addToList(list, EOF);    //Add the end-of-file as a character in the tree

    createHuffmanTree(&list);       //Create the Huffman Tree

    makeBinary(&(list->tree));      //Associate Binary code to character node

    writeBits(srcFile, fileDest, list->tree);

    fclose(srcFile);      //Close the file
    freeList(list);       //Free the Tree List
}

/**
 * @brief 
 * 
 * @param src 
 * @param tree 
 */
List* buildTree(FILE* src)
{
    if (!src)
        return NULL;
    
    int charbuffer;
	int intbuffer = 0;
    List* tmp = NULL;
    
    fseek(src, 0, SEEK_SET);    //Return to the start of src file
    
    while (1) 
	{
        charbuffer = fgetc(src);

        if ((charbuffer == (int)'$' && getNextChar(src) == (int)'$') || charbuffer == EOF)
            break;

        printf("Character %c, %c\n", charbuffer, getNextChar(src));
        
		tmp = insertList(tmp, init(charbuffer, 0));
        
		while(1) 
        {
            charbuffer = fgetc(src);
            if (charbuffer == ' ')
                break;
            
			intbuffer = concatenate(intbuffer, charbuffer - 48);
		}

		tmp->tree->occurence = intbuffer;
		intbuffer = 0;
    }

    createHuffmanTree(&tmp);
    //*list = tmp;
    printList(tmp);
    return tmp;
}

int concatenate(int x, int y) 
{
    int pow = 10;

    while(y >= pow)
        pow *= 10;

    return x * pow + y;        
}

int getNextChar(FILE* src)
{
    // get the character
    int nextCharacter = fgetc(src);

    // fseek it back, so you don't really move the file descriptor
    fseek(src, -1, SEEK_CUR);

    // returning the char (as int)
    return nextCharacter;
}