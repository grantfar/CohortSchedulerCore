#include <CUnit/CUnit.h>
#include <CUnit/Automated.h>
#include "../src/sortClasses.h"

void sortClassesTest(){
	node * cohortReqList = readCohorts("cohortReqs.csv");
	node * classList = readCourses("courseList.csv");
	node * cohortList = sortCohorts(cohortReqList);
	node * sortedClasses = sortClasses(cohortList, classList);
	CU_ASSERT(((clas *)sortedClasses->data)->cohortCt >= ((clas *)sortedClasses->next->data)->cohortCt);
	CU_ASSERT(((clas *)sortedClasses->next->data)->cohortCt >= ((clas *)sortedClasses->next->next->data)->cohortCt);
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
    CU_add_test(psuite,"sortClassesTest",sortClassesTest);
    CU_automated_run_tests();
}