#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "type.h"


/********** Basic functions *************/

// For initializing
void initList(T_List *l){
    *l=NULL;
}

bool isEmptyList(T_List l){
    return (l==NULL);
}

/********** Action on the pointers *************/

T_List getNextCell(T_List l){
    return l->next;
}

T_List getPrevCell(T_List l){
    return l->prev;
}

T_List getFirstCell(T_List l){
    while(!isEmptyList(getPrevCell(l)))
        l = getPrevCell(l);
    return l;
}

T_List getLastCell(T_List l){
    while (!isEmptyList(getNextCell(l)))
        l = getNextCell(l);
    return l;
}

Tunite* getData(T_List l){
    if (!isEmptyList(l))
        return l->pdata;
    printf("ERROR - getData : Empty list.\n");
    exit(EXIT_FAILURE);
}

/* possible ?
int* getIfData(T_List l, int mydata){
    l = getFirstCell(l);
    do {
        if (*getData(l) == mydata)
            return getData(l);
        l = getNextCell(l);
    } while (!isEmptyList(getNextCell(l)));
    printf("ERROR - getIfData : Data not in list.\n");
    exit(EXIT_FAILURE);
}
*/

void swapData(T_List source, T_List destination ){
    Tunite* temp = getData(source);
    source->pdata = getData(destination);
    destination->pdata = temp;
}

/********** Add/Remove in List *************/

T_List addFirst(T_List l, Tunite mydata){
    Tunite* data = (Tunite*)malloc(sizeof(Tunite));
    T_Cell* new = (T_Cell*)malloc(sizeof(T_Cell));
    *data = mydata;
    initList(&new->prev);
    new->pdata = data;
    new->next = l;
    if(isEmptyList(l))
        return new;
    l->prev = new;
    return new;
}

T_List addLast(T_List l, Tunite mydata){
    Tunite* data = (Tunite*)malloc(sizeof(Tunite));
    struct T_Cell* new = (struct T_Cell*)malloc(sizeof(struct T_Cell));
    *data = mydata;
    initList(&new->prev);
    new->pdata = data;
    initList(&new->next);
    if (isEmptyList(l))
        return new;
    T_List temp = l;
    while (!isEmptyList(getNextCell(temp)))
        temp = getNextCell(temp);
    temp->next = new;
    new->prev = temp;
    return l;
}

T_List addAtN(T_List l, int pos, Tunite mydata){
    if (isEmptyList(l) && pos > 0) {
        printf("WARNING - addAtN : Non zero Index in NULL List (adding first)\n");
        return addFirst(l, mydata);
    }
    if (pos == 0) {
        return addFirst(l, mydata);
    }
    Tunite* data = (Tunite*)malloc(sizeof(Tunite));
    struct T_Cell* new = (struct T_Cell*)malloc(sizeof(struct T_Cell));
    *data = mydata;
    initList(&new->prev);
    new->pdata = data;
    initList(&new->next);
    T_List temp = l;
    int index = 0;
    while (!isEmptyList(getNextCell(temp)) && index < pos - 1){
        temp = getNextCell(temp);
        index++;
    }
    if (index < pos - 1) {
        printf("WARNING - addAtN : Index out of Bounds (adding last)\n");
        return addLast(l, mydata);
    }
    new->next = getNextCell(temp);
    if (!isEmptyList(getNextCell(temp))) {
        temp->next->prev = new;
    }
    temp->next = new;
    new->prev = temp;
    return l;
}

T_List delFirst(T_List l){
    if (isEmptyList(l)){
        printf("WARNING - delFirst : List already empty.\n");
        return NULL;
    }
    T_List new = getNextCell(l);
    free(getData(l));
    free(l);
    return new;
}

T_List delLast(T_List l){
    if (isEmptyList(l)){
        printf("WARNING - delLast : List already empty.\n");
        return NULL;
    }
    if (isEmptyList(getNextCell(l))){
        free(l->pdata);
        free(l);
        return NULL;
    }
    T_List temp = l;
    while (!isEmptyList(temp->next->next))
        temp = getNextCell(temp);
    free(getData(getNextCell(temp)));
    free(getNextCell(temp));
    temp->next = NULL;
    return l;
}

T_List delAtN(T_List l, int pos){
    if (isEmptyList(l) && pos > 0) {
        printf("WARNING - delAtN : Non zero Index in NULL List (deleting first)\n");
        return NULL;
    }
    if (pos == 0) {
        return delFirst(l);
    }
    T_List temp = l;
    int index = 0;
    while (!isEmptyList(getNextCell(temp)) && index < pos){
        temp = getNextCell(temp);
        index++;
    }
    if (index < pos) {
        printf("WARNING - delAtN : Index out of Bounds (deleting last)\n");
        return delLast(l);
    }
    free(getData(temp));
    free(temp);
    *temp = *(*temp).next; // TBD demander si possible de modif
    return l;
}

/********** Others *************/

int getNbCell(T_List l){
    if (isEmptyList(l))
        return 0;
    l = getFirstCell(l);
    int n = 1;
    while(!isEmptyList(getNextCell(l))){
        n++;
        l = getNextCell(l);
    }
    return n;
}

int getSizeBytes(T_List l){
    int n = getNbCell(l);
    n = n*sizeof(T_Cell);
    return n;
}

T_List creatNewListeFromFusion(T_List l1, T_List l2){
    T_Cell* new = (T_Cell*)malloc(sizeof(T_Cell));
    new = l1;
    while(!isEmptyList(getNextCell(new)))
        new = getNextCell(new);
    new->next = l2;
    return new;
}

T_List addBehind(T_List l1, T_List l2){
    if (isEmptyList(l1)) return l2;
    if (isEmptyList(l2)) return l1;
    T_List lastCellL1 = getLastCell(l1);
    lastCellL1->next = l2;
    l2->prev = lastCellL1;
    return getFirstCell(l2);
}

/* possible ?
T_List findCell(T_List l, int data){
    l = getFirstCell(l);
    do {
        if (*(getData(l)) == data)
            return l;
        l = getNextCell(l);
    } while (!isEmptyList(getNextCell(l)));
    printf("ERROR - getData : Data not in list.\n");
    return NULL;
}

int getOccurences(T_List l, int data){
    l = getFirstCell(l);
    int n =0;
    while (!isEmptyList(l) && !isEmptyList(getNextCell(l))){
        if (*(getData(l)) == data)
            n++;
        l = getNextCell(l);
    }
    return n;
}
*/
