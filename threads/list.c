//
//  list.c
//  threads
//
//  Created by Adam on 5/9/18.
//  Copyright © 2018 Adam. All rights reserved.
//

#include "list.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#ifdef PTHREADS

#include <pthread.h>

#endif

struct node_t {
	unsigned int key;
	void * value;
	node_handle next;
	node_handle previous;
};

node_handle create_node(unsigned int key, void * element)
{
	node_handle new = (node_handle)malloc(sizeof(*new));
	new->key = key;
	new->value = element;
	new->next = NULL;
	new->previous = NULL;
	return new;
}

void destroy_node(node_handle node)
{
	free(node);
}

void List_Init(list_handle list)
{
	list->head = NULL;
	list->count = 0;
	list->spinlock = (spinlock_handle)malloc(sizeof(spinlock_t));
#ifdef PTHREADS
	
	pthread_mutex_init(&list->spinlock->lock, NULL);
	
#endif
}

void List_Insert(list_handle list, void * element, unsigned int key)
{
	spinlock_acquire(list->spinlock);
	if (list->head) {
		node_handle new = create_node(key, element);
		new->next = list->head;
		list->head->previous = new;
		list->head = new;
		(list->count)++;
	}
	else { //list->head == NULL, list is empty
		assert(list->count == 0);
		list->head = create_node(key, element);
		(list->count)++;
	}
	spinlock_release(list->spinlock);
}

void List_Delete(list_handle list, unsigned int key)
{
	spinlock_acquire(list->spinlock);
	node_handle node = list->head;
	while (node != NULL) {
		node_handle next = node->next;
		
		if (node->key == key) { //key matches, delete
			if (node == list->head) { //have to delete the head
				if (next) {
					next->previous = NULL;
				}
				destroy_node(node);
				list->head = next;
				(list->count)--;
				spinlock_release(list->spinlock);
				return;
			}
			else if (next == NULL) { //have to delete the tail
				node->previous->next = NULL;
				destroy_node(node);
				(list->count)--;
				spinlock_release(list->spinlock);
				return;
			}
			else { //some node in the middle
				node_handle previous = node->previous;
				previous->next = next;
				next->previous = previous;
				destroy_node(node);
				(list->count)--;
				spinlock_release(list->spinlock);
				return;
			}
		}
		
		node = next;
	}
	spinlock_release(list->spinlock);
}

void * List_Lookup(list_handle list, unsigned int key)
{
	node_handle node = list->head;
	while (node != NULL) {
		if (node->key == key) {
			return node->value;
		}
		node = node->next;
	}
	return NULL;
}



