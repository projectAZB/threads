//
//  hash.c
//  threads
//
//  Created by Adam on 5/9/18.
//  Copyright © 2018 Adam. All rights reserved.
//

#include "hash.h"

#include <stdlib.h>

#include "list.h"

struct hash_t {
	int num_buckets;
	list_handle * buckets;
};

void Hash_Init(hash_handle hash, int buckets)
{
	hash = (hash_handle)malloc(sizeof(*hash));
	hash->num_buckets = buckets;
	hash->buckets = (list_handle *)malloc(sizeof(list_handle) * buckets);
	for (int i = 0; i < buckets; i++)
	{
		list_handle list = NULL;
		List_Init(list);
		hash->buckets[i] = list;
	}
}

void Hash_Insert(hash_handle hash, void * element, unsigned int key)
{
	int index = key % (hash->num_buckets);
	list_handle list = hash->buckets[index];
	List_Insert(list, element, key);
}

void Hash_Delete(hash_handle hash, unsigned int key)
{
	int index = key % (hash->num_buckets);
	list_handle list = hash->buckets[index];
	List_Delete(list, key);
}

void * Hash_Lookup(hash_handle hash, unsigned int key)
{
	int index = key % (hash->num_buckets);
	list_handle list = hash->buckets[index];
	return List_Lookup(list, key);
}
