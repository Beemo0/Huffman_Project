#include "list.h"

/*------------------------------------------------*/
/*---------------Insert function------------------*/
/*------------------------------------------------*/

List* addToList(List* list, char character)
{
    if (list == NULL)
    {
        list = (List*)malloc(sizeof(List));
        if (!list){
            perror("Error: Allocation");
            exit(1);
        }

        list->tree = init(character, 1);
        list->next = NULL;
        return list;

    } else {
        
        /*Search for the character in the List*/
        List* tmp1 = list;

        while (tmp1 != NULL)
        {
            if (tmp1->tree != NULL)
            {
                if (character == tmp1->tree->character)
                {
                    tmp1->tree->occurence++;
                    return list;
                }
            }
            tmp1 = tmp1->next;
        }

        /*If the character isn't already in the list*/
        /*Create a new node for it*/
        List* tmp2 = list;

        tmp2 = NULL;
        tmp2 = (List*)malloc(sizeof(List));
        if (!tmp2){
            perror("Error: Allocation");
            exit(1);
        }

        tmp2->tree = init(character, 1);
        tmp2->next = list;
        return tmp2;
    }
}

List* insertList(List* list, Tree* tree)
{
    if (list == NULL)
    {
        list = (List*)malloc(sizeof(List));
        if (!list){
            perror("Error: Allocation");
            exit(1);
        }

        list->tree = tree;
        list->next = NULL;
        return list;

    } else {
        
        List* tmp = NULL;
        tmp = (List*)malloc(sizeof(List));
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
            tmp = insertList(tmp, list->tree);
            tmp = insertList(tmp, list->next->tree);

            freeList(list);  //Free the old List
            
            return tmp;        
        }

        return list;
    }

    /*Else merge sort*/
    return fSortHide(list);
}


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
 * @brief Merge two List
 * 
 * @param n1 
 * @param n2 
 * @return List* 
 */
List* mergeList(List* n1, List* n2) {

    if(n1 == NULL)      //If n1 is empty return the other list
        return n2;
    
    if(n2 == NULL)      //If n2 is empty return the other list
        return n1;

    List* head = NULL;

    /*Recursively order the new list "head" with the other two*/
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
 * @brief Split a List into two List n1 and n2
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
	left->next = NULL;
}

/*------------------------------------------------*/
/*------------------------------------------------*/
/*------------------------------------------------*/
//DEBUG
void createHuffmanTree(List** list){

    /*If the list is empty*/
    if (*list == NULL)
        return;
    
    List* n1 = NULL;
    List* n2 = NULL;

    /*While the list doesn't content only one element*/
    while ((*list) != NULL && (*list)->next != NULL)
    {   
        /*Sort the List*/
        (*list) = fSort((*list));

        /*Take the two lowest element (in term of occurences)*/
        n1 = (*list);
        n2 = (*list)->next;

        /*Merge their tree into a single one*/
        Tree* t1 = NULL;
        t1 = mergeTree(n1->tree, n2->tree);

        /*Pop thee element out of the List*/
        popList(list);
        popList(list);

        /*Insert the new tree contening the two old tree*/
        (*list) = insertList((*list), t1); 
    }
}

/*------------------------------------------------*/
/*----------------Utility function----------------*/
/*------------------------------------------------*/

/**
 * @brief Get the lenght of a List 
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
 * @brief Print a List
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
 * @brief Free a List
 * 
 * @param list 
 */
void freeList(List* list){

    if (list == NULL)
        return;

    freeList(list->next);

    free(list);
}

/**
 * @brief Free the first element of a List
 * 
 * @param list 
 */
void popList(List** list){

    if (list == NULL)
        return;
    
    List* tmp = *list;
    (*list) = (*list)->next;

    free(tmp);

}