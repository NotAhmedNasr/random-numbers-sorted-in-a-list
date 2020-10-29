/**** This program generates 200 random ints in an array then inserts them into a list then sorts, remove duplicates and prints them ****/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ELEMENTS 200
#define RANGE 50

struct linkedList    //linked list struct (node)
{
    int number;
    struct linkedList *next;
    struct linkedList *prev;
};

typedef struct linkedList linkedList;  // using linkedList as the name

// function to create the list
linkedList *makeList(int data)
{
    linkedList *list = malloc(sizeof(linkedList));
    list->number = data;
    list->next = NULL;
    list->prev = NULL;

    return list;
}

// creats an adds a node to the beginning of the list
linkedList *addToList(linkedList *list, int data)
{
    linkedList *newList = makeList(data);
    newList->next = list;
    list->prev = newList;

    return newList;
}

// free the list after usage
void freeList(linkedList *list)
{
    if (list == NULL)
    {
        return;
    }
    freeList(list->next);
    free(list);
}

// useing bubble sort as requested to sort the list
void sortList(linkedList *list)
{
    int swapsInLoop, temp;   // flags used to control while loop
    linkedList *traverser;   // used to traverse the list

    if (list == NULL)
    {
        return;
    }

    do
    {
        swapsInLoop = 0;
        traverser = list;

        while (traverser->next != NULL)  // this loop contains the bubble logic in a asingle loop
        {
            if (traverser->number > traverser->next->number)
            {
                temp = traverser->number;
                traverser->number = traverser->next->number;
                traverser->next->number = temp;
                swapsInLoop++;
            }
            traverser = traverser->next;
        }

    }while(swapsInLoop != 0);   // if no swaps happened in a loop then the list is sorted
}

// prints the list on the screen
void printList(linkedList *list)
{
    int i = 0;
    if (list == NULL)
    {
        return;
    }

    linkedList *traverser = list;

    while(traverser != NULL)
    {
        printf("[%d]: %d\n", ++i, traverser->number);
        traverser = traverser->next;
    }
}

// this removes a node from the list
void deleteNode(linkedList *node)
{
    if (node->next == NULL)  // checks if it is the last node
    {
        node->prev->next = node->next;
    }
    else if (node->prev == NULL)   // checks if it is the first node
    {
        node->next->prev = node->prev;
    }
    else
    {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }

    free(node);
}


// clears dubs from sorted list
void clearDubs(linkedList *list)
{
    linkedList *traverser, *deleted;
    int number;

    if (list == NULL)
    {
        return;
    }

    traverser = list->next;

    while(traverser != NULL && traverser->prev != NULL)
    {
        if (traverser->number == traverser->prev->number)
        {
            deleted = traverser;
            traverser = traverser->next;
            deleteNode(deleted);
        }
        else
        {
            traverser = traverser->next;
        }
    }
}

int main()
{
    int randomNumbers[ELEMENTS] = {0};  // holds random numbers
    int i;

    srand(time(NULL));   // seed for the random number generator ---> the function rand()

    for (i = 0; i < ELEMENTS; i++)
    {
        randomNumbers[i] = rand() % RANGE;   // generates random number between 0 and 200  0 <= n < 200
        printf("%d\n", randomNumbers[i]);
    }

    linkedList *numbersList = makeList(randomNumbers[0]);

    for (i = 1; i < ELEMENTS; i++)                    // inserting tha array in the list
    {
        numbersList = addToList(numbersList, randomNumbers[i]);
    }

    sortList(numbersList);
    clearDubs(numbersList);
    printList(numbersList);
    freeList(numbersList);

    return 0;
}
