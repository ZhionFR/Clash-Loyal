#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED

#include <stdbool.h>

typedef struct T_Cell{
    struct T_Cell *next;
    struct T_Cell *prev;
    int *pdata; //Careful to do a malloc on this field before using it
} T_Cell;
typedef T_Cell *T_List;

void initList(T_List *l);
bool isEmptyList(T_List l);

void displayListV1(T_List l);

T_List addAtHead(T_List l, int mydata);
T_List addAtEnd(T_List l, int mydata);
T_List addAtN(T_List l, int pos, int mydata);

T_List delAtHead(T_List l);
T_List delAtEnd(T_List l);
T_List delAtN(T_List l, int pos);

T_List getptrFirstCell(T_List l);
T_List getptrLastCell(T_List l);
T_List getptrNextCell(T_List l);
T_List getptrPrevCell(T_List l);

int* getPtrData(T_List l);
void swapPtrData( T_List source, T_List destination );

int getNbrCell(T_List l);
int getSizeBytes(T_List l);

T_List creatNewListFromFusion(T_List l1, T_List l2);
T_List addBehind(T_List start, T_List end);

T_List findCell(T_List l, int data);
int getOccurences(T_List l, int data);  // Number of time data is present in l1

void displayListV2( T_List l);


// Part 2

void selectionSort(int *tab, int length);

T_List createRandomList(int n);
int* listToArray(T_List l, int *size);
int* listToArrayWithMemoryFree(T_List *originalList, int *size);
T_List arrayToList(int *arr, int size);

// TBD : Faire encapsulation si besoin sur tout le reste du code


#endif // LIST_H_INCLUDED
