//
//  spin.c
//  threads
//
//  Created by Adam on 5/9/18.
//  Copyright © 2018 Adam. All rights reserved.
//

#include "spin.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <assert.h>

#ifdef PTHREADS

#include <pthread.h>

#endif

static inline uint
xchg(volatile unsigned int *addr, unsigned int newval)
{
	uint result;
	asm volatile("lock; xchgl %0, %1" : "+m" (*addr), "=a" (result) : "1" (newval) : "cc");
	//xchg: exchange the two source operands
	//two outputs: *addr and result
	//"+m", m means the operand is directly from memory, + means read and write
	//"=a": suggest gcc to put the operand value into eax register; `=' means write only
	//one input: newval, "1" means it uses the same constraint as the earlier 1th, i.e., it
	// will be put into eax and then be overwritten
	//"cc" means the condition register might be altered
	return result;
}

void spinlock_acquire(spinlock_handle lock) {
#ifdef PTHREADS
	pthread_mutex_lock(&lock->lock);
#else
	while (xchg(&lock->flag, 1) == 1) { //spin
	}
#endif
	
}

void spinlock_release(spinlock_handle lock) {

#ifdef PTHREADS
	pthread_mutex_unlock(&lock->lock);
#else
	lock->flag = 0;
#endif
}
