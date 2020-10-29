/**** This program generates 100 random ints in an array then inserts them into a list then sorts and prints them ****/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct linkedList    //linked list struct (node)
{
    int number;
    struct linkedList *next;
};

typedef struct linkedList linkedList;  // using linkedList as the name

// function to create the list
linkedList *makeList(int data)
{
    linkedList *list = malloc(sizeof(linkedList));
    list->number = data;
    list->next = NULL;

    return list;
}

// creats an adds a node to the beginning of the list
linkedList *addToList(linkedList *list, int data)
{
    linkedList *newList = malloc(sizeof(linkedList));
    newList->number = data;
    newList->next = list;

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

int main()
{
    int randomNumbers[100] = {0};  // holds random numbers
    int i;

    srand(time(NULL));   // seed for the random number generator ---> the function rand()

    for (i = 0; i < 100; i++)
    {
        randomNumbers[i] = rand() % 200;   // generates random number between 0 and 200  0 <= n < 200
    }

    linkedList *numbersList = makeList(randomNumbers[0]);

    for (i = 1; i < 100; i++)                    // inserting tha array in the list
    {
        numbersList = addToList(numbersList, randomNumbers[i]);
    }

    sortList(numbersList);
    printList(numbersList);
    freeList(numbersList);

    return 0;
}
