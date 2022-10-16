/************************************************************************************
 * @file: list.c
 * @author: Fang XS.
 * @version: v1.0
 * @date: Create on 2022-10-14 , Modified on xx xx-xx-xx
 ***********************************************************************************/

/* Includes -----------------------------------------------------------------------*/
#include "list.h"

/* global variables ---------------------------------------------------------------*/
/* functions implementation ********************************************************/
static void CopyToNode(Node * pNode, Item item){
    pNode->item = item;
}

void InitList(List * pList) {
    pList->Head = NULL;
}

bool ListIsEmpty(const List * pList) {
    if(pList == NULL){
        return true;
    } else {
        if(pList->Head == NULL){
            return true;
        } else {
            return false;
        }
    }
}

bool ListIsFull(const List * pList) {
    (void)pList;
    /*
     * @brief
     * this func just judge is there any node size to malloc.
    */
    Node * pt;
    bool isFull;
    pt = (Node *)malloc(sizeof(Node));
    if(pt == NULL){
        /* cannot [malloc] size anymore */
        isFull = true;
    } else {
        isFull = false;
    }
    free(pt);
    return isFull;
}

uint32_t ListItemCount(const List * pList) {
    uint32_t count = 0;
    Node * pNode = pList->Head;
    while(pNode != NULL){
        count ++;
        pNode = pNode->next;
    }
    return count;
}

bool AddItem(List * pList, Item item) {
    Node * scan = pList->Head;
    Node * pNew = (Node *) malloc(sizeof(Node));
    if(pNew == NULL){
        return false;
    }
    CopyToNode(pNew, item);
    pNew->next = NULL;
    if(scan == NULL){
        pList->Head = pNew;
    } else {
        while(scan->next != NULL){
            scan = scan->next;
        }
        scan->next = pNew;
    }
    return true;
}

bool DelItem(List * pList, Item item){
    Node * p = NULL;
    Node * q = NULL;
    for( q = NULL,p = pList->Head; p; q=p, p = p->next ){
        /* the target node */
        if(p->item.a == item.a){
            if( q ){
                q->next = p->next;
            } else {
                pList->Head = p->next;
            }
            free( p );
            return true;
        }
    }
    return false;
}

void EmptyTheList(List * pList) {
    Node * pSave;
    while(pList->Head != NULL){
        pSave = (pList->Head)->next;
        free(pList->Head);
        pList->Head = pSave;
    }
}

/**
 * @brief pFun is acting on the nodes of list.
 * */
void Traverse(List * pList, void (*pFun)(Item item)) {
    Node * pNode = pList->Head;
    while(pNode != NULL){
        (*pFun)(pNode->item);
        pNode = pNode->next;
    }
}


/* module test */
//#include <stdio.h>
//void print_list(Item item){
//    printf("\t item:%d\n",item.a);
//}
//int main() {
//List test ;
//Item tItem = {
//        .a = 3
//};
//Item yItem = {
//        .a = 5
//};
//
//printf("Init List...\n");
//InitList(&test);
//if(ListIsFull(&test)){
//printf("mem not enough.\n");
//}
//printf("is empty:%s\n",ListIsEmpty(&test)?"yes":"no");
//
//printf("AddItem:%s\n",AddItem(&test, tItem)?"yes":"no");
//printf("total: %d items.\n",ListItemCount(&test));
//
//printf("list is full?:%s\n",ListIsFull(&test)?"yes":"no");
//
//printf("AddItem:%s\n",AddItem(&test, yItem)?"yes":"no");
//
//printf("is empty?:%s\n",ListIsEmpty(&test)?"yes":"no");
//printf("total: %d items.\n",ListItemCount(&test));
//
//printf("print list...\n");
//Traverse(&test, print_list);
//printf("total: %d items.\n",ListItemCount(&test));
//
//printf("DelItem:%s\n",DelItem(&test, yItem)?"yes":"no");
//printf("total: %d items.\n",ListItemCount(&test));
//
//printf("print list...\n");
//Traverse(&test, print_list);
//
//printf("del List...\n");
////    EmptyTheList(&test);
//printf("is empty?:%s\n",ListIsEmpty(&test)?"yes":"no");
//
//
//printf("Init List...\n");
//InitList(&test);
//if(ListIsFull(&test)){
//printf("mem not enough.\n");
//}
//printf("is empty:%s\n",ListIsEmpty(&test)?"yes":"no");
//
//printf("AddItem:%s\n",AddItem(&test, tItem)?"yes":"no");
//printf("total: %d items.\n",ListItemCount(&test));

//    return 0;
//}

/*********************************** END OF FILE ***********************************/
