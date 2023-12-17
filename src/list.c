#include "list.h"
#include <stdio.h>
#include <stdlib.h>

//-------------------------------------------------------------------------------
//
//                   LIST CLASSIQUE
//
//-------------------------------------------------------------------------------

void initDynamicList(DynamicList *list) {
  list->head = NULL;
  list->size = 0;
}

void add(DynamicList *list, int data) {
  Node *newNode = malloc(sizeof(Node));
  if (newNode == NULL) {
    fprintf(stderr, "Erreur d'allocation mémoire.\n");
    exit(EXIT_FAILURE);
  }

  newNode->data = data;
  newNode->next = NULL;

  if (list->head == NULL) {
    list->head = newNode;
  } else {
    Node *current = list->head;
    while (current->next != NULL) {
      current = current->next;
    }
    current->next = newNode;
  }

  list->size++;
}

void removeByIndex(DynamicList *list, int index) {
  if (index >= list->size) {
    fprintf(stderr, "Indice hors de la plage de la liste.\n");
    exit(EXIT_FAILURE);
  }

  if (index == 0) {
    Node *temp = list->head;
    list->head = list->head->next;
    free(temp);
  } else {
    Node *current = list->head;
    for (int i = 0; i < index - 1; ++i) {
      current = current->next;
    }

    Node *temp = current->next;
    current->next = temp->next;
    free(temp);
  }

  list->size--;
}

void printDynamicList(DynamicList *list) {
  Node *current = list->head;
  while (current != NULL) {
    printf("%d ", current->data);
    current = current->next;
  }
  printf("\n");
}

void freeDynamicList(DynamicList *list) {
  Node *current = list->head;
  Node *next;
  while (current != NULL) {
    next = current->next;
    free(current);
    current = next;
  }

  list->head = NULL;
  list->size = 0;
}

//-------------------------------------------------------------------------------
//
//                   LIST CIRCULAIRE
//
//-------------------------------------------------------------------------------

// Fonction pour initialiser une liste vide
void initList(CircularList *list) {
  list->head = NULL;
  list->tail = NULL;
  list->nb_elem = 0;
}

// Fonction pour ajouter un élément en tête de la liste
void addHead(CircularList *list, int data) {
  Node *newNode = malloc(sizeof(Node));
  if (newNode == NULL) {
    fprintf(stderr, "Erreur d'allocation mémoire.\n");
    exit(EXIT_FAILURE);
  }

  newNode->data = data;
  newNode->next = list->head;

  if (list->head == NULL) {
    list->tail = newNode;
  }

  list->head = newNode;

  if (list->tail != NULL) {
    list->tail->next = list->head;
  }
  list->nb_elem++;
}

// Fonction pour ajouter un élément en queue de la liste
void addTail(CircularList *list, int data) {
  Node *newNode = malloc(sizeof(Node));
  if (newNode == NULL) {
    fprintf(stderr, "Erreur d'allocation mémoire.\n");
    exit(EXIT_FAILURE);
  }

  newNode->data = data;
  newNode->next = NULL;

  if (list->head == NULL) {
    list->head = newNode;
    list->tail = newNode;
  } else {
    list->tail->next = newNode;
    list->tail = newNode;
  }

  if (list->head != NULL) {
    list->tail->next = list->head;
  }
  list->nb_elem++;
}

// Fonction pour supprimer l'élément en tête de la liste
void removeHead(CircularList *list) {
  if (list->head != NULL) {
    Node *temp = list->head;
    list->head = list->head->next;

    if (list->head == NULL) {
      list->tail = NULL;
    }

    free(temp);

    if (list->tail != NULL) {
      list->tail->next = list->head;
    }
  }
  list->nb_elem--;
}

// Fonction pour supprimer l'élément en queue de la liste
void removeTail(CircularList *list) {
  if (list->head != NULL) {
    Node *temp = list->head;
    Node *prev = NULL;

    while (temp->next != NULL && temp->next != list->head) {
      prev = temp;
      temp = temp->next;
    }

    if (temp == list->head && temp->next == list->head) {
      free(temp);
      list->head = NULL;
      list->tail = NULL;
    } else if (prev != NULL) {
      prev->next = NULL;
      list->tail = prev;
      free(temp);
    }

    if (list->head != NULL) {
      list->tail->next = list->head;
    }
  }
  list->nb_elem--;
}

// Fonction pour imprimer les éléments de la liste
void printList(CircularList *list) {
  Node *current = list->head;

  for (int i = 0; i < list->nb_elem; i++) {
    printf("%d ", current->data);
    current = current->next;
  }
  printf("\n");
}

// Fonction pour libérer la mémoire allouée à la liste
void freeList(CircularList *list) {
  Node *current = list->head;
  Node *next;

  while (current != NULL && current->next != list->head) {
    next = current->next;
    free(current);
    current = next;
  }

  list->head = NULL;
  list->tail = NULL;
}
