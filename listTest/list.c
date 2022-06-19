#include "list.h"
#include <stdlib.h>
#include <stdio.h>

node * createList()
{
  return NULL;
}

node *createNode(int v) {
  node *n = malloc(sizeof(node));
  if (n) {
    n->var = v;
    n->next = NULL;
  } else {
    fprintf(stderr, "Node can't be create\n");
    exit(EXIT_FAILURE);
  }
  return n;
}

void insertHead(node **head, node *newNode) {
  node *lastHead = *head;
  *head = newNode;
  newNode->next = lastHead;
}

void tail(node **head) {
  node *supr = *head;
  *head = (*head)->next;
  free(supr);
}

void printList(node *head) {
  printf("[LIST]\n");
  while (head) {
    printf("|%d|->", head->var);
    head = head->next;
  }
  printf("NULL\n");
}

void freeList(node **n) {
  node *last;
  while (*n) {
    last = *n;
    *n = (*n)->next;
    free(last);
  }
}

int lengthList(node *head) {
  int i = 0;
  while (head && ++i)
    head = head->next;

  return i;
}

void insertAtList(node **head, node *n, int index) {
  node *next;
  node *curr = *head;
  if (!index) {
    insertHead(head, n);
  } else {
    while (head != NULL && index-- > 0)
      curr = curr->next;

    if (head) {
      next = curr->next;
      curr->next = n;
      n->next = next;
    }
  }
}

void removeAtList(node **head, int index) {
  node *supr;
  node *curr = *head;
  if (!index) {
    tail(head);
  } else {
    while (curr && --index) {
      curr = curr->next;
    }

    if (curr && (supr = curr->next)) {
      curr->next = supr->next;
      free(supr);
    }
  }
}
int main(void) {
  node *list = createList();
  for (int i = 0; i < 10; i++) {
    insertHead(&list, createNode(i));
  }
  printList(list);
  printf("longueur : %d\n", lengthList(list));
  printf("insertion en 0:\n");
  insertAtList(&list, createNode(10), 0);
  printList(list);
  printf("insertion en 1:\n");
  insertAtList(&list, createNode(33), 1);
  printList(list);
  printf("insertion en fin:\n");
  insertAtList(&list, createNode(22), lengthList(list) - 1);
  printList(list);
  printf("suppression en 0:\n");
  removeAtList(&list, 0);
  printList(list);
  printf("suppression en fin:\n");
  removeAtList(&list, lengthList(list) - 1);
  printList(list);
  printf("suppression:\n");
  freeList(&list);
  printList(list);
  return 0;
}
