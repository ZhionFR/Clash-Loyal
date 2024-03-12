#include <stdio.h>
#include <stdlib.h>
#include "list.h"



////////////////////////////    Step 1    ////////////////////////////


void initListe(T_liste *l){
    *l=NULL;
}

bool listeVide(T_liste l){
    return (l==NULL);
};

void afficheListeV1(T_liste l){
    printf("\n< ");
    while(l != NULL){
        printf("%d, ",(*(*l).pdata));
        l = l->suiv;
    }
    printf(">\n");
}

T_liste ajoutEnTete(T_liste l, int mydata){
    int* data = (int*)malloc(sizeof(int));
    struct T_cell* nouv = (struct T_cell*)malloc(sizeof(struct T_cell));
    *data = mydata;
    nouv->prec = NULL;
    nouv->pdata = data;
    nouv->suiv = l;
    if(l == NULL) return nouv;
    l->prec = nouv;
    return nouv;
}

T_liste ajoutEnFin(T_liste l, int mydata){
    int* data = (int*)malloc(sizeof(int));
    struct T_cell* nouv = (struct T_cell*)malloc(sizeof(struct T_cell));
    *data = mydata;
    nouv->prec = NULL;
    nouv->pdata = data;
    nouv->suiv = NULL;
    if (l == NULL) return nouv;
    T_liste temp = l;
    while (temp->suiv != NULL) temp = temp->suiv;
    temp->suiv = nouv;
    nouv->prec = temp;
    return l;
}

T_liste ajoutEnN(T_liste l, int pos, int mydata){
    if (l == NULL && pos > 0) {
        printf("WARNING === ajoutEnN:Non zero Index in NULL List (adding first)\n");
        return ajoutEnTete(l, mydata);
    }
    if (pos == 0) {
        return ajoutEnTete(l, mydata);
    }
    int* data = (int*)malloc(sizeof(int));
    struct T_cell* nouv = (struct T_cell*)malloc(sizeof(struct T_cell));
    *data = mydata;
    nouv->prec = NULL;
    nouv->pdata = data;
    nouv->suiv = NULL;
    T_liste temp = l;
    int index = 0;
    while (temp->suiv != NULL && index < pos - 1){
        temp = temp->suiv;
        index++;
    }
    if (index < pos - 1) {
        printf("WARNING === ajoutEnN:Index out of Bounds (adding last)\n");
        return ajoutEnFin(l, mydata);
    }
    nouv->suiv = temp->suiv;
    if (temp->suiv != NULL) {
        temp->suiv->prec = nouv;
    }
    temp->suiv = nouv;
    nouv->prec = temp;
    return l;
}

T_liste suppEnTete(T_liste l){
    if (l==NULL){
        printf("WARNING === suppEnTete:List already empty.\n");
        return NULL;
    }
    T_liste nouv = l->suiv;
    free(l->pdata);
    free(l);
    return nouv;
}

T_liste suppEnFin(T_liste l){
    if (l == NULL){
        printf("WARNING === suppEnFin:List already empty.\n");
        return NULL;
    }
    if (l->suiv == NULL){
        free(l->pdata);
        free(l);
        return NULL;
    }
    T_liste temp = l;
    while (temp->suiv->suiv != NULL) temp = temp->suiv;
    free(temp->suiv->pdata);
    free(temp->suiv);
    temp->suiv = NULL;
    return l;
}

T_liste suppEnN(T_liste l, int pos){
    if (l == NULL && pos > 0) {
        printf("WARNING === suppEnN:Non zero Index in NULL List (deleting first)\n");
        return NULL;
    }
    if (pos == 0) {
        return suppEnTete(l);
    }
    T_liste temp = l;
    int index = 0;
    while (temp->suiv != NULL && index < pos){
        temp = temp->suiv;
        index++;
    }
    if (index < pos) {
        printf("WARNING === suppEnN:Index out of Bounds (deleting last)\n");
        return suppEnFin(l);
    }
    free(temp->pdata);
    free(temp);
    *temp = *(*temp).suiv;
    return l;
}

T_liste getptrFirstCell(T_liste l){
    while (l->prec != NULL) l = l->prec;
    return l;
}

T_liste getptrLastCell(T_liste l){
    while (l->suiv != NULL) l = l->suiv;
    return l;
}

T_liste getptrNextCell(T_liste l){
    return l->suiv;
}

T_liste getptrPrevCell(T_liste l){
    return l->prec;
}

int* getPtrData(T_liste l){
    if (l!=NULL) return l->suiv;
    printf("ERROR === getPtrData : List empty.\n");
    return NULL;
}


int* getPtrIfData(T_liste l, int mydata){
    l = getptrFirstCell(l);
    do {
        if (*(l->pdata) == mydata) return l->pdata;
        l = l->suiv;
    } while (l->suiv != NULL);
    printf("ERROR === getPtrIfData : Data not in list.\n");
    return NULL;
}

void swapPtrData( T_liste source, T_liste destination ){
    int* temp = source->pdata;
    source->pdata = destination->pdata;
    destination->pdata = temp;
}

int getNbreCell(T_liste l){
    if (l==NULL) return 0;
    l = getptrFirstCell(l);
    int n = 1;
    while(l->suiv!=NULL){
        n++;
        l = l->suiv;
    }
    return n;
}

int getSizeBytes(T_liste l){
    int n = getNbreCell(l);
    n = n*sizeof(struct T_cell);
    return n;
}

T_liste creatNewListeFromFusion(T_liste l1, T_liste l2){
    struct T_cell* nouv = (struct T_cell*)malloc(sizeof(struct T_cell));
    nouv = l1;
    while(nouv->suiv!=NULL) nouv = nouv->suiv;
    nouv->suiv = l2;
    return nouv;
}

T_liste addBehind(T_liste l1, T_liste l2){
    if (l1 == NULL) return l2;
    if (l2 == NULL) return l1;
    T_liste lastCellL1 = getptrLastCell(l1);
    lastCellL1->suiv = l2;
    l2->prec = lastCellL1;
    return getptrFirstCell(l2);
}

T_liste findCell(T_liste l, int data){
    l = getptrFirstCell(l);
    do {
        if (*(l->pdata) == data) return l;
        l = l->suiv;
    } while (l->suiv != NULL);
    printf("ERROR === getPtrData : Data not in list.\n");
    return NULL;
}

int getOccurences(T_liste l, int data){
    l = getptrFirstCell(l);
    int n =0;
    while (l !=NULL && l->suiv != NULL){
        if (*(l->pdata) == data) n++;
        l = l->suiv;
    }
    return n;
}

void afficheListeV2( T_liste l){
    printf("\n< ");
    if (l!=NULL){
        printf("%i, ", (*(l->pdata)));
        while(l->suiv!=NULL){
            l = getptrNextCell(l);
            printf("%i, ", (*(l->pdata)));
        }
    }
    printf(">\n");
}

////////////////////////////    Step 2    ////////////////////////////
#include <time.h>

// STARTUtils
void affichetab(int* tab, int size){
    int i;
    printf("\n[");
    if (size>=1) printf("%i", tab[0]);
    for(i=1;i<size;i++){
        printf(", %i", tab[i]);
    }
    printf("]\n");
}


// ENDUtils

void tri_selection(int* tab, int size){
    int i, j, min, temp;

    for (i=0; i<size-1; i++){
        min = i;
        for (j=i; j<size; j++)if (tab[j]<tab[min]) min = j;
        temp = tab[i];
        tab[i] = tab[min];
        tab[min] = temp;
    }
}

// Question 1
T_liste genlist(int size){
    int i, n;
    T_liste l = NULL;
    for(i=0;i<size;i++){
        srand(time(NULL));
        n = rand()%100;
        l = ajoutEnFin(l, n);
    }
    return l;
}

// Question 2
int* list_to_tab(T_liste list,  int size){
    int i = 0, *tab;
    while(i<size && list!=NULL){
        tab[i] = *(list->pdata);
        list = suppEnTete(list);
    }
    return tab;
}























