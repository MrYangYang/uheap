#include "heap.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

heap *heap_init (int max_size)
{
	assert (max_size > 0);
	int total = max_size * sizeof(int) + sizeof(heap);
	heap *p = malloc (total);
	assert(p);
	memset (p, 0, total);
	p->max_size  = max_size;
	p->size = 0;
	return p;
}

void heap_insert (heap *h, int n)
{
	int sz = h->size++;
	if (h->size >= h->max_size)
		heap_expand (&h, HEAP_DEFAULT_INCR);	
	while (sz > 0) {
		// min heap
		if (n < h->arr[(sz - 1)/2]) { 
			h->arr[sz] = h->arr[(sz - 1)/2];
			sz = (sz  - 1)/2;
		} else {
			h->arr[sz] = n;
			return;
		}
	}
	h->arr[0] = n;
}

void heap_remove (heap *h, int *n)
{
	h->size--;
	*n = h->arr[0];
	h->arr[0] = h->arr[h->size];
	h->arr[h->size] = 0;
	int i = 1;
	int cv = h->arr[0];
	while (i < h->size) {
		if (i < (h->size - 1) && h->arr[i] > h->arr[i+1])
			i++;
		if (h->arr[i] < cv) {
			h->arr[(i - 1)/2] = h->arr[i];
			h->arr[i] = cv;
			i = i * 2 + 1;
		} else {
			return;
		}
	}
}

void heap_expand (heap **hp, int incr) {
	assert (incr > 0);
	int sz = (*hp)->max_size + incr;
	heap *tmp_heap = realloc (*hp, sizeof(heap) + sz * sizeof(int));
	assert (tmp_heap);
	tmp_heap->max_size = sz;
	*hp = tmp_heap;
}

