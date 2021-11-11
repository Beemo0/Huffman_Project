#include "list.h"

/*------------------------------------------------*/
/*---------------Insert function------------------*/
/*------------------------------------------------*/

List* addToList(List* list, char character)
{

    if (list == NULL)
    {
        list = malloc(sizeof(List));
        if (!list){
            printf("Error: Allocation");
            exit(1);
        }

        list->tree = init(character, 1);
        list->next = NULL;
        return list;

    } else {
        
        List* tmp = list;

        while (tmp != NULL)
        {
            if (tmp->tree != NULL)
            {
                if (character == tmp->tree->character)
                {
                    tmp->tree->occurence++;
                    return list;
                }
            }
            tmp = tmp->next;
        }
        
        /* If the character isn't already in the list*/
        tmp = NULL;
        tmp = malloc(sizeof(List));
        if (!tmp){
            printf("Error: Allocation");
            exit(1);
        }

        tmp->tree = init(character, 1);
        tmp->next = list;
        return tmp;
    }
}

List* insertList(List* list, Tree* tree)
{
    if (list == NULL)
    {
        list = malloc(sizeof(List));
        if (!list){
            printf("Error: Allocation");
            exit(1);
        }

        list->tree = tree;
        list->next = NULL;
        return list;

    } else {
        
        List* tmp = NULL;
        tmp = malloc(sizeof(List));
        if (!tmp){
            printf("Error: Allocation");
            exit(1);
        }

        tmp->tree = tree;
        tmp->next = list;
        return tmp;
    }
}

/*------------------------------------------------*/
/*------------Function MERGE SORT-----------------*/
/*------------------------------------------------*/


List* fSort(List* list)
{
    /*If the list only has 2 element*/
    if (lenghtList(list) == 2)
    {
        if (list->tree->occurence > list->next->tree->occurence)
        {
            List* tmp = NULL;

            /*Swap the two node in a new List*/
            insertList(tmp, list->tree);
            insertList(tmp, list->next->tree);

            freeList(list);  //Free the old List
            
            return tmp;        
        }

        return list;
    }

    /*Else merge sort*/
    return fSortHide(list);
}


//Possibilite d'utiliser des threads
List* fSortHide(List* list)
{
    /*If the current or next node is null: stop*/
    if(list == NULL || list->next == NULL)
        return list;
    
    /*Else Divide and Conquer*/

    List* left = NULL;
    List* right = NULL;

    splitList(list, &left, &right);  //Split the current list in two

    left = fSortHide(left);          //Recursively sort the first half
    right = fSortHide(right);        //Recursively sort the second half

    return mergeList(left, right);   //Merge the two list
}

/**
 * @brief Merge two list
 * 
 * @param n1 
 * @param n2 
 * @return List* 
 */
List* mergeList(List* n1, List* n2) {

    if(n1 == NULL) 
        return n2;
    
    if(n2 == NULL)
        return n1;

    List* head = NULL;

    if(n1->tree->occurence <= n2->tree->occurence)
    {
        head = n1;
        head->next = mergeList(n1->next, n2);
    } else {
        head = n2;
        head->next = mergeList(n1, n2->next);
    }

    return head;
}

/**
 * @brief Split a list into n1 and n2
 * 
 * @param list 
 * @param n1 
 * @param n2 
 */
void splitList(List* list, List** n1, List** n2) 
{ 
	List* left = NULL; 
	List* right = NULL; 
    
	left = list; 
    right = list->next; 

	//Get left to the middle point of list
	while (right != NULL)
    { 
		right = right->next;
		if (right != NULL)
        { 
			left = left->next; 
			right = right->next; 
		} 
	}

    *n1 = list;        //n1 is the first half of list

    *n2 = left->next;  //n2 is the second half of list
	left->next = NULL; //Left->next is the end of the first half
} 

/*------------------------------------------------*/
/*----------------Utility function----------------*/
/*------------------------------------------------*/

/**
 * @brief Get the lenght of a list 
 * 
 * @param list 
 * @return int 
 */
int lenghtList(List* list)
{
    if (!list) 
        return 0;

    return lenghtList(list->next) + 1;
}

/**
 * @brief Print the list
 * 
 * @param list 
 */
void printList(List* list){

    if (!list)
        return;

    printInfixTree(list->tree);

    printList(list->next);
}

/**
 * @brief Free the list
 * 
 * @param list 
 */
void freeList(List* list){

    if (list == NULL)
        return;

    freeList(list->next);

    free(list);
}
