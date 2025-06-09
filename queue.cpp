#include <iostream>
#include <cstdlib>
#include <cstring>
#include "queue.h"


Queue* init(void) {
	Queue* q = (Queue*)malloc(sizeof(Queue));
	if (!q) return NULL;

	q->head = (Node*)malloc(sizeof(Node));
	q->tail = (Node*)malloc(sizeof(Node));
	if (!q->head || !q->tail) {
		free(q->head);
		free(q->tail);
		free(q);
		return NULL;
	}

	q->head->next = q->tail;
	q->tail->next = NULL;

	return q;

}


void release(Queue* queue) {
	return;
}


Node* nalloc(Item item) {
	// Node 생성, item으로 초기화
	return NULL;
}


void nfree(Node* node) {
	return;
}


Node* nclone(Node* node) {
	return NULL;
}


Reply enqueue(Queue* queue, Item item) {
	Reply reply = { false, {0, nullptr, 0} };
	if (!queue) return reply;

	Node* New_Node = (Node*)malloc(sizeof(Node));
	New_Node->item.key = item.key;
	New_Node->item.value_size = item.value_size;
	New_Node->item.value = malloc(item.value_size);
	memcpy(New_Node->item.value, item.value, item.value_size);


	if (queue->head->next == queue->tail) {
		queue->head->next = New_Node;
		New_Node->next = queue->tail;
	}

	else { 
		New_Node->next = queue->head->next;
		queue->head->next = New_Node;
	}


	reply.success = true;
	reply.item = New_Node->item;
	return reply;
}

Reply dequeue(Queue* queue) {
	Reply reply = { false, NULL };
	return reply;
}

Queue* range(Queue* queue, Key start, Key end) {
	return NULL;
}
