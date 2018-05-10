//
//  main.c
//  threads
//
//  Created by Adam on 5/9/18.
//  Copyright © 2018 Adam. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <time.h>

#include "counter.h"
#include "list.h"

void counter_test(int times)
{
	for (int r = 0; r < times; r++)
	{
		counter_handle counter = (counter_handle)malloc(sizeof(counter_t));
		Counter_Init(counter, -r);
		int count_to = rand() % 1000000;
		int sum = 0;
		for (int i = 0; i < count_to; i++)
		{
			int flip = rand() % 2;
			if (flip) {
				Counter_Increment(counter);
				sum++;
			}
			else {
				Counter_Decrement(counter);
				sum--;
			}
		}
		sum = sum + -r;
		assert(Counter_GetValue(counter) == sum);
	}
}

void list_test(int times)
{
	for (int r = 0; r < times; r++)
	{
		list_handle list = (list_handle)malloc(sizeof(list_t));
		List_Init(list);
		int operations = rand() % 1000000;
		int occupied[operations];
		int numbers[operations];
		for (int i = 0; i < operations; i++)
		{
			numbers[i] = i + 1;
			occupied[i] = 0;
		}
		for (int i = 0; i < operations; i++)
		{
			List_Insert(list, &numbers[i], i);
			occupied[i] = 1;
			/*
			if (list->count == 0) {
				List_Insert(list, &numbers[i], i);
				occupied[i] = 1;
			}
			
			else {
				int flip = rand() % 2;
				if (flip) {
					List_Insert(list, &numbers[i], i);
					occupied[i] = 1;
				}
				else {
					while (1) { //a delete WILL happen
						int rand_index = rand() % i;
						if (occupied[rand_index] == 0) { //was already deleted
							void * data = List_Lookup(list, rand_index);
							assert(data == NULL);
							continue;
						}
						else { //should still be in, delete
							void * data = List_Lookup(list, rand_index);
							assert(data != NULL);
							List_Delete(list, rand_index);
							occupied[rand_index] = 0; //now it's deleted
							break;
						}
					}
				}
			}
			 */
		}
		
		int count = 0;
		for (int i = 0; i < operations; i++)
		{
			if (occupied[i] == 1) {
				count++;
			}
		}
		assert(count == list->count);
	}
}

void hash_test(int times)
{
	
}

int main(int argc, const char * argv[])
{
	srand((unsigned int)time(NULL));
	counter_test(10);
	list_test(10);
	return 0;
}
