/************************************************************************************
 * @file: queue.h
 * @author: Fang XS.
 * @version: v1.0
 * @date: Create on 2022-10-14 , Modified on xx xx-xx-xx
 * @brief: queue.c primer plus.
 ***********************************************************************************/

/* Define to prevent recursive inclusion ------------------------------------------*/
#ifndef QUEUE_H
#define QUEUE_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes -----------------------------------------------------------------------*/
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

/* Exported macro -----------------------------------------------------------------*/
/* Exported types -----------------------------------------------------------------*/
/**< Item >**/
typedef struct ItemOfQueue{
    int data;
}Item;

/**< node >**/
typedef struct NodeOfQueue{
    Item item;
    struct NodeOfQueue * next;
}Node;

/**< queue >**/
typedef struct queue{
    Node * front;
    Node * rear;
    int items;
}Queue;

enum Global_CONST_INTEGER{
    MAXQUEUE = 10
};
/* Exported functions -------------------------------------------------------------*/
void InitQueue(Queue * pq);

bool QueueIsFull(const Queue * pq);

bool QueueIsEmpty(const Queue * pq);

uint32_t QueueItemCount(const Queue * pq);

bool DeQueue(Queue * pq, Item * pItem);

bool EnQueue(Queue * pq, Item item);

void EmptyTheQueue(Queue * pq);

#ifdef __cplusplus
}
#endif

#endif /* QUEUE_H */

/*********************************** END OF FILE ***********************************/
