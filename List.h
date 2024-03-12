#ifndef LISTEDOUBLE_H_INCLUDED
#define LISTEDOUBLE_H_INCLUDED

#include <stdbool.h>

////////////////////////////    Step 1    ////////////////////////////

typedef struct T_Cell{
    struct T_Cell *next;
    struct T_Cell *prev;
    int *pdata;              // Be careful to do a malloc before using this
} T_Cell;
typedef T_Cell *T_List;

/********** Basic functions *************/

void initList(T_List *l);
bool isEmptyList(T_List l);

/********** Functions on the pointers *************/

T_List getNextCell(T_List l);
T_List getPrevCell(T_List l);
T_List getFirstCell(T_List l);
T_List getLastCell(T_List l);
int* getData(T_List l);
int* getIfData(T_List l, int mydata);
void swapData( T_List source, T_List destination );
//Pour "AfficheListeV1" Vous avez le droit de lire directement dans la structure de donn�es
//Utile pour afficher et debuguer les fonctions ci-dessous

T_List addFirst(T_List l, int mydata); //Bien mettre � NULL les champs suiv et prec non utilis�s s'il y en a
T_List addLast(T_List l, int mydata);
T_List addAtN(T_List l, int pos, int mydata);

T_List delFirst(T_List l);
T_List delLast(T_List l);
T_List delAtN(T_List l, int pos);

int getNbCell(T_List l);
int getSizeBytes(T_List l);

T_List creatNewListFromFusion(T_List l1, T_List l2);
T_List addBehind(T_List debut, T_List suite);

T_List findCell(T_List l, int data);
int getOccurences(T_List l, int data);

/********** Printing Functions *************/

void displayListV1( T_List l);
void displayListV2( T_List l);

////////////////////////////    Step 2    ////////////////////////////
// Utils
void displayTab(int* tab, int size);


void selectionSort(int* tab, int n);

//Q1
T_List genList(int size);

//Q2
int* listToTab(T_List list,  int size);


#endif // LISTEDOUBLE_H_INCLUDED

