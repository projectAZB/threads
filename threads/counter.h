//
//  counter.h
//  threads
//
//  Created by Adam on 5/9/18.
//  Copyright © 2018 Adam. All rights reserved.
//

#ifndef counter_h
#define counter_h

#include "spin.h"

struct counter_t {
	int value;
	spinlock_handle spinlock;
};
typedef struct counter_t counter_t;
typedef counter_t * counter_handle;

void Counter_Init(counter_handle c, int value);
int Counter_GetValue(counter_handle c);
void Counter_Increment(counter_handle c);
void Counter_Decrement(counter_handle c);

#endif 
