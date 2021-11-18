#include "tree.h"

/**
 * @brief Initialise a node with a character and it's occurences
 * 
 * @param character 
 * @param occurence 
 * @return Tree* 
 */
Tree* init(char character, unsigned int occurence){

    /*Allocate memory for a new node*/
    Tree* tmp = NULL;
    tmp = (Tree*)malloc(sizeof(Tree));

    if (!tmp){
        perror("Error: Can't allocate memory\n");
        exit(1);
    }

    /*Initialisation value*/
    tmp->character = character;
    //tmp->code = NULL;

    if(occurence >= 0)
        tmp->occurence = occurence;
    else {
        perror("Error: Occurence negative in tree init");
        exit(1);
    }

    tmp->left = NULL;
    tmp->right = NULL;

    return tmp;
}

/**
 * @brief Make the binary code for each character in an huffman tree
 * 
 * @param tree 
 */
void makeBinary(Tree** tree)
{
    if (*tree == NULL)
        return;
    
    if ((*tree)->left)
        makeBinaryHide(&((*tree)->left), NULL, 0);

    if ((*tree)->right)
        makeBinaryHide(&((*tree)->right), NULL, 1);
}

void makeBinaryHide(Tree** tree, ListBinary* code, short binary)
{
    if (!(*tree))
        return;
    
    if (binary != 0 && binary != 1)
    {
        perror("Error: in makeBinaryHide: value not binary\n");
        exit(1);
    }

    code = insertListBinary(code, binary);

    ListBinary* head = code;
    while (code != NULL)
    {
        (*tree)->binary = insertListBinary((*tree)->binary, code->data);
        code = code->next;
    }

    if ((*tree)->left != NULL)
        makeBinaryHide(&((*tree)->left), head, 0);

    if ((*tree)->right != NULL)
        makeBinaryHide(&((*tree)->right), head, 1);   

}

/**
 * @brief Function to insert a new node in the Tree*
 *
 * @param Tree*
 * @param value
 */
Tree* mergeTree(Tree* t1, Tree* t2){

    Tree* tree = (Tree*)malloc(sizeof(Tree));
    if (!tree){
        perror("Error: Can't allocate memory\n");
        exit(1);
    }

    tree->character = '+';
    tree->occurence = 0;

    if (t1->occurence < t2->occurence)
    {
        tree->left = t1;
        tree->right = t2;
    } else {
        tree->left = t2;
        tree->right = t1;
    }

    if (t1)
        tree->occurence += t1->occurence;

    if (t2)
        tree->occurence += t2->occurence;

    return tree;
}

/**
 * @brief Get the node with minimun occurences
 * 
 * @param tree 
 * @return Tree* 
 */
Tree* minTree(Tree* tree){

    if (!tree)
        return NULL;

    if (!tree->left)
        return tree;

    return minTree(tree->left);
}

/**
 * @brief Get the node with maximun occurences
 * 
 * @param tree 
 * @return Tree* 
 */
Tree* maxTree(Tree* tree){

    if (!tree)
        return NULL;

    if (!tree->right)
        return tree;

    return maxTree(tree->right);
}

/**
 * @brief Get the previous node
 * 
 * @param tree 
 * @return Tree* 
 */
Tree* previous(Tree* tree){

    if (!tree)
        return NULL;

    return maxTree(tree->left);
}

/**
 * @brief Get the next node
 * 
 * @param tree 
 * @return Tree* 
 */
Tree* next(Tree* tree){

    if (!tree)
        return NULL;

    return minTree(tree->right);
}

int depth(Tree* tree){

    if (!tree)
        return 0;

    int depthR, depthL;

    depthL = depth(tree->left);
    depthR = depth(tree->right);

    if (depthL < depthR)
        return depthR + 1;
    else
        return depthL + 1;
}

/*------------------------------------------------*/
/*------------------Print function----------------*/
/*------------------------------------------------*/

/**
 * @brief Print a tree leaf in prefix mode
 * 
 * @param tree 
 */
void printPrefixTree(Tree* tree){

    if (tree)
    {
        if (!tree->left && !tree->right)
            printf("Character: %c, Occurence: %d\n", tree->character, tree->occurence);

        if (tree->left)
            printPrefixTree(tree->left);

        if (tree->right)
            printPrefixTree(tree->right);

    }
}

/*In DEBUG version*/
void printInfixTree(Tree* tree){

    if (tree)
    {
        if (tree->left)
            printInfixTree(tree->left);

          
        if (!tree->left && !tree->right)
        {
            printf("Character: %c, Occurence: %d  ", tree->character, tree->occurence);
            printListBinary(tree->binary);
            printf("\n");
        }
        
        if (tree->right)
            printInfixTree(tree->right);

    }
}

void printRootTree(Tree* tree)
{
    if (tree)
        printf("Character: %c, Occurence: %d\n", tree->character, tree->occurence);

}

/**
 * @brief Print a tree leaf in postfix mode
 * 
 * @param tree 
 */
void printPostfixTree(Tree* tree){

    if (tree)
    {
        if (tree->left)
            printPostfixTree(tree->left);

        if (tree->right)
            printPostfixTree(tree->right);

        if (!tree->left && !tree->right)
            printf("Character: %c, Occurence: %d\n", tree->character, tree->occurence);
    }
}

/*------------------------------------------------*/
/*--------------Free function---------------------*/
/*------------------------------------------------*/

/**
 * @brief Free a tree
 * 
 * @param tree 
 */
void freeTree(Tree* tree){

    if (!tree)
        return;

    if (tree->left)
        freeTree(tree->left);

    if (tree->right)
        freeTree(tree->right);

    if(tree->binary)
        freeListBinary(tree->binary);
    
    free(tree);
}