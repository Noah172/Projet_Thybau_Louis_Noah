#ifndef LIST_H
#define LIST_H
#include "types.h"

//-------------------------------------------------------------------------------
//
//                   LIST CLASSIQUE
//
//-------------------------------------------------------------------------------

void initDynamicList(DynamicList *list);

void add(DynamicList *list, void *data, DataType type);

int get_int(DynamicList *list, int index);

char *get_char(DynamicList *list, int index);

void removeByIndex(DynamicList *list, int index);

void printDynamicList(DynamicList *list);

void freeDynamicList(DynamicList *list);

//-------------------------------------------------------------------------------
//
//                   LIST CIRCULAIRE
//
//-------------------------------------------------------------------------------

void initList(CircularList *list);

void addHead(CircularList *list, void *data, DataType type);

void addTail(CircularList *list, void *data, DataType type);

int gett_int(CircularList *list, int index);

char *gett_char(CircularList *list, int index);

void removeHead(CircularList *list);

void removeTail(CircularList *list);

void printList(CircularList *list);

void freeList(CircularList *list);

#endif // LIST_H
