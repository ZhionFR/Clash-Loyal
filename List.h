#ifndef LISTEDOUBLE_H_INCLUDED
#define LISTEDOUBLE_H_INCLUDED

#include <stdbool.h>
#include "type.h"
/********** Basic Get / Set *************/

T_List getNextCell(T_List l);
T_List getPrevCell(T_List l);
Tunite* getData(T_List l);

void setNextCell(T_List l1, T_List l2);
void setPrevCell(T_List l1, T_List l2);
void setData(T_List l, Tunite* mydata);

/********** Basic functions *************/

void initList(T_List *l);

bool isEmptyList(T_List l);


/********** Functions on the pointers *************/

T_List getFirstCell(T_List l);
T_List getLastCell(T_List l);
int* getIfData(T_List l, int mydata);
void swapData( T_List source, T_List destination );
//Pour "AfficheListeV1" Vous avez le droit de lire directement dans la structure de données
//Utile pour afficher et debuguer les fonctions ci-dessous

/********** Add/Remove in List *************/

T_List addFirst(T_List l, Tunite mydata); //Bien mettre à NULL les champs suiv et prec non utilisés s'il y en a
T_List addLast(T_List l, Tunite mydata);
T_List addAtN(T_List l, int pos, Tunite mydata);

T_List delFirst(T_List l);
T_List delLast(T_List l);
T_List delAtN(T_List l, int pos);

/********** Others *************/

int lenList(T_List l);
int getNbCell(T_List l);
int getSizeBytes(T_List l);

T_List creatNewListFromFusion(T_List l1, T_List l2);
T_List addBehind(T_List debut, T_List suite);

T_List findCell(T_List l, int data);
int getOccurences(T_List l, int data);

/********** Printing Functions *************/

void displayListV1( T_List l);
void displayListV2( T_List l);


// Utils
void displayTab(int* tab, int size);


void selectionSort(int* tab, int n);

//Q1
T_List genList(int size);

//Q2
int* listToTab(T_List list,  int size);


#endif // LISTEDOUBLE_H_INCLUDED

