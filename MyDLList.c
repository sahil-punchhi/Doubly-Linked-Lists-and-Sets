//Name: Sahil Punchhi
//zID: z5204256
// COMP 9024 Assignment 1
// 17 March 2019

//////////////////////////////
//
//  main.c
//  Comp 9024 C
//
//  Created by Sahil Punchhi on 23/2/19.
//  Copyright © 2019 Sahil Punchhi. All rights reserved.
//

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

// all the basic data structures and functions are included in this template
// you can add your own auxiliary functions as you like

// data structures representing DLList

// data type for nodes
typedef struct DLListNode {
    int  value;  // value (int) of this list item
    struct DLListNode *prev;
    // pointer previous node in list
    struct DLListNode *next;
    // pointer to next node in list
} DLListNode;

//data type for doubly linked lists
typedef struct DLList{
    int  size;      // count of items in list
    DLListNode *first; // first node in list
    DLListNode *last;  // last node in list
} DLList;

// create a new DLListNode
DLListNode *newDLListNode(int it)
{
    DLListNode *new;
    new = malloc(sizeof(DLListNode));
    assert(new != NULL);
    new->value = it;
    new->prev = new->next = NULL;
    return new;
}

// create a new empty DLList
DLList *newDLList()
{
    DLList *L;
    
    L = malloc(sizeof (struct DLList));
    assert (L != NULL);
    L->size = 0;
    L->first = NULL;
    L->last = NULL;
    return L;
}

// function which creates a new node at the last
// Time complexity O(n)
void node_atLast(DLListNode *first_node,int val){
    DLListNode *new_node;
    DLListNode *iterator;
    iterator = first_node;
    new_node = newDLListNode(val);
    while(iterator->next!= NULL){
        iterator = iterator->next;
    }
    iterator->next = new_node;
    new_node->prev = iterator;
}

// function which creates a new node at the last if the node is distinct from all other nodes
// Time complexity O(n)
void addNode_atLast(DLListNode *first_node,int val){
    DLListNode *iterator;
    DLListNode *new_node;
    iterator = first_node;
    if (iterator->value == val){
        return;
    }
    new_node=newDLListNode(val);
    while(iterator->next!=NULL){
        
        if (iterator->value == val){
            return;  //function returns if value is not distinct
        }
        if (iterator->next->value == val){
            return; //function returns if value is not distinct
        }
        
        iterator = iterator->next;
    }
    iterator->next = new_node;
    new_node->prev = iterator;
    
    return;
}

// function to create a doubly linked list by- scanning all elements from a file/ inputting elements manually
// Time complexity O(n^2)
DLList *CreateDLListFromFileDlist(const char *filename)
{
    int elements[9999]; //assuming 9999 elements in array
    int i=0, j=1;
    
    //taking elements manually
    if (strcmp(filename, "stdin") == 0){
        char *num = calloc(100,sizeof(char*));
        while (*fgets(num, 12, stdin) != '\n'){
            elements[i++] = atoi(num); //atoi converts string to integer
    }
        free(num);
        fflush(stdin);
        
    }
    
    //taking elements from input file
    else {
        FILE *fptr;
        fptr=fopen(filename,"r"); //values taken from an input file
        
        if(fptr == NULL){
            exit(0);
        }
        fscanf(fptr,"%d",&elements[i]); //values scanned from the file
        while(!feof(fptr)){
            i++;
            fscanf(fptr,"%d",&elements[i]);
        }
        fclose(fptr); //file closed
        
        if (i == 0) { // returning null if there is no element in the file
            return NULL;
        }
    }
    


        DLListNode *first_node; //creating first node of doubly linked list
        DLList *linked_list; //creating doubly linked list
        linked_list = newDLList();
        

        
        //size of linked list
        first_node = newDLListNode(elements[0]);
        linked_list->size += 1;
        while(j<i){
            node_atLast(first_node,elements[j]);
            linked_list->size += 1;
            j++;
        }

        linked_list->first = first_node;
        while(first_node->next != NULL){
            first_node = first_node->next;
        }
        linked_list->last = first_node; //declaring last element of linked list
//        printf("------%d\n", linked_list->size);
        return linked_list;
    
//    return NULL;
}

// printing all the elements of a linked list from head to tail
// Time complexity O(n)
void printDLList(DLList *u )
{
    if(u == NULL){
     return;
     }
    DLListNode *point = u->first;
    while(point != NULL){
        printf("%d\n",point->value);
        point = point->next;
    }
    
}

// printing all the elements of a linked list from tail to head
// Time complexity O(n)
void printDLList_reversed(DLList *u )
{    if(u == NULL){
        return;
        }
    DLListNode *point = u->last;
    while(point != NULL){
        printf("%d\n",point->value);
        point = point->prev;
    }
    
}

// cloning a linked list
// Time complexity O(n^2)
DLList *cloneList(DLList *u)
{     if(u == NULL){ // if no elements then returns null
    return NULL;
    }
    DLListNode *first_node;
    DLListNode *point = u->first; // first element of linked list
    DLList *clone_list;
    clone_list = newDLList(); //creating new linked list
    first_node=newDLListNode(u->first->value);
    
    clone_list->first = first_node;
    
    while(point->next != NULL){
        point = point->next;
        node_atLast(first_node, point->value); //adding nodes to the new linked list
    }
    

    clone_list->last=point; //declaring last element of a new linked list
    return clone_list;
}

// function to find union of elements in 2 different linked lists
// Time complexity O(n^2)
DLList *setUnion(DLList *u, DLList *v)
{
    if(u == NULL){ // if first linked list is null, returns second linked list
        return v;
    }
    if(v == NULL){ // if second linked list is null, returns first linked list
        return u;
    }
    DLListNode *first_node_u;
    DLListNode *point_u = u->first;
    DLListNode *point_v = v->first;
    DLList *union_list; //creating a new linked list
    union_list = newDLList();
    first_node_u=newDLListNode(u->first->value);
    
    union_list->first = first_node_u; //first element of the new linked list
    
    while(point_u->next != NULL){
        point_u = point_u->next;
        addNode_atLast(first_node_u, point_u->value); //adds distinct element at the last in new linked list from u
        
    }
    
    while(point_v != NULL){
        
        addNode_atLast(first_node_u, point_v->value); //adds distinct element at the last in new linked list from v
        point_v = point_v->next;
        
    }
    union_list->first=first_node_u;
    while(first_node_u->next!=NULL){
        first_node_u=first_node_u->next;
    }
    union_list->last=first_node_u; //declaring last element of a linked list
    
    return union_list;
    }

// function to find intersection of elements in 2 different linked lists
// Time complexity O(n^3)
DLList *setIntersection(DLList *u, DLList *v)
{
    if(u == NULL || v == NULL){ // if either of u or v is null, returns null
        return NULL;
    }
    DLList *intersection_list; //creating a new linked list
    intersection_list = newDLList();
    

    DLListNode *first_node_intersection = NULL;
    DLListNode *point_u = u->first;
    DLListNode *point_v = v->first;
    
    while(point_u != NULL){ //iterating through all elements of u
        point_v = v->first;
        while(point_v != NULL){ //iterating through all elements of v
            if(point_u->value == point_v->value){
                if (first_node_intersection == NULL) {
                    first_node_intersection = newDLListNode(point_u->value);
                }
                addNode_atLast(first_node_intersection, point_u->value);
                //adds distinct element at the last in new linked list
                
            }
                point_v = point_v->next;
            
            }
        
        point_u = point_u->next;
    }
    intersection_list->first = first_node_intersection;//declaring first element of linked list
    while(first_node_intersection->next != NULL){
        first_node_intersection = first_node_intersection->next;
    }
    intersection_list->last = first_node_intersection;//declaring last element of linked list
    
    return intersection_list;
}

// Time complexity: O(n)
void freeDLList(DLList *u)
{   if(u == NULL){ // if linked list is null, return
        return;
    }
    DLListNode *del; //create new Node del and temp
    DLListNode *temp = u->first;
    while (temp != NULL) {
        del = temp;
        temp = temp->next;
        free(del); //free the node
    }
    
    free(temp); //free temp
    free(u);
}

//path /Users/sahilpunchhi/Desktop/COMP\ 9024\ DSA/C\ Repository/Comp\ 9024\ C/Comp\ 9024\ C/
int main()
{
    DLList *list1, *list2, *list3, *list4;
    
    list1=CreateDLListFromFileDlist("File1.txt");
    printDLList(list1);
    
    list2=CreateDLListFromFileDlist("File2.txt");
    printDLList(list2);
    
    list3=setUnion(list1, list2);
    printDLList(list3);
    
    list4=setIntersection(list1, list2);
    printDLList(list4);
    
    freeDLList(list1);
    freeDLList(list2);
    freeDLList(list3);
    freeDLList(list4);
    
    printf("please type all the integers of list1\n");
    list1=CreateDLListFromFileDlist("stdin");
    
    printf("please type all the integers of list2\n");
    list2=CreateDLListFromFileDlist("stdin");
    
    list3=cloneList(list1);
    printDLList(list3);
    list4=cloneList(list2);
    printDLList(list4);
    
    freeDLList(list1);
    freeDLList(list2);
    freeDLList(list3);
    freeDLList(list4);
    
    return 0;
}

