#include <CUnit/CUnit.h>
#include <CUnit/Automated.h>
#include "../src/readClasses.h"

void parseLineTest(){
	course * retVal = parseCourse("BIOS1600,1,MW,1000,1140,M,40");
	CU_ASSERT(strcmp(retVal->name, "BIOS1600") == 0);
	CU_ASSERT(retVal->section == 1);
	CU_ASSERT(retVal->classSize == 40);
}

void readClassesTest(){
	node * retVal = readCourses("./courseList.csv");
	course * c = (course *) retVal->data;
	int i = strcmp(c->name, "GEOS1300");
	CU_ASSERT(i == 0);
	
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

    psuite = CU_add_suite("readClassesSuite",init,close);
    CU_add_test(psuite,"readClassesTest",readClassesTest);
    CU_add_test(psuite,"parseLineTest",parseLineTest);
    CU_automated_run_tests();
}