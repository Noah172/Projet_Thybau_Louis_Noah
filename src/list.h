#ifndef LIST_H
#define LIST_H
#include "types.h"

void initDynamicList(DynamicList *list);

void add(DynamicList *list, int data);

void removeByIndex(DynamicList *list, int index);

void printDynamicList(DynamicList *list);

void freeDynamicList(DynamicList *list);



void initList(CircularList *list);

void addHead(CircularList *list, int data);

void addTail(CircularList *list, int data);

void removeHead(CircularList *list);

void removeTail(CircularList *list);

void printList(CircularList *list);

void freeList(CircularList *list);

#endif // LIST_H
