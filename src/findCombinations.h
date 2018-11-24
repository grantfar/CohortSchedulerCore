#ifndef FINDCOMBINATIONS_H
#define FINDCOMBINATIONS_H
#include "sortClasses.h"

typedef struct _cohortSchedule{
	cohort * co;
	node * classes;
} cohortSchedule;

void findAll(node * classList, node * cohortList, char * out);

int findSchedulesForClass(node * classList, node * cohortList, FILE * outFile);

int fitsInClass(int cohortSize, course * sect);

int fitsInSchedule(cohortSchedule * co, course * sect);

int writeSchedule(node * cohortList, FILE * outFile);

#endif