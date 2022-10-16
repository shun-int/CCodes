/************************************************************************************
 * @file: queue.c
 * @author: Fang XS.
 * @version: v1.0
 * @date: Create on 2022-10-14 , Modified on xx xx-xx-xx
 ***********************************************************************************/

/* Includes -----------------------------------------------------------------------*/
#include "queue.h"

/* global variables ---------------------------------------------------------------*/

/* functions implementation ********************************************************/
static void CopyToNode(Node * pn, Item item){
    pn->item = item;
}

static void CopyToItem(Node * pn, Item *pi){
    *pi = pn->item;
}

void InitQueue(Queue * pq) {
    pq->front = NULL;
    pq->rear  = NULL;
    pq->items = 0U;
}

bool QueueIsFull(const Queue * pq) {
    return (pq->items == MAXQUEUE);
}

bool QueueIsEmpty(const Queue * pq) {
    return (pq->items == 0U);
}

uint32_t QueueItemCount(const Queue * pq) {
    return pq->items;
}

bool EnQueue(Queue * pq, Item item) {
    /* bug: did not check [MAXQUEUE] */
    Node * pNew = (Node*)malloc(sizeof(Node));
    if(pNew == NULL){
        return false;
    }
    CopyToNode(pNew, item);
    pNew->next = NULL;
    if(QueueIsEmpty(pq)){
        pq->front = pNew;
    } else {
        pq->rear->next = pNew;
    }
    pq->rear = pNew;
    pq->items ++;
    return true;
}

bool DeQueue(Queue * pq, Item * pItem) {
    Node * pt;
    if(QueueIsEmpty(pq)){
        return false;
    }
    if(pItem == NULL){
        /* NULL item to do nothing */
    } else {
        CopyToItem(pq->front, pItem);
    }
    pt = pq->front;
    pq->front = pq->front->next;
    free(pt);
    pq->items --;
    if(pq->items == 0U){
        pq->rear = NULL;
    }
    return true;
}

void EmptyTheQueue(Queue * pq) {
    Item dummy;
    while(!QueueIsEmpty(pq)){
        DeQueue(pq, &dummy);
    }
    InitQueue(pq);
}


/* module test */
//#include <stdio.h>
//int main() {
//    Queue queue;
//    Item item={
//            .data = 3
//    };
//    Item item1={
//            .data = 5
//    };
//
//    Item itemCopy;
//    bool isYes;
//    printf("Init queue...\n");
//    InitQueue(&queue);
//    printf("is empty: %s\n", QueueIsEmpty(&queue)?"yes":"no");
//
//    printf("Enqueue...\n");
//    isYes = EnQueue(&queue,item);
//    printf("Enqueue :%s\n",isYes?"yes":"no");
//    EnQueue(&queue,item);
//    EnQueue(&queue,item);
//    EnQueue(&queue,item);
//    EnQueue(&queue,item);
//    EnQueue(&queue,item);
//    EnQueue(&queue,item);
//    EnQueue(&queue,item);
//    EnQueue(&queue,item);
//    EnQueue(&queue,item);
//    EnQueue(&queue,item);
//
//    printf("count : %d\n",QueueItemCount(&queue));
//    printf("is empty: %s\n", QueueIsEmpty(&queue)?"yes":"no");
//
//    isYes = EnQueue(&queue,item1);
//    printf("Enqueue :%s\n",isYes?"yes":"no");
//    /* bug: [QueueItemCount] >10  is not full */
//    printf("is Full: %s\n", QueueIsFull(&queue)?"yes":"no");
//    printf("count : %d\n",QueueItemCount(&queue));
//
//    isYes = DeQueue(&queue,&itemCopy);
//    printf("Dequeue :%s, data: %d\n",
//           isYes?"yes":"no",itemCopy.data
//    );
//    printf("count : %d\n",QueueItemCount(&queue));
//
//    printf("empty queue...\n");
//    EmptyTheQueue(&queue);
//    printf("count : %d\n",QueueItemCount(&queue));
//
//    return 0;
//}

/*********************************** END OF FILE ***********************************/