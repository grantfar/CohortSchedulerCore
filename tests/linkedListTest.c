#include <CUnit/CUnit.h>
#include <CUnit/Automated.h>
#include "../src/linkedList.h"

void linkedListTest(){
	int i = 1;
	int j = 2;
	int k = 3;
	node * test = addNode(&i, NULL);
	test = addNode(&j, test);
	test = addNode(&k, test);
	int * l = (int*)removeNode(&test);
	int * m = (int*)removeNode(&test);
	int * n = (int*)removeNode(&test);
	CU_ASSERT(k == *l);
	CU_ASSERT(j == *m);
	CU_ASSERT(i == *n);
	
}

int close(){
    return 0;
}

int init(){
    return 0;
}

int main(int argc, char* argv[]){
	
	CU_pSuite psuite = NULL;

    if (CUE_SUCCESS != CU_initialize_registry())
    {
        return CU_get_error();
    }

    psuite = CU_add_suite("LinkedListSuite",init,close);
    CU_add_test(psuite,"linkedListTest",linkedListTest);
    CU_automated_run_tests();
}
