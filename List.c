#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "List.h"

// Create an empty list
void initList(T_List *l){ // No malloc, just initialize at NULL the pointer
    *l=NULL;
}

// Check if the list is empty
bool isEmptyList(T_List l){ // Check if a list is empty
    return (l==NULL);
}

T_List getptrNextCell(T_List l){
    if (isEmptyList(l)){
        printf("getptrNextCell: WARNING - No next cell\n");
        return NULL;
    }
    return l->next;
}

T_List getptrPrevCell(T_List l){
    if (isEmptyList(l)){
        printf("getptrPrevCell: WARNING - No previous cell\n");
        return NULL;
    }
    return l->prev;
}

T_List getptrFirstCell(T_List l){
    if (isEmptyList(l)){
        printf("getptrFirstCell - WARNING Empty List (Return NULL)");
        return NULL;
    }
    while (!isEmptyList(getptrPrevCell(l))){
        l = getptrPrevCell(l);
    }
    return l;
}

T_List getptrLastCell(T_List l){
    if (isEmptyList(l)){
        printf("getptrLastCell - WARNING Empty List (Return NULL)");
        return NULL;
    }
    while (!isEmptyList(l->next)){
        l = l->next;
    }
    return l;
}



int* getPtrData(T_List l){
    return l->pdata;
}

void swapPtrData(T_List source, T_List destination){
    if (isEmptyList(source) || isEmptyList(destination)){
        printf("swapPtrData: ERROR - One or both pointers are NULL\n");
        exit(EXIT_FAILURE);
    }
    int *temp = source->pdata;
    source->pdata = destination->pdata;
    destination->pdata = temp;
}

// Display the list ( [1;2;3;...] )
void displayListV1(T_List l){
    T_List current = l;
    printf("[");
    while(!isEmptyList(current)){
        printf("%d",*(current->pdata));
        if(!isEmptyList(current->next)){
            printf(";");
        }
        current = current->next;
    }
    printf("]\n");
}

// Add an element to the head of a list
T_List addAtHead(T_List l, int mydata){
    T_List new = (T_List)malloc(sizeof(T_List));
    new->pdata = (int*)malloc(sizeof(int));
    *(new->pdata)=mydata; // Modify the content at the pointer's adress
    if (isEmptyList(l)) // Creat first cell of the list
    {
        initList(&new->next);
        initList(&new->prev);
    }
    else // List not empty, so need to make the connections
{
        new->next = l;
        initList(&new->prev);
        l->prev = new;
    }
    return new;
}

// Add an element to the end of a list
T_List addAtEnd(T_List l, int mydata){
    T_List new = (T_List)malloc(sizeof(T_Cell));
    if (isEmptyList(new)){
        printf("ERROR - addAtEnd : Memory allocation failed (Code : 1)");
        exit(EXIT_FAILURE);
    }
    new->pdata = (int*)malloc(sizeof(int));
    if (new->pdata == NULL){
        printf("ERROR - addAtEnd : Memory allocation failed (Code : 2)\n");
        free(new); // Free the allocated node
        exit(EXIT_FAILURE);
    }
    *(new->pdata)=mydata; // Modify the content at the pointer's adress
    initList(&new->next);
    if (isEmptyList(l)){ // Creat first cell of the list
        initList(&new->prev);
        return new;
    }
    else{ // List not empty, so need to make the connections
        T_List current=l;
        while(!isEmptyList(current->next)){
            current = current->next;
        }
        new->prev = current;
        current->next = new;
    }
    return l;
}

// Add an element at the position N in a list
T_List addAtN(T_List l, int pos, int mydata) {
    T_List new = (T_List)malloc(sizeof(T_List));
    new->pdata = (int*)malloc(sizeof(int));
    *(new->pdata) = mydata;
    T_List current = l;
    int i = 0;
    if (isEmptyList(l)){
        if (pos == 0){
            return addAtHead(l, mydata); // Add to the beginning if pos = 0
        }
        else {
            printf("addAtN: WARNING - Empty list but position > 0 (Adding First)\n");
            return addAtHead(l, mydata); // Return unchanged list
        }
    }
    while (!isEmptyList(current) && pos > i) { // List Traversal
        i++;
        current = current->next;
    }
    if (isEmptyList(current) && pos > i) { // If position is out of bounds
        printf("addAtN: WARNING - Position out of bounds (Adding Last)\n");
        return addAtEnd(l, mydata); // Return unchanged list
    }
    T_List prev;
    if (!isEmptyList(current)){
        prev = current->prev;
    } else {
        prev = l;
    }
    if (pos == 0) { // Add to the beginning
        return addAtHead(l, mydata);
    }
    else {
        if (isEmptyList(current)){ // Add to the end
            return addAtEnd(l, mydata);
        }
        else { // Add at the specified position
            new->next = current;
            new->prev = prev;
            current->prev = new;
            if (!isEmptyList(prev)) {
                prev->next = new;
            }
            return l;
        }
    }
}

T_List delAtHead(T_List l){
    if (isEmptyList(l)){
        printf("delAtHead : ERROR - Empty List (Return NULL)");
        return NULL;
    }
    if (isEmptyList(l->next)){ // If l is the only element in the list
        free(l->pdata);
        free(l);
        return NULL; // List becomes empty after deletion
    }
    else{
        T_List temp = l->next;
        initList(&temp->prev);
        free(l->pdata);
        free(l);
        return temp;
    }
}

T_List delAtEnd(T_List l){
    if (isEmptyList(l)){
        printf("delAtEnd: ERROR - Empty List (Return NULL)\n");
        return NULL;
    }
    if (isEmptyList(l->next)){ // If l is the only element in the list
        free(l->pdata);
        free(l);
        return NULL; // List becomes empty after deletion
    }
    // List traversal
    T_List previous, temp = l;
    initList(&previous);
    while (!isEmptyList(temp->next)){
        previous = temp;
        temp = temp->next;
    }
    if (!isEmptyList(previous)) {
        initList(&previous->next);
    } else {
        // If previous is NULL, it means l is the only element in the list
        free(l->pdata);
        free(l);
        return NULL; // List becomes empty after deletion
    }
    free(temp->pdata);
    free(temp);
    return l;
}

T_List delAtN(T_List l, int pos){
    if (isEmptyList(l)){
        printf("delAtN: ERROR - Empty List (Return NULL)\n");
        return NULL;
    }
    if (pos == 0){// If position is 0, delete the head
        T_List temp = l->next;
        if (!isEmptyList(temp))
            initList(&temp->prev);
        free(l->pdata);
        free(l);
        return temp;
    }
    // List traversal
    T_List current = l;
    int index = 0;
    while (!isEmptyList(current) && index < pos - 1){
        current = current->next;
        index++;
    }
    if (isEmptyList(current) || isEmptyList(current->next)){// If position > len or pos < 0 error && return
        printf("delAtN: ERROR - Position out of bounds (Deleting last)\n");
        return delAtEnd(l);
    }
    T_List temp = current->next;
    current->next = temp->next;
    if (!isEmptyList(temp->next))
        temp->next->prev = current;
    free(temp->pdata);
    free(temp);
    return l;
}



int getNbreCell(T_List l){
    int count = 0;
    while (!isEmptyList(l)){
        count++;
        l = l->next;
    }
    return count;
}

int getSizeBytes(T_List l){
    int totalBytes = 0;
    while (!isEmptyList(l)){
        totalBytes += sizeof(T_List);
        l = l->next;
    }
    return totalBytes;
}

T_List creatNewListFromFusion(T_List l1, T_List l2){
    T_List fusedList;// Initialize the new list
    initList(&fusedList);
    while (!isEmptyList(l1)){
        fusedList = addAtEnd(fusedList, *(l1->pdata));
        l1 = l1->next;
    }
    while (!isEmptyList(l2)){
        fusedList = addAtEnd(fusedList, *(l2->pdata));
        l2 = l2->next;
    }
    return fusedList;
}

T_List addBehind(T_List first, T_List last){
    if (isEmptyList(first)){
        if (isEmptyList(last)){
            printf("WARNING - addBehind : adding two NULL lists");
        }
        return last;
    }
    T_List temp = first;
    while (!isEmptyList(temp->next)){
        temp = temp->next;
    }
    temp->next = last;
    if (!isEmptyList(last)){
        last->prev = temp;
    }
    return first;
}

T_List findCell(T_List l, int data){
    while (!isEmptyList(l)){
        if (*(l->pdata) == data){
            return l;
        }
        l = l->next;
    }
    return NULL;
}

int getOccurences(T_List l, int data){
    int count = 0;
    while (!isEmptyList(l)){
        if (*(l->pdata) == data){
            count++;
        }
        l = l->next;
    }
    return count;
}

void displayListV2(T_List l){
    T_List current = l;
    printf("[");
    while(!isEmptyList(current)){
        printf("%d",*(current->pdata));
        if(!isEmptyList(current->next)){
            printf(";");
        }
        current = getptrNextCell(current);
    }
    printf("]\n");
}

// Part 2

void selectionSort(int *tab, int length){
    int current, smaller, j, temp;
    for (current = 0; current < length - 1; current++){
        smaller = current;
        for (j = current; j < length; j++)
            if (tab[j] < tab[smaller])
                smaller = j;
        temp = tab[current];
        tab[current] = tab[smaller];
        tab[smaller] = temp;
    }
}

T_List createRandomList(int n){
    T_List newList;
    initList(&newList);
    int randomValue = rand()%100;
    srand(time(NULL)); // Seed the random number generator
    newList = (T_List)malloc(sizeof(T_List));
    newList = addAtEnd(newList, randomValue);
    newList->pdata = (int*)malloc(sizeof(int));
    if (newList->pdata == NULL) {
        printf("ERROR - createRandomList : Memory allocation failed\n");
        free(newList);
        exit(EXIT_FAILURE);
    }
    *(newList->pdata) = randomValue;
    initList(&newList->next);
    initList(&newList->prev);
    for (int i = 0; i < n; i++){
        randomValue = rand()%100;
        newList = addAtEnd(newList, randomValue);
    }
    return newList;
}

int* listToArray(T_List l, int *size) {
    int listSize = getNbreCell(l);
    if (listSize == 0) {
        *size = 0;
        return NULL;
    }
    int *arr = (int*)malloc(listSize * sizeof(int));
    if (arr == NULL) {
        printf("ERROR - listToArray : Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    int index = 0;
    while (!isEmptyList(l)) {
        arr[index] = *(l->pdata);
        l = l->next;
        index++;
    }
    *size = listSize;
    return arr;
}

int* listToArrayWithMemoryFree(T_List *originalList, int *size){
    int listSize = getNbreCell(*originalList);
    if (listSize == 0){
        *size = 0;
        return NULL;
    }
    int *arr = (int*)malloc(listSize * sizeof(int));
    if (arr == NULL){
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    int index = 0;
    T_List current = *originalList;
    while (!isEmptyList(current)){
        arr[index] = *(current->pdata);
        T_List temp = current;
        current = current->next;
        free(temp->pdata);
        free(temp);
        index++;
    }
    *size = listSize;
    *originalList = NULL;
    return arr;
}


//
// Created by cejuba on 2/20/2024.
//


