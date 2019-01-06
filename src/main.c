#include "readCohorts.h"
#include "readClasses.h"
#include "sortClasses.h"
#include "findCombinations.h"

int main(int argc, char * argv[]){
	node * cohortReqList = readCohorts("cohortReqsLarge.csv");
	node * classList = readCourses("courseListLarge.csv");
	node * cohortList = sortCohorts(cohortReqList);
	node * sortedClasses = sortClasses(cohortList, classList);
	findAll(sortedClasses, cohortList, "output.txt");
}
