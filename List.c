#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "type.h"

/********** Basic Getters / Setters *************/

T_List getNextCell(T_List l){
    return l->next;
}

T_List getPrevCell(T_List l){
    return l->prev;
}

Tunite* getData(T_List l){
    if (!isEmptyList(l))
        return l->pdata;
    printf("ERROR - getData : Empty list.\n");
    exit(EXIT_FAILURE);
}

void setNextCell(T_List l1, T_List l2){
    l1->next = l2;
}

void setPrevCell(T_List l1, T_List l2){
    l1->prev = l2;
}

void setData(T_List l, Tunite* mydata){
    l->pdata = mydata;
}

/********** Basic functions *************/

// For initializing
void initList(T_List *l){
    *l=NULL;
}

bool isEmptyList(T_List l){
    return (l==NULL);
}



/********** Action on the pointers *************/


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
    Tunite* temp = getData(source); // temp = a;
    setData(source, getData(destination)); // a = b;
    setData(destination, temp); // b = temp;
}

/********** Add/Remove in List *************/

T_List addFirst(T_List l, Tunite mydata){
    Tunite* data = (Tunite*)malloc(sizeof(Tunite));
    T_Cell* new = (T_Cell*)malloc(sizeof(T_Cell));
    *data = mydata;
    initList(&new->prev); // Pas possible de faire initList(&getPrevCell(new)); Sinon, utiliser le code commenté ci-dessous.
// Sinon, T_List prev; prev = getPrevCell(new); initList(&prev);
    setData(new, data); // Setup the data of the cell
    setNextCell(new,l); // Setup the pointer new to l
    if(isEmptyList(l))
        return new;
    setPrevCell(l, new); // Setup the pointer l to new (if l!=NULL)
    return new;
}

//void initPrevCell(T_Cell* l){
//  initList(&l->prev)
//}

T_List addLast(T_List l, Tunite mydata){
    Tunite* data = (Tunite*)malloc(sizeof(Tunite));
    struct T_Cell* new = (struct T_Cell*)malloc(sizeof(struct T_Cell));
    *data = mydata;
    initList(getPrevCell(new)); // Initialize the new cell
    setData(new, data); // Setup the data of the cell
    initList(getNextCell(new)); // Initialize the new cell
    if (isEmptyList(l))
        return new;
    T_List temp = l;
    while (!isEmptyList(getNextCell(temp))) // Traverse the list to reach the last cell
        temp = getNextCell(temp);
    setNextCell(temp, new); // Setup the pointer temp to new
    setPrevCell(new, temp); // Setup the pointer new to temp
    return l;
}

T_List addAtN(T_List l, int pos, Tunite mydata){
    if (isEmptyList(l) && pos > 0) { // Limit condition
        printf("WARNING - addAtN : Non zero Index in NULL List (adding first)\n");
        return addFirst(l, mydata);
    }
    if (pos == 0) { // Limit condition
        return addFirst(l, mydata);
    }
    Tunite* data = (Tunite*)malloc(sizeof(Tunite));
    struct T_Cell* new = (struct T_Cell*)malloc(sizeof(struct T_Cell));
    *data = mydata;
    initList(getPrevCell(new)); // Initialize the new cell
    setData(new, data); // Setup the data of the cell
    initList(getNextCell(new)); // Initialize the new cell
    T_List temp = l;
    int index = 0;
    while (!isEmptyList(getNextCell(temp)) && index < pos - 1){ // Traverse the list to reach the Nth cell
        temp = getNextCell(temp);
        index++;
    }
    if (index < pos - 1) { // If pos > len list
        printf("WARNING - addAtN : Index out of Bounds (adding last)\n");
        return addLast(l, mydata);
    }
    setNextCell(new, getNextCell(temp)); // TBD
    if (!isEmptyList(getNextCell(temp))){
        setPrevCell(getNextCell(temp), new);
    }
    setNextCell(temp, new); // Setup the pointer temp to new
    setPrevCell(new, temp); // Setup the pointer new to temp
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
    if (isEmptyList(l)){ // Limit condition
        printf("WARNING - delLast : List already empty.\n");
        return NULL;
    }
    if (isEmptyList(getNextCell(l))){ // Limit condition
        free(getData(l));
        free(l);
        return NULL;
    }
    T_List temp = l;
    while (!isEmptyList(getNextCell(getNextCell(temp)))) // Traverse the list to reach the last cell
        temp = getNextCell(temp);
    free(getData(getNextCell(temp)));
    free(getNextCell(temp));
    setNextCell(temp, NULL);
    return l;
}

T_List delAtN(T_List l, int pos){
    if (isEmptyList(l) && pos > 0) { // Limit condition
        printf("WARNING - delAtN : Non zero Index in NULL List (deleting first)\n");
        return NULL;
    }
    if (pos == 0) { // Limit condition
        return delFirst(l);
    }
    T_List temp = l;
    int index = 0;
    while (!isEmptyList(getNextCell(temp)) && index < pos){ // Traverse the list to reach the Nth cell
        temp = getNextCell(temp);
        index++;
    }
    if (index < pos){ // If pos > len list
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
    if (isEmptyList(l)) // Limit condition
        return 0;
    l = getFirstCell(l);
    int n = 1;
    while(!isEmptyList(getNextCell(l))){ // Traverse the list
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
    while(!isEmptyList(getNextCell(new))) // Traverse the l1 list to reach the last cell
        new = getNextCell(new);
    setNextCell(new, l2);
    return new;
}

T_List addBehind(T_List l1, T_List l2){
    if (isEmptyList(l1)) // Limit condition
        return l2;
    if (isEmptyList(l2)) // Limit condition
        return l1;
    T_List lastCellL1 = getLastCell(l1);
    setNextCell(lastCellL1, l2);
    setPrevCell(l2, lastCellL1);
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


