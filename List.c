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

void setNextCell(T_List l, T_List newnext){
    l->next = newnext;
}

void setPrevCell(T_List l, T_List newprev){
    l->prev = newprev;
}

void setData(T_List l, Tunite* mydata){
    l->pdata = mydata;
}

/********** Basic functions *************/

// For initializing
void initList(T_List* l){
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

void swapData(T_List source, T_List destination ){
    Tunite* temp = getData(source); // temp = a;
    setData(source, getData(destination)); // a = b;
    setData(destination, temp); // b = temp;
}

/********** Add/Remove in List *************/

T_List addFirst(T_List l, Tunite* mydata){
    T_List new = (T_List)malloc(sizeof(T_Cell));
    setData(new, mydata);
    if (isEmptyList(l)){
        return new;
    }
    setNextCell(new, l);
    setPrevCell(l, new);
    return new;
}

T_List addLast(T_List l, Tunite* mydata){
    T_List new = (T_List)malloc(sizeof(T_Cell));
    setData(new, mydata);
    setPrevCell(new, NULL);
    setNextCell(new, NULL);
    if (isEmptyList(l)){
        return new;
    }
    T_List temp = l;
    while(!isEmptyList(getNextCell(temp))){
        temp = getNextCell(temp);
    }
    setNextCell(temp, new);
    setPrevCell(new, temp);
    return l;
}

/*
T_List addAtN(T_List l, int pos, Tunite mydata){
    if (isEmptyList(l) && pos > 0) { // Limit condition
        printf("WARNING - addAtN : Non zero Index in NULL List (adding first)\n");
        return addFirst(l, &mydata);
    }
    if (pos == 0) { // Limit condition
        return addFirst(l, &mydata);
    }
    Tunite* data = (Tunite*)malloc(sizeof(Tunite));
    struct T_Cell* new = (struct T_Cell*)malloc(sizeof(struct T_Cell));
    *data = mydata;
    T_List prevcell = getPrevCell(new);
    initList(&prevcell); // Initialize the new cell
    setData(new, data); // Setup the data of the cell
    T_List nextcell = getNextCell(new);
    initList(&nextcell); // Initialize the new cell
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
*/



T_List delFirst(T_List l){
    if (isEmptyList(l)){
        printf("WARNING - delFirst : List already empty.\n");
        return NULL;
    }
    T_List new = getNextCell(l);
    setPrevCell(new, NULL);
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


// ChatGPT's function
T_List delAtN(T_List list, int index){
    if (isEmptyList(list)){
        printf("ERROR - delAtN: Empty list.\n");
        return list;
    }
    T_List current = list;
    int count = 0;
    while (current != NULL && count < index){
        current = getNextCell(current);
        count++;
    }
    if (current == NULL){
        printf("ERROR - delAtN: Index out of bounds.\n");
        return list;
    }
    if (count == 0){
        if (current->next != NULL)
            setPrevCell(current->next, NULL);
        list = current->next;
    } else{
        if (current->prev != NULL)
            setNextCell(current->prev, current->next);
        if (current->next != NULL)
            setPrevCell(current->next, current->prev);
    }
    free(current);
    return list;
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
    if (isEmptyList(l1)) // If l1 is empty, simply return l2
        return l2;

    T_List lastCellL1 = getLastCell(l1); // Get the last cell of l1
    setNextCell(lastCellL1, l2); // Append l2 to the end of l1
    setPrevCell(l2, lastCellL1); // Set the previous pointer of l2 to the last cell of l1
    return getFirstCell(l1); // Return the first cell of the merged list
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


