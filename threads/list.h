//
//  list.h
//  threads
//
//  Created by Adam on 5/9/18.
//  Copyright © 2018 Adam. All rights reserved.
//

#ifndef list_h
#define list_h

#include "spin.h"

typedef struct node_t node_t;
typedef node_t * node_handle;

struct list_t {
	unsigned int count;
	node_handle head;
	spinlock_handle spinlock;
};
typedef struct list_t list_t;
typedef list_t * list_handle;

void List_Init(list_handle list);
void List_Insert(list_handle list, void * element, unsigned int key);
void List_Delete(list_handle list, unsigned int key);
void * List_Lookup(list_handle list, unsigned int key);

#endif
