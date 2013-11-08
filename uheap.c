#include "uheap.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

uheap *__uheap_init_mem (size_t type_len,size_t max_size)
{
        assert (max_size > 0);
        assert (type_len > 0);
        int total = max_size * type_len + sizeof(uheap);
        uheap *p = malloc (total);
        assert(p);
        memset (p, 0, total);
        p->max_size  = max_size;
        p->size = 0;
        p->type_len = type_len;
        return p;
}

void uheap_insert (uheap *h, void *elem)
{
        int sz = h->size++;
        if (h->size >= h->max_size)
                uheap_expand (&h, HEAP_DEFAULT_INCR);
        while (sz > 0) {
                // min heap
                int i = (h->cmpfunc)(__get_elem(h, __uheap_parent(sz)), elem);
                printf("cmp return %d\n", i);
                if ((h->cmpfunc)(__get_elem(h, __uheap_parent(sz)), elem) > 0 ){ 
                        //memcpy(__get_elem(h, sz), __get_elem(h, __uheap_parent(sz)), h->type_len);
                        void *src = __get_elem(h, __uheap_parent(sz));
                        __set_elem(h, sz, src);
                        // h->arr[sz] = h->arr[(sz - 1)/2];
                        sz = __uheap_parent(sz);
                } else {
                        __set_elem(h, sz, elem);
                        //memcpy(__get_elem(h, sz), elem, h->type_len);
                        //h->arr[sz] = n;
                        return;
                }
        }
        __set_elem(h, 0, elem);
}

void uheap_remove (uheap *h, void *n)
{
        if(h->size <= 0) {
                return;
        }
        h->size--;
        memcpy(n, h->arr, h->type_len);
        //*n = h->arr[0];))
        //h->arr[0] = h->arr[h->size];
        memcpy(h->arr, __get_elem(h, h->size), h->type_len);
        //h->arr[h->size] = 0;
        memset(__get_elem(h, h->size), 0, h->type_len);
        int i = 1;
        void *tmp = malloc(h->type_len);
        memset(tmp, 0, h->type_len);
        memcpy(tmp, __get_elem(h, 0), h->type_len);
        while (i < h->size) {
                if (i < (h->size - 1) && ((h->cmpfunc)(__get_elem(h, i), __get_elem(h, i + 1))) > 0)
                        //        h->arr[i] > h->arr[i+1])
                        i++;
                if ((h->cmpfunc)(__get_elem(h, i), tmp) < 0) {
                        //h->arr[i] < cv) {
                        memcpy(__get_elem(h, __uheap_parent(i)), __get_elem(h, i), h->type_len);
                        //h->arr[(i - 1)/2] = h->arr[i];
                        //h->arr[i] = cv;
                        memcpy(__get_elem(h, i), tmp, h->type_len);
                        i = __uheap_lchild(i);
                } else {
                        return;
                }
        }
}

void uheap_expand (uheap **hp, int incr) {
        assert (incr > 0);
        int sz = (*hp)->max_size + incr;
        uheap *tmp_heap = realloc (*hp, sizeof(uheap) + sz * ((*hp)->type_len) );
        assert (tmp_heap);
        tmp_heap->max_size = sz;
        *hp = tmp_heap;
}

