#ifndef SORTCLASSES_H
#define SORTCLASSES_H
#include "readClasses.h"
#include "readCohorts.h"

typedef struct _clas{
	char * name;
	int cohortCt;
	int offeringCt;
	node * cohorts;
	node * offerings;
} clas;

node * sortClasses(node * cohortList, node * classList);

node * arrangeClasses(node * cohortList, node * classList);

clas * gatherOfferings(node * classList,char * className, node * cohortList);

clas * gatherCohorts(clas * cl, node * cohortList);

int needsClass(node * cohortReqs, char * name);

#endif