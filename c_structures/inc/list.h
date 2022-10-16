/************************************************************************************
 * @file: list.h
 * @author: Fang XS.
 * @version: v1.0
 * @date: Create on 2022-10-14 , Modified on xx xx-xx-xx
 * @brief: a simple link-list. c primer plus.
 ***********************************************************************************/

/* Define to prevent recursive inclusion ------------------------------------------*/
#ifndef LIST_H
#define LIST_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes -----------------------------------------------------------------------*/
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>

/* Exported macro -----------------------------------------------------------------*/
/* Exported types -----------------------------------------------------------------*/
/**< item >**/
typedef struct ItemOfList{
    int a;
}Item;

/**< node >**/
typedef struct NodeOfList{
    Item item;
    struct NodeOfList * next;
}Node;

/**< list >**/
typedef struct list{
    Node * Head;
}List;

/* Exported functions -------------------------------------------------------------*/
void InitList(List * pList);

bool ListIsEmpty(const List * pList);

bool ListIsFull(const List * pList);

uint32_t ListItemCount(const List * pList);

bool AddItem(List * pList, Item item);

bool DelItem(List * pList, Item item);

/**
 * @brief del list and free the memory.
 * */
void EmptyTheList(List * pList);

/**
 * @brief pFun is acting on the nodes of list.
 * */
void Traverse(List * pList, void (*pFun)(Item item));


#ifdef __cplusplus
}
#endif

#endif /* LIST_H */

/*********************************** END OF FILE ***********************************/