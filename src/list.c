/** \file list.c
 *  \brief Implémentation des fonctions pour les listes dynamiques et circulaires.
 */
#include "list.h"
#include <stdio.h>
#include <stdlib.h>

//-------------------------------------------------------------------------------
//
//                   LIST CLASSIQUE
//
//-------------------------------------------------------------------------------

/** \fn void initDynamicList(DynamicList *list)
 *  \brief Initialise une liste dynamique.
 *
 *  \param list Pointeur vers la liste dynamique à initialiser.
 */
void initDynamicList(DynamicList *list) {
  list->head = NULL;
  list->size = 0;
}

/** \fn void add(DynamicList *list, void *data, DataType type)
 *  \brief Ajoute un élément à la fin de la liste dynamique.
 *
 *  \param list Pointeur vers la liste dynamique.
 *  \param data Pointeur vers les données à ajouter.
 *  \param type Type de données (INT_TYPE ou CHAR_TYPE).
 */
void add(DynamicList *list, void *data, DataType type) {
  Node *newNode = malloc(sizeof(Node));
  if (newNode == NULL) {
    fprintf(stderr, "Erreur d'allocation mémoire.\n");
    exit(EXIT_FAILURE);
  }

  if (type == INT_TYPE) {

    newNode->data_int = *(int *)data;
  } else
    newNode->data_str = (char *)data;
  newNode->next = NULL;
  newNode->type = type;

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

/** \fn int get_int(DynamicList *list, int index)
 *  \brief Récupère la valeur entière à l'index spécifié dans la liste dynamique.
 *
 *  \param list Pointeur vers la liste dynamique.
 *  \param index Indice de l'élément à récupérer.
 *  \return La valeur entière à l'index spécifié.
 */
int get_int(DynamicList *list, int index) {
  if (index >= list->size) {
    fprintf(stderr, "Indice hors de la plage de la liste.\n");
    exit(EXIT_FAILURE);
  }
  Node *current = list->head;
  for (int i = 0; i < index; ++i) {
    current = current->next;
  }
  return current->data_int;
}

/** \fn char *get_char(DynamicList *list, int index)
 *  \brief Récupère la valeur de chaîne de caractères à l'index spécifié dans la liste dynamique.
 *
 *  \param list Pointeur vers la liste dynamique.
 *  \param index Indice de l'élément à récupérer.
 *  \return La valeur de chaîne de caractères à l'index spécifié.
 */
char *get_char(DynamicList *list, int index) {
  if (index >= list->size) {
    fprintf(stderr, "Indice hors de la plage de la liste.\n");
    exit(EXIT_FAILURE);
  }
  Node *current = list->head;
  for (int i = 0; i < index; ++i) {
    current = current->next;
  }
  return current->data_str;
}

/** \fn void set_int(DynamicList *list, int index, int newData)
 *  \brief Modifie la valeur entière à l'index spécifié dans la liste dynamique.
 *
 *  \param list Pointeur vers la liste dynamique.
 *  \param index Indice de l'élément à modifier.
 *  \param newData Nouvelle valeur entière.
 */
void set_int(DynamicList *list, int index, int newData) {
  if (index >= list->size) {
    fprintf(stderr, "Indice hors de la plage de la liste.\n");
    exit(EXIT_FAILURE);
  }
  Node *current = list->head;
  for (int i = 0; i < index; ++i) {
    current = current->next;
  }
  current->data_int = newData;
}

/** \fn void set_char(DynamicList *list, int index, char *newData)
 *  \brief Modifie la valeur de chaîne de caractères à l'index spécifié dans la liste dynamique.
 *
 *  \param list Pointeur vers la liste dynamique.
 *  \param index Indice de l'élément à modifier.
 *  \param newData Nouvelle valeur de chaîne de caractères.
 */
void set_char(DynamicList *list, int index, char *newData) {
  if (index >= list->size) {
    fprintf(stderr, "Indice hors de la plage de la liste.\n");
    exit(EXIT_FAILURE);
  }
  Node *current = list->head;
  for (int i = 0; i < index; ++i) {
    current = current->next;
  }
  current->data_str = newData;
}

/** \fn void removeByIndex(DynamicList *list, int index)
 *  \brief Supprime l'élément à l'index spécifié dans la liste dynamique.
 *
 *  \param list Pointeur vers la liste dynamique.
 *  \param index Indice de l'élément à supprimer.
 */
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

/** \fn void printDynamicList(DynamicList *list)
 *  \brief Affiche les éléments de la liste dynamique.
 *
 *  \param list Pointeur vers la liste dynamique.
 */
void printDynamicList(DynamicList *list) {
  Node *current = list->head;
  while (current != NULL) {
    if (current->type == INT_TYPE)
      printf("%d ", current->data_int);
    else
      printf("%s ", current->data_str);
    current = current->next;
  }
  printf("\n");
}

/** \fn void freeDynamicList(DynamicList *list)
 *  \brief Libère la mémoire allouée à la liste dynamique.
 *
 *  \param list Pointeur vers la liste dynamique.
 */
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

/** \fn void initList(CircularList *list)
 *  \brief Initialise une liste circulaire.
 *
 *  \param list Pointeur vers la liste circulaire à initialiser.
 */
void initList(CircularList *list) {
  list->head = NULL;
  list->tail = NULL;
  list->nb_elem = 0;
}

/** \fn void addHead(CircularList *list, void *data, DataType type)
 *  \brief Ajoute un élément en tête de la liste circulaire.
 *
 *  \param list Pointeur vers la liste circulaire.
 *  \param data Pointeur vers les données à ajouter.
 *  \param type Type de données (INT_TYPE ou CHAR_TYPE).
 */
void addHead(CircularList *list, void *data, DataType type) {
  Node *newNode = malloc(sizeof(Node));
  if (newNode == NULL) {
    fprintf(stderr, "Erreur d'allocation mémoire.\n");
    exit(EXIT_FAILURE);
  }

  if (type == INT_TYPE)
    newNode->data_int = *(int *)data;
  else
    newNode->data_str = (char *)data;
  newNode->type = type;
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

/** \fn void addTail(CircularList *list, void *data, DataType type)
 *  \brief Ajoute un élément en queue de la liste circulaire.
 *
 *  \param list Pointeur vers la liste circulaire.
 *  \param data Pointeur vers les données à ajouter.
 *  \param type Type de données (INT_TYPE ou CHAR_TYPE).
 */
void addTail(CircularList *list, void *data, DataType type) {
  Node *newNode = malloc(sizeof(Node));
  if (newNode == NULL) {
    fprintf(stderr, "Erreur d'allocation mémoire.\n");
    exit(EXIT_FAILURE);
  }

  if (type == INT_TYPE)
    newNode->data_int = *(int *)data;
  else
    newNode->data_str = (char *)data;
  newNode->type = type;
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

/** \fn int gett_int(CircularList *list, int index)
 *  \brief Récupère la valeur entière à l'index spécifié dans la liste circulaire.
 *
 *  \param list Pointeur vers la liste circulaire.
 *  \param index Indice de l'élément à récupérer.
 *  \return La valeur entière à l'index spécifié.
 */
int gett_int(CircularList *list, int index) {
  if (index >= list->nb_elem) {
    fprintf(stderr, "Indice hors de la plage de la liste.\n");
    exit(EXIT_FAILURE);
  }
  Node *current = list->head;
  for (int i = 0; i < index; ++i) {
    current = current->next;
  }
  return current->data_int;
}

/** \fn char *gett_char(CircularList *list, int index)
 *  \brief Récupère la valeur de chaîne de caractères à l'index spécifié dans la liste circulaire.
 *
 *  \param list Pointeur vers la liste circulaire.
 *  \param index Indice de l'élément à récupérer.
 *  \return La valeur de chaîne de caractères à l'index spécifié.
 */
char *gett_char(CircularList *list, int index) {
  if (index >= list->nb_elem) {
    fprintf(stderr, "Indice hors de la plage de la liste.\n");
    exit(EXIT_FAILURE);
  }
  Node *current = list->head;
  for (int i = 0; i < index; ++i) {
    current = current->next;
  }
  return current->data_str;
}

/** \fn void sett_int(CircularList *list, int index, int newData)
 *  \brief Modifie la valeur entière à l'index spécifié dans la liste circulaire.
 *
 *  \param list Pointeur vers la liste circulaire.
 *  \param index Indice de l'élément à modifier.
 *  \param newData Nouvelle valeur entière.
 */
void sett_int(CircularList *list, int index, int newData) {
  if (index >= list->nb_elem) {
    fprintf(stderr, "Indice hors de la plage de la liste.\n");
    exit(EXIT_FAILURE);
  }
  Node *current = list->head;
  for (int i = 0; i < index; ++i) {
    current = current->next;
  }
  current->data_int = newData;
}

/** \fn void sett_char(CircularList *list, int index, char *newData)
 *  \brief Modifie la valeur de chaîne de caractères à l'index spécifié dans la liste circulaire.
 *
 *  \param list Pointeur vers la liste circulaire.
 *  \param index Indice de l'élément à modifier.
 *  \param newData Nouvelle valeur de chaîne de caractères.
 */
void sett_char(CircularList *list, int index, char *newData) {
  if (index >= list->nb_elem) {
    fprintf(stderr, "Indice hors de la plage de la liste.\n");
    exit(EXIT_FAILURE);
  }
  Node *current = list->head;
  for (int i = 0; i < index; ++i) {
    current = current->next;
  }
  current->data_str = newData;
}

/** \fn void removeHead(CircularList *list)
 *  \brief Supprime l'élément en tête de la liste circulaire.
 *
 *  \param list Pointeur vers la liste circulaire.
 */
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

/** \fn removeTail(CircularList *list)
 *  \brief Supprime l'élément en queue de la liste circulaire.
 *
 *  \param list Pointeur vers la liste circulaire.
 */
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

/** \fn printList(CircularList *list)
 *  \brief Imprime les éléments de la liste circulaire.
 *
 *  \param list Pointeur vers la liste circulaire.
 */
void printList(CircularList *list) {
  Node *current = list->head;

  for (int i = 0; i < list->nb_elem; i++) {
    if (current->type == INT_TYPE)
      printf("%d ", current->data_int);
    else
      printf("%s ", current->data_str);
    current = current->next;
  }
  printf("\n");
}

/** \fn freeList(CircularList *list)
 *  \brief Libère la mémoire allouée à la liste circulaire.
 *
 *  \param list Pointeur vers la liste circulaire.
 */
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
