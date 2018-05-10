//
//  hash.h
//  threads
//
//  Created by Adam on 5/9/18.
//  Copyright © 2018 Adam. All rights reserved.
//

#ifndef hash_h
#define hash_h

#include "list.h"

struct hash_t {
	int num_buckets;
	list_handle * buckets;
};
typedef struct hash_t hash_t;
typedef hash_t * hash_handle;

void Hash_Init(hash_handle hash, int buckets);
void Hash_Insert(hash_handle hash, void * element, unsigned int key);
void Hash_Delete(hash_handle hash, unsigned int key);
void * Hash_Lookup(hash_handle hash, unsigned int key);

#endif 
