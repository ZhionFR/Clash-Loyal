#ifndef LISTEDOUBLE_H_INCLUDED
#define LISTEDOUBLE_H_INCLUDED

#include <stdbool.h>

////////////////////////////    Step 1    ////////////////////////////

typedef struct T_cell{
    struct T_cell *suiv;
    struct T_cell *prec;
    int *pdata;              //attention à faire un malloc sur ce champ avant de s'en servir
} T_cellule;
typedef T_cellule *T_liste;

/********** Basic functions *************/

void initList(T_liste *l);
bool emptyList( T_liste l);

/********** Action on the pointers *************/


void afficheListeV1( T_liste l);
//Pour "AfficheListeV1" Vous avez le droit de lire directement dans la structure de données
//Utile pour afficher et debuguer les fonctions ci-dessous

T_liste ajoutEnTete(T_liste l, int mydata); //Bien mettre à NULL les champs suiv et prec non utilisés s'il y en a
T_liste ajoutEnFin(T_liste l, int mydata);
T_liste ajoutEnN(T_liste l, int pos, int mydata);

T_liste suppEnTete(T_liste l);
T_liste suppEnFin(T_liste l);
T_liste suppEnN(T_liste l, int pos);

T_liste getptrFirstCell(T_liste l);
T_liste getptrLastCell(T_liste l);
T_liste getptrNextCell(T_liste l);
T_liste getptrPrevCell(T_liste l);

int* getPtrData(T_liste l);
int* getPtrIfData(T_liste l, int mydata);
void swapPtrData( T_liste source, T_liste destination );

int getNbreCell(T_liste l);
int getSizeBytes(T_liste l);

T_liste creatNewListeFromFusion(T_liste l1, T_liste l2);
T_liste addBehind(T_liste debut, T_liste suite);

T_liste findCell(T_liste l, int data);
int getOccurences(T_liste l, int data);


void afficheListeV2( T_liste l);

////////////////////////////    Step 2    ////////////////////////////
// Utils
void affichetab(int* tab, int size);


void tri_selection(int* tab, int n);

//Q1
T_liste genlist(int size);

//Q2
int* list_to_tab(T_liste list,  int size);


#endif // LISTEDOUBLE_H_INCLUDED

