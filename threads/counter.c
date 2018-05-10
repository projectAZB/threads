//
//  counter.c
//  threads
//
//  Created by Adam on 5/9/18.
//  Copyright © 2018 Adam. All rights reserved.
//

#include "counter.h"

#include <stdio.h>
#include <stdlib.h>

#ifdef PTHREADS

#include <pthread.h>

#endif

void Counter_Init(counter_handle c, int value)
{
	c->value = value;
	c->spinlock = (spinlock_handle)malloc(sizeof(spinlock_t));
#ifdef PTHREADS
	pthread_mutex_init(&c->spinlock->lock, NULL);
#endif
}

int Counter_GetValue(counter_handle c)
{
	return c->value;
}

void Counter_Increment(counter_handle c)
{
	spinlock_acquire(c->spinlock);
	(c->value)++;
	spinlock_release(c->spinlock);
}

void Counter_Decrement(counter_handle c)
{
	spinlock_acquire(c->spinlock);
	(c->value)--;
	spinlock_release(c->spinlock);
}
