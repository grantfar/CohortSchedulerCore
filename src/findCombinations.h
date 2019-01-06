#ifndef FINDCOMBINATIONS_H
#define FINDCOMBINATIONS_H
#include "sortClasses.h"
#include <ctype.h>

typedef struct _cohortSchedule{
	cohort * co;
	node * classes;
} cohortSchedule;

void findAll(node * classList, node * cohortList, char * out);

int findCombosForHeadCohort(node * classList, node * cohortList, FILE * outFile, node * assigned);

int pickClass(node * classList, node * cohortList, FILE * outFile, node * assigned, node * needed);

node * getClassesFromReqs(node * reqs, node * classList);

int fitsInClass(cohortReq * coh, course * sect);

int fitsInSchedule(node * classes, course * sect, cohortReq * coh, node * cohReqs);

int writeSchedule(node * cohortList, FILE * outFile);

int tryCombination(node * classList, node * cohortList, FILE * outFile, node * assigned);

int arePair(char * name1, cohortReq * coh, node * cohortReqs);

#endif