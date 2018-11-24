#include <CUnit/CUnit.h>
#include <CUnit/Automated.h>
#include "../src/readCohorts.h"

void parseLineTest(){
	cohortReq * retVal = parseLine("BIOS1,BIOS1600,18");
	CU_ASSERT(strcmp(retVal->name, "BIOS1") == 0);
	CU_ASSERT(retVal->nbrOfSeats == 18);
}

void readCohortsTest(){
	node * retVal = readCohorts("./cohortReqs.csv");
	cohortReq * c = (cohortReq *) retVal->data;
	int i = strcmp(c->name, "ENV1");
	CU_ASSERT(i == 0);
	
}

void sortCohortsTest(){
	printf("In sort Test\n");
	node * cohortReqList = readCohorts("./cohortReqs.csv");
	node * cohortList = sortCohorts(cohortReqList);
	CU_ASSERT(cohortList != NULL);
	while(cohortList != NULL){
		printf("%s\n", ((cohort *)cohortList->data)->name);
		cohortList = cohortList->next;
	}
}

void arrContainsTest(){
	char ** tst = malloc(2 * sizeof(char *));
	tst[0] = malloc(8 * sizeof(char));
	strcpy(tst[0], "test");
	tst[1] = NULL;
	CU_ASSERT(arrContains(tst, "test\0")==1);
	CU_ASSERT(arrContains(tst, "a\0")==0);
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

    psuite = CU_add_suite("readCohortsSuite",init,close);
    CU_add_test(psuite,"readCohortsTest",readCohortsTest);
    CU_add_test(psuite,"parseLineTest",parseLineTest);
    CU_add_test(psuite, "arrContainsTest", arrContainsTest);
    CU_add_test(psuite, "sortCohortsTest", sortCohortsTest);
    CU_automated_run_tests();
}