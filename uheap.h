#ifndef _HEAP_H_
#define _HEAP_H_

#define HEAP_DEFAULT_INCR 20

static 

typedef struct _uheap uheap;
struct _uheap {
        size_t max_size; // current max size of heap
        size_t size;     // current size of heap
        size_t type_len; // elem type len in byte
        int (*cmpfunc)(void *, void *); // comparator
        char arr[0];     // mem of heap
};

#define uheap_init(elem_type, max_sz, cmpfunc)  ({ (elem_type) p = NULL; \
                p = __uheap_init_mem(sizof((elem_type)), (max_sz)), \
                p->cmpfunc = cmpfunc, \
                p;})

#define uheap_cmp(p_uheap, elem_type, el, er) ({ \
                (elem_type) elt = ((elem_type) *) el; \
                (elem_type) ert = ((elem_type) *) er; \
                (p_uheap->cmpfunc)(elt, ert);})

#define __uheap_parent(i) ((i - 1) >> 1)
#define __uheap_lchild(i) (i << 1)
#define __uheap_rchild(i) ((i << 1) + 1)

// init a heap
uheap *__uheap_init_mem (size_t type_len, size_t max_sz);
                

// insert element into heap
void uheap_insert (uheap *h, void *elem);

// remove element from heap
void uheap_remove (uheap *p, void *n);

// expand heap max_size
void uheap_expand (uheap **p, int incr);

#endif
