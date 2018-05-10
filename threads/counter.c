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

struct counter_t {
	int value;
};

void Counter_Init(counter_handle c, int value)
{
	c = (counter_handle)malloc(sizeof(*c));
	c->value = value;
}

int Counter_GetValue(counter_handle c)
{
	return c->value;
}

void Counter_Increment(counter_handle c)
{
	(c->value)++;
}

void Counter_Decrement(counter_handle c)
{
	(c->value)--;
}
