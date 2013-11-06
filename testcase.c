#include <stdio.h>
#include <stdlib.h>
#include "heap.h"
#include <CUnit/CUnit.h>
#include <CUnit/Console.h>
#include <CUnit/TestDB.h>
#include <CUnit/Basic.h>

static heap *mheap = NULL;
/*
 * test if heap_init work
 */
void test_heap_init (void)
{
	int max_size = 1;
	mheap = heap_init (max_size);
	CU_ASSERT(mheap->arr != NULL);
	CU_ASSERT(1 == mheap->max_size);
	CU_ASSERT(0 == mheap->size);	
}

/*
 * test if heap_insert
 */
void test_heap_insert (void)
{
	heap_insert(mheap, 2);
	CU_ASSERT(mheap->arr[0] == 2);
	heap_insert(mheap, 0);
	CU_ASSERT(mheap->arr[1] == 2);
	CU_ASSERT(mheap->arr[0] == 0);
	heap_insert(mheap, 1);
	CU_ASSERT(mheap->arr[2] == 1);
	CU_ASSERT(mheap->size == 3);

	CU_ASSERT(mheap->max_size == 21);
}

/*
 * test if heap_remove
 */
void test_heap_remove (void)
{
	int n;
	heap_remove(mheap, &n);
	CU_ASSERT(0 == n);
	CU_ASSERT(2 == mheap->size);
	heap_remove(mheap, &n);
	CU_ASSERT(1 == n);
	CU_ASSERT(1 == mheap->size);
	heap_remove(mheap, &n);
	CU_ASSERT(2 == n);
	CU_ASSERT(0 == mheap->size);
}

int init_suite_heap (void)
{
	return 0;
}

int clean_suite_heap (void)
{
	free (mheap);
	return 0;
}

int main (void)
{
	CU_pSuite pSuite = NULL;

	/* initialize the CUnit test registry */
	if (CUE_SUCCESS != CU_initialize_registry())
		return CU_get_error();

	/* add a suite to the registry */
	pSuite = CU_add_suite ("suite_heap", 
			       init_suite_heap, 
			       clean_suite_heap);
	if (NULL == pSuite) {
		CU_cleanup_registry();
		return CU_get_error();
	}

	CU_add_test(pSuite, "test of init heap", test_heap_init);
	CU_add_test(pSuite, "test of insert heap", test_heap_insert);
	CU_add_test(pSuite, "test of remove heap", test_heap_remove);
	
	CU_basic_set_mode(CU_BRM_VERBOSE);
	CU_basic_run_tests();
	CU_cleanup_registry();
	return CU_get_error();
}

