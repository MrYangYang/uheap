#include <stdio.h>
#include <stdlib.h>
#include "uheap.h"
#include <assert.h>
#include <CUnit/CUnit.h>
#include <CUnit/Console.h>
#include <CUnit/TestDB.h>
#include <CUnit/Basic.h>

static uheap *mheap = NULL;

typedef struct _test_data test_data;
struct _test_data
{
        int key;
        char data[20];
};

int cmpfunc(test_data *l, test_data *r)
{
        assert(l);
        assert(r);
        return l->key - r->key;
}

void test_uheap_init(void)
{

}

void test_cmpfunc(void)
{
        test_data l = {
                .key = 1,
                .data = "this is 1"
        };
        test_data r = {
                .key = 2,
                .data = "this is 2"
        };
        CU_ASSERT(cmpfunc(&l, &r) < 0);
        int (*p_cmpfunc)(void *, void *) = cmpfunc;
        CU_ASSERT(p_cmpfunc(&l, &r) < 0);
}

void test___uheap_parent(void)
{
        CU_ASSERT(__uheap_parent(1) == 0);
        CU_ASSERT(__uheap_parent(2) == 0);
        CU_ASSERT(__uheap_parent(3) == 1);
        CU_ASSERT(__uheap_parent(5) == 2);
}

void test___uheap_lchild(void)
{
        CU_ASSERT(__uheap_lchild(0) == 1);
        CU_ASSERT(__uheap_lchild(1) == 3);
        CU_ASSERT(__uheap_lchild(2) == 5);        
}

void test___get_elem(void){
        uheap *heap = uheap_init(test_data, 4, cmpfunc);
        CU_ASSERT(heap != NULL);
        test_data data = {
                .key = 0,
                .data = "haha"
        };
        memcpy(heap->arr, &data, heap->type_len);
        data.key = 1;
        memcpy(heap->arr + heap->type_len, &data, heap->type_len);
        data.key = 2;
        memcpy(heap->arr + 2 * heap->type_len, &data, heap->type_len);
        data.key = 3;
        memcpy(heap->arr + 3 * heap->type_len, &data, heap->type_len);

        test_data *res = NULL;
        res = __get_elem(heap, 0);
        CU_ASSERT(res->key == 0);
        res = __get_elem(heap, 1);
        CU_ASSERT(res->key == 1);
        res = __get_elem(heap, 2);
        CU_ASSERT(res->key == 2);
        res = __get_elem(heap, 3);
        CU_ASSERT(res->key == 3);
        
        free(heap);
}

void test___set_elem(void)
{
        uheap *heap = uheap_init(test_data, 4, cmpfunc);
        CU_ASSERT(heap != NULL);
        test_data data = {
                .key = 0,
                .data = "haha"
        };
        __set_elem(heap, 0, &data);
        data.key = 1;
        __set_elem(heap, 1, &data);
        data.key = 2;
        __set_elem(heap, 2, &data);
        data.key = 3;
        __set_elem(heap, 3, &data);
        
        CU_ASSERT(((test_data *)(heap->arr + 0 * heap->type_len)) -> key == 0);
        CU_ASSERT(((test_data *)(heap->arr + 1 * heap->type_len)) -> key == 1);
        CU_ASSERT(((test_data *)(heap->arr + 2 * heap->type_len)) -> key == 2);
        CU_ASSERT(((test_data *)(heap->arr + 3 * heap->type_len)) -> key == 3);

        free(heap);
}

void test___uheap_rchild(void)
{
        CU_ASSERT(__uheap_rchild(0) == 2);
        CU_ASSERT(__uheap_rchild(1) == 4);
        CU_ASSERT(__uheap_rchild(2) == 6);
}

void test_uheap_insert(void)
{
        // init test data;
        test_data value[6];
        test_data *tmp;
        int i;
        for(i = 0; i < 6; i++){
                (value[i]).key = i;
        }
        uheap_insert(mheap, &value[2]);
        CU_ASSERT(mheap->size == 1);
        uheap_insert(mheap, &value[0]);
        CU_ASSERT(mheap->size == 2);
        uheap_insert(mheap, &value[1]);
        CU_ASSERT(mheap->size == 3);
        uheap_insert(mheap, &value[4]);
        CU_ASSERT(mheap->size == 4);
        uheap_insert(mheap, &value[3]);
        CU_ASSERT(mheap->size == 5);
        uheap_insert(mheap, &value[5]);
        CU_ASSERT(mheap->size == 6);
        //for(i = 0; i < 6; i++) {
        //        free(value[i]);
        //}
        tmp = __get_elem(mheap, 0);
        CU_ASSERT(tmp->key == 0);
        printf("tmp->key  head %d\n", tmp->key);
        tmp = __get_elem(mheap, 1);
        printf("%d\n", tmp->key);
        CU_ASSERT(tmp->key == 2);
        tmp = __get_elem(mheap, 2);
        printf("%d\n", tmp->key);
        CU_ASSERT(tmp->key == 1);
        tmp = __get_elem(mheap, 3);
        printf("%d\n", tmp->key);
        CU_ASSERT(tmp->key == 4);
        tmp = __get_elem(mheap, 4);
        printf("%d\n", tmp->key);
        CU_ASSERT(tmp->key == 3);
        tmp = __get_elem(mheap, 5);
        printf("%d\n", tmp->key);
        CU_ASSERT(tmp->key == 5);

        CU_ASSERT(mheap->max_size == 21);
}

void test_uheap_remove(void)
{
        test_data *data = malloc(sizeof(test_data));
        uheap_remove(mheap, data);
        CU_ASSERT(data->key == 0);
        printf("remove 0 %d\n", data->key);
        CU_ASSERT(mheap->size == 5);
        uheap_remove(mheap, data);
        printf("remove 1 %d\n", data->key);
        CU_ASSERT(data->key == 1);
        CU_ASSERT(mheap->size == 4);
        uheap_remove(mheap, data);
        printf("remove 2 %d\n", data->key);
        CU_ASSERT(data->key == 2);
        CU_ASSERT(mheap->size == 3);
}

int init_suite_uheap(void)
{
        int max_sz = 1;
        mheap = uheap_init(test_data, max_sz, cmpfunc);
        printf("mheap %p\n", mheap);
        assert(mheap);
        printf("mheap->arr %p\n", mheap->arr);
        printf("type_len %u\n", mheap->type_len);
        assert(mheap->arr);


        printf("max_size %u\n", mheap->max_size);
        assert(max_sz == mheap->max_size);
        printf("size %u\n", mheap->size);
        assert(0 == mheap->size);

        return 0;
}

int clean_suite_uheap(void)
{
        free(mheap);
        return 0;
}

int main(void)
{
        CU_pSuite pSuite = NULL;

        if(CUE_SUCCESS != CU_initialize_registry())
                return CU_get_error();

        pSuite = CU_add_suite("suite_uheap",
                        init_suite_uheap,
                        clean_suite_uheap);
        if(NULL == pSuite) {
                CU_cleanup_registry();
                return CU_get_error();
        }

        CU_add_test(pSuite, "test cmpfunc", test_cmpfunc);
        CU_add_test(pSuite, "__uheap_parent", test___uheap_parent);
        CU_add_test(pSuite, "__uheap_lchild", test___uheap_lchild);
        CU_add_test(pSuite, "__uheap_rchild", test___uheap_rchild);
        CU_add_test(pSuite, "__get_elem", test___get_elem);
        CU_add_test(pSuite, "__set_elem", test___set_elem);
        
        CU_add_test(pSuite, "test of init uheap", test_uheap_init);
        CU_add_test(pSuite, "test of inset uheap", test_uheap_insert);
        CU_add_test(pSuite, "test of remove uheap", test_uheap_remove);

        CU_basic_set_mode(CU_BRM_NORMAL);
        CU_basic_run_tests();
        CU_cleanup_registry();
        return CU_get_error();
}

