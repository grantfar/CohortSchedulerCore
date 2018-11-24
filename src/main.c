#include "readCohorts.h"
#include "readClasses.h"

int main(int argc, char * argv[]){
	node * cohortReqList = readCohorts("cohortReqs.csv");
	node * classList = readCourses("courseList.csv");
	node * cohortList = sortCohorts(cohortReqList);
	node * sortedClasses = sortClasses(cohortList, classList);
	while(cohortList != NULL){
		printf("%s\n", ((cohort *)cohortList->data)->name);
		cohortList = cohortList->next;
	}
}