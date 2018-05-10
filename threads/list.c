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

typedef struct node_t node_t;

typedef node_t * node_handle;

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

struct list_t {
	unsigned int count;
	node_handle head;
	//one lock per list
};

void List_Init(list_handle list)
{
	list = (list_handle)malloc(sizeof(*list));
	list->head = NULL;
	list->count = 0;
}

void List_Insert(list_handle list, void * element, unsigned int key)
{
	if (list->head) {
		node_handle new = create_node(key, element);
		new->next = list->head;
		list->head->previous = new;
		list->head = new;
	}
	else { //list->head == NULL
		list->head = create_node(key, element);
	}
}

void List_Delete(list_handle list, unsigned int key)
{
	node_handle node = list->head;
	while (node != NULL) {
		node_handle next = node->next;
		
		if (node->key == key) { //key matches, delete
			if (node == list->head) { //have to delete the head
				destroy_node(node);
				next->previous = NULL;
				list->head = next;
				(list->count)--;
				return;
			}
			else if (next == NULL) { //have to delete the tail
				node->previous->next = NULL;
				destroy_node(node);
				(list->count)--;
				return;
			}
			else { //some node in the middle
				node_handle previous = node->previous;
				previous->next = next;
				next->previous = previous;
				destroy_node(node);
				(list->count)--;
				return;
			}
		}
		
		node = next;
	}
}

void * List_Lookup(list_handle list, unsigned int key)
{
	node_handle node = list->head;
	while (node != NULL) {
		if (node->key == key) {
			return node->value;
		}
	}
	return NULL;
}



