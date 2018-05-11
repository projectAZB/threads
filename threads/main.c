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
#include <sys/time.h>
#include <pthread.h>
#include <math.h>

#include "counter.h"
#include "list.h"
#include "hash.h"

#define ARR_SIZE(x) (int)(sizeof(x)/sizeof(x[0]))

#define MAX 1000000

int numbers[MAX];

long get_cur_time()
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	time_t cur_time = tv.tv_sec;
	return cur_time;
}

long average(long * values, int size)
{
	float sum = 0;
	for (int r = 0; r < size; r++)
	{
		sum += values[r];
	}
	return round(((double)sum) / size);
}

void print_array(long * values, int size)
{
	printf(" [");
	for (int i = 0; i < size; i++)
	{
		printf("%ld", values[i]);
		if (i == size - 1) {
			printf("] ");
		}
		else {
			printf(", ");
		}
	}
}

//COUNTER TEST
void * counter_increment(void * counter)
{
	for (int i = 0; i < MAX; i++)
	{
		Counter_Increment((counter_handle)counter);
	}
	return NULL;
}

void counter_test(int runs, int thread_count)
{
	long times[runs];
	for (int r = 0; r < runs; r++)
	{
		long start = get_cur_time();
		pthread_t threads[thread_count];
		counter_handle counter = (counter_handle)malloc(sizeof(*counter));
		Counter_Init(counter, 0);
		for (int t = 0; t < thread_count; t++)
		{
			pthread_create(&threads[t], NULL, counter_increment, (void *)counter);
		}
		for (int t = 0; t < thread_count; t++)
		{
			pthread_join(threads[t], NULL);
		}
		long end = get_cur_time();
		times[r] = end - start;
	}
	long avg = average(times, runs);
	printf("Counter Test: %d Trials, %d Threads: ", runs, thread_count);
	print_array(times, runs);
	printf("Average Runtime: %ld\n", avg);
}

//LIST TEST
void * list_insert(void * list)
{
	for (int i = 0; i < MAX; i++)
	{
		List_Insert((list_handle)list, &numbers[i], i);
	}
	return NULL;
}

void list_test(int runs, int thread_count)
{
	long times[runs];
	for (int r = 0; r < runs; r++)
	{
		long start = get_cur_time();
		pthread_t threads[thread_count];
		list_handle list = (list_handle)malloc(sizeof(*list));
		List_Init(list);
		for (int t = 0; t < thread_count; t++)
		{
			pthread_create(&threads[t], NULL, list_insert, (void *)list);
		}
		for (int t = 0; t < thread_count; t++)
		{
			pthread_join(threads[t], NULL);
		}
		long end = get_cur_time();
		times[r] = end - start;
	}
	long avg = average(times, runs);
	printf("List Test: %d Trials, %d Threads: ", runs, thread_count);
	print_array(times, runs);
	printf("Average Runtime: %ld\n", avg);
}

int main(int argc, const char * argv[])
{
	for (int i = 0; i < MAX; i++)
	{
		numbers[i] = i + 1;
	}
	srand((unsigned int)time(NULL));
	counter_test(1, 4);
	counter_test(1, 8);
	counter_test(1, 12);
	list_test(3, 4);
	list_test(3, 8);
	list_test(3, 12);
	return 0;
}
