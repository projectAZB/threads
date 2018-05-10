//
//  spin.h
//  threads
//
//  Created by Adam on 5/9/18.
//  Copyright © 2018 Adam. All rights reserved.
//

#ifndef spin_h
#define spin_h

struct spinlock_t {
	volatile unsigned int flag;
};

typedef struct spinlock_t spinlock_t;
typedef spinlock_t * spinlock_handle;

void spinlock_acquire(spinlock_handle lock);
void spinlock_release(spinlock_handle lock);

#endif 
