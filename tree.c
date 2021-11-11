#include "tree.h"

/**
 * @brief Function to initialise a new node with a value
 *
 * @param value
 * @return Tree*
 */
Tree* init(char character, int occurence){

    Tree* tmp = NULL;
    tmp = malloc(sizeof(Tree*));

    if (!tmp){
        printf("Error: Can't allocate memory\n");
        exit(1);
    }

    /*Initialise value*/
    tmp->character = character;
    tmp->occurence = occurence;
    tmp->left = NULL;
    tmp->right = NULL;

    return tmp;
}

/**
 * @brief Function to insert a new node in the Tree*
 *
 * @param Tree*
 * @param value
 */
Tree* fusionTree(Tree* t1, Tree* t2){

    Tree* tree = malloc(sizeof(Tree*));
    tree->occurence = 0;
    tree->left = t1;
    tree->right = t2;

    if (t1)
        tree->occurence += t1->occurence;

    if (t2)
        tree->occurence += t2->occurence;

    return tree;
}

Tree* minTree(Tree* tree){

    if (!tree)
        return NULL;

    if (!tree->left)
        return tree;

    return minTree(tree->left);
}

Tree* maxTree(Tree* tree){

    if (!tree)
        return NULL;

    if (!tree->right)
        return tree;

    return maxTree(tree->right);
}

Tree* previous(Tree* tree){

    if (!tree)
        return NULL;

    return maxTree(tree->left);
}

Tree* next(Tree* tree){

    if (!tree)
        return NULL;

    return minTree(tree->right);
}

/*Free function*/

void freeTree(Tree* tree){

    if (!tree)
        return;

    if (tree->left)
        freeTree(tree->left);

    if (tree->right)
        freeTree(tree->right);

    free(tree);
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

/* Print function */

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

void printInfixTree(Tree* tree){

    if (tree)
    {
        if (tree->left)
            printInfixTree(tree->left);

        if (!tree->left && !tree->right)
            printf("Character: %c, Occurence: %d\n", tree->character, tree->occurence);

        if (tree->right)
            printInfixTree(tree->right);

    }
}

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
