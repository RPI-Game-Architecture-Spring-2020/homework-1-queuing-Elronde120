/*
** RPI Game Architecture Engine
**
** Portions adapted from:
** Viper Engine - Copyright (C) 2016 Velan Studios - All Rights Reserved
**
** This file is distributed under the MIT License. See LICENSE.txt.
*/

#include "ga_queue.h"

ga_queue::ga_queue(int node_count)
{
	// TODO:
	// Initialize the queue.
	// For extra credit, preallocate 'node_count' elements (instead of
	// allocating on push).
	// See https://www.research.ibm.com/people/m/michael/podc-1996.pdf
	Node* node = new Node; //randomly allocate new node because PDF said so?
	node->next = NULL;
	Tail = Head = node;
	count = 0;
}

ga_queue::~ga_queue()
{
	// TODO:
	// Free any resources held by the queue.
	// See https://www.research.ibm.com/people/m/michael/podc-1996.pdf
	Node* node = Head;
	while (node->next != NULL) {//free the queue
		Node* prevNode = node;
		node = node->next;
		free(prevNode);
	}

	if (node != NULL) {//double check that we deleted ourselves
		free(node);
	}
	count = 0;
}

void ga_queue::push(void* data)
{
	// TODO:
	// Push 'data' onto the queue in a thread-safe manner.
	// If you preallocated 'node_count' elements, and if the queue is full when
	// this function is called, you must block until another thread pops an
	// element off the queue.
	// See https://www.research.ibm.com/people/m/michael/podc-1996.pdf
	Node* node = new Node;
	node->data = data;
	node->next = NULL;
	T_LOCK.lock();
	Tail->next = node;
	Tail = Tail->next;
	count++;
	T_LOCK.unlock();
}

bool ga_queue::pop(void** data)
{
	// TODO:
	// Pop one element off the queue in a thread-safe manner and place it in
	// the memory pointed to by 'data'.
	// If the queue is empty when this function is called, return false.
	// Otherwise return true.
	// See https://www.research.ibm.com/people/m/michael/podc-1996.pdf
	H_Lock.lock();
	Node* node = Head;
	Node* newHead = node->next;
	if (newHead == NULL) {
		H_Lock.unlock();
		return false;
	}
	*data = newHead->data;
	Head = newHead;
	H_Lock.unlock();
	free(node);
	return true;
}

int ga_queue::get_count() const
{
	// TODO:
	// Get the number of elements currently in the queue.
	return count;
}
