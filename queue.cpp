#include <iostream>
#include <cstdlib>
#include <cstring>
#include "queue.h"
#include <mutex>

Queue* init(void) {
	Queue* q = (Queue*)malloc(sizeof(Queue));
	if (!q) return NULL;
	new (&q->mtx) std::mutex();

	q->head = (Node*)malloc(sizeof(Node));
	q->tail = (Node*)malloc(sizeof(Node));
	if (!q->head || !q->tail) {
		free(q->head);
		free(q->tail);
		q->mtx.~mutex();
		free(q);
		return NULL;
	}

	q->head->next = q->tail;
	q->tail->next = NULL;

	return q;

}


void release(Queue* queue) {
	if (!queue) return;
	Node* prev = queue->head->next;
	Node* Next_Node;

	while (prev != queue->tail) {
		Next_Node = prev->next;
		free(prev->item.value);
		free(prev);
		prev = Next_Node;
	}

	free(queue->tail);
	free(queue->head);
	queue->mtx.~mutex();
	free(queue);
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
	std::lock_guard<std::mutex> Lock(queue->mtx);

	Node* Previous_Node = queue->head;
	Node* Current_Node = Previous_Node->next;
	while (Current_Node != queue->tail) {
		if (Current_Node->item.key == item.key) {
			free(Current_Node->item.value);
			Current_Node->item.value_size = item.value_size;
			Current_Node->item.value = malloc(item.value_size);
			memcpy(Current_Node->item.value, item.value, item.value_size);

			reply.success = true;
			reply.item = Current_Node->item;
			return reply;
		}
		Previous_Node = Current_Node;
		Current_Node = Current_Node->next;
	}

	Node* New_Node = (Node*)malloc(sizeof(Node));
	New_Node->item.key = item.key;
	New_Node->item.value_size = item.value_size;
	New_Node->item.value = malloc(item.value_size);
	memcpy(New_Node->item.value, item.value, item.value_size);


	Previous_Node = queue->head;
	Current_Node = Previous_Node->next;
	while (Current_Node != queue->tail) {
		if (Current_Node->item.key <= item.key) {
			break;
		}
		Previous_Node = Current_Node;
		Current_Node = Current_Node->next;
	}

	Previous_Node->next = New_Node;
	New_Node->next = Current_Node;

	reply.success = true;
	reply.item = New_Node->item;
	return reply;
}

Reply dequeue(Queue* queue) {
	Reply reply = { false, {0, nullptr, 0} };
	if (!queue) return reply;
	std::lock_guard<std::mutex> Lock(queue->mtx);

	if (queue->head->next == queue->tail) return reply;

	Node* target = queue->head->next;
	queue->head->next = target->next;

	reply.item.key = target->item.key;
	reply.item.value_size = target->item.value_size;
	reply.item.value = malloc(reply.item.value_size);
	memcpy(reply.item.value, target->item.value, reply.item.value_size);

	reply.success = true;
	free(target->item.value);
	free(target);
	return reply;
}


Queue* range(Queue* queue, Key start, Key end) {
	if (!queue) return NULL;
	std::lock_guard<std::mutex> Lock(queue->mtx);

	Queue* Copy_Queue = init();
	Node* cur = queue->head->next;
	Item copy;

	if (!Copy_Queue) return NULL;
	while (cur != queue->tail) {
		if (cur->item.key >= start && cur->item.key <= end) {
			copy = cur->item;
			enqueue(Copy_Queue, copy);
		}
		cur = cur->next;
	}

	return Copy_Queue;
}
