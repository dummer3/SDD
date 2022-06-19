#ifndef __LIST_H__
#define __LIST_H__


/**
 * struct node containing our value and the next node
 * (var = value ::: next = next node)
 */
typedef struct node
{
  int var;
  struct node * next;
} node;

node * createList();
node * createNode(int);
void insertHead(node ** head, node * newNode);
int lengthList(node * head);
void insertAtList(node **head, node *n, int index);
void removeAtList(node **head, int index);
void freeList(node **);
void printList(node * head);

#endif


