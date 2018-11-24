#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include <stdlib.h>
typedef struct _node {void * data; struct _node * next;} node;

node * addNode(void * data, node * head);

void * removeNode(node ** headPtr);

#endif