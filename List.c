#include <stdio.h>
#include <stdlib.h>
#include "list.h"


/********** Basic functions *************/

// For initializing
void initList(T_List *l){
    *l=NULL;
}

bool emptyList(T_List l){
    return (l==NULL);
};

/********** Action on the pointers *************/

T_List getNextCell(T_List l){
    return l->next;
}

T_List getPrevCell(T_List l){
    return l->prev;
}

T_List getFirstCell(T_List l){
    while(!initList(getPrevCell(l)))
        l = getPrevCell(l);
    return l;
}

T_List getLastCell(T_List l){
    while (l->next != NULL)
        l = l->next;
    return l;
}

int* getPtrData(T_List l){
    if (l!=NULL) return l->next;
    printf("ERROR === getPtrData : List empty.\n");
    return NULL;
}

/********** Others *************/


void afficheListeV1(T_List l){
    printf("\n< ");
    while(l != NULL){
        printf("%d, ",(*(*l).pdata));
        l = l->next;
    }
    printf(">\n");
}

T_List ajoutEnTete(T_List l, int mydata){
    int* data = (int*)malloc(sizeof(int));
    struct T_Cell* nouv = (struct T_Cell*)malloc(sizeof(struct T_Cell));
    *data = mydata;
    nouv->prev = NULL;
    nouv->pdata = data;
    nouv->next = l;
    if(l == NULL) return nouv;
    l->prev = nouv;
    return nouv;
}

T_List ajoutEnFin(T_List l, int mydata){
    int* data = (int*)malloc(sizeof(int));
    struct T_Cell* nouv = (struct T_Cell*)malloc(sizeof(struct T_Cell));
    *data = mydata;
    nouv->prev = NULL;
    nouv->pdata = data;
    nouv->next = NULL;
    if (l == NULL) return nouv;
    T_List temp = l;
    while (temp->next != NULL) temp = temp->next;
    temp->next = nouv;
    nouv->prev = temp;
    return l;
}

T_List ajoutEnN(T_List l, int pos, int mydata){
    if (l == NULL && pos > 0) {
        printf("WARNING === ajoutEnN:Non zero Index in NULL List (adding first)\n");
        return ajoutEnTete(l, mydata);
    }
    if (pos == 0) {
        return ajoutEnTete(l, mydata);
    }
    int* data = (int*)malloc(sizeof(int));
    struct T_Cell* nouv = (struct T_Cell*)malloc(sizeof(struct T_Cell));
    *data = mydata;
    nouv->prev = NULL;
    nouv->pdata = data;
    nouv->next = NULL;
    T_List temp = l;
    int index = 0;
    while (temp->next != NULL && index < pos - 1){
        temp = temp->next;
        index++;
    }
    if (index < pos - 1) {
        printf("WARNING === ajoutEnN:Index out of Bounds (adding last)\n");
        return ajoutEnFin(l, mydata);
    }
    nouv->next = temp->next;
    if (temp->next != NULL) {
        temp->next->prev = nouv;
    }
    temp->next = nouv;
    nouv->prev = temp;
    return l;
}

T_List suppEnTete(T_List l){
    if (l==NULL){
        printf("WARNING === suppEnTete:List already empty.\n");
        return NULL;
    }
    T_List nouv = l->next;
    free(l->pdata);
    free(l);
    return nouv;
}

T_List suppEnFin(T_List l){
    if (l == NULL){
        printf("WARNING === suppEnFin:List already empty.\n");
        return NULL;
    }
    if (l->next == NULL){
        free(l->pdata);
        free(l);
        return NULL;
    }
    T_List temp = l;
    while (temp->next->next != NULL) temp = temp->next;
    free(temp->next->pdata);
    free(temp->next);
    temp->next = NULL;
    return l;
}

T_List suppEnN(T_List l, int pos){
    if (l == NULL && pos > 0) {
        printf("WARNING === suppEnN:Non zero Index in NULL List (deleting first)\n");
        return NULL;
    }
    if (pos == 0) {
        return suppEnTete(l);
    }
    T_List temp = l;
    int index = 0;
    while (temp->next != NULL && index < pos){
        temp = temp->next;
        index++;
    }
    if (index < pos) {
        printf("WARNING === suppEnN:Index out of Bounds (deleting last)\n");
        return suppEnFin(l);
    }
    free(temp->pdata);
    free(temp);
    *temp = *(*temp).next;
    return l;
}


int* getPtrIfData(T_List l, int mydata){
    l = getFirstCell(l);
    do {
        if (*(l->pdata) == mydata) return l->pdata;
        l = l->next;
    } while (l->next != NULL);
    printf("ERROR === getPtrIfData : Data not in list.\n");
    return NULL;
}

void swapPtrData( T_List source, T_List destination ){
    int* temp = source->pdata;
    source->pdata = destination->pdata;
    destination->pdata = temp;
}

int getNbreCell(T_List l){
    if (l==NULL) return 0;
    l = getFirstCell(l);
    int n = 1;
    while(l->next!=NULL){
        n++;
        l = l->next;
    }
    return n;
}

int getSizeBytes(T_List l){
    int n = getNbreCell(l);
    n = n*sizeof(struct T_Cell);
    return n;
}

T_List creatNewListeFromFusion(T_List l1, T_List l2){
    struct T_Cell* nouv = (struct T_Cell*)malloc(sizeof(struct T_Cell));
    nouv = l1;
    while(nouv->next!=NULL) nouv = nouv->next;
    nouv->next = l2;
    return nouv;
}

T_List addBehind(T_List l1, T_List l2){
    if (l1 == NULL) return l2;
    if (l2 == NULL) return l1;
    T_List lastCellL1 = getLastCell(l1);
    lastCellL1->next = l2;
    l2->prev = lastCellL1;
    return getFirstCell(l2);
}

T_List findCell(T_List l, int data){
    l = getFirstCell(l);
    do {
        if (*(l->pdata) == data) return l;
        l = l->next;
    } while (l->next != NULL);
    printf("ERROR === getPtrData : Data not in list.\n");
    return NULL;
}

int getOccurences(T_List l, int data){
    l = getFirstCell(l);
    int n =0;
    while (l !=NULL && l->next != NULL){
        if (*(l->pdata) == data) n++;
        l = l->next;
    }
    return n;
}

void afficheListeV2( T_List l){
    printf("\n< ");
    if (l!=NULL){
        printf("%i, ", (*(l->pdata)));
        while(l->next!=NULL){
            l = getNextCell(l);
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
T_List genlist(int size){
    int i, n;
    T_List l = NULL;
    for(i=0;i<size;i++){
        srand(time(NULL));
        n = rand()%100;
        l = ajoutEnFin(l, n);
    }
    return l;
}

// Question 2
int* list_to_tab(T_List list,  int size){
    int i = 0, *tab;
    while(i<size && list!=NULL){
        tab[i] = *(list->pdata);
        list = suppEnTete(list);
    }
    return tab;
}























