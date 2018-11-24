#include "linkedList.h"

node * addNode(void * data, node * head){
	node * newNode = malloc(sizeof(node));
	newNode->data = data;
	newNode->next = head;
	return newNode;
}

void * removeNode(node ** headPtr){
	void * toRet = (*headPtr)->data;
	*headPtr = (*headPtr)->next;
	return toRet;
}
