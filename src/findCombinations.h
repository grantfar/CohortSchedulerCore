#ifndef FINDCOMBINATIONS_H
#define FINDCOMBINATIONS_H
#include "sortClasses.h"

typedef struct _cohortSchedule{
	cohort * co;
	node * classes;
} cohortSchedule;

void findAll(node * classList, node * cohortList, char * out);

int findAllSectionArrayCombos(node * classList, node * cohortList, node * ordered, FILE * outFile, node * pool);

int findAllCohortCombos(node * classList, node * cohortList,node * orderedCl, node * ordered, FILE * outFile, node * pool, int ct);

node * getNeededCohorts(node * cohortList, clas * cl);

int fitsInClass(cohortSchedule * coh, course * sect);

int fitsInSchedule(cohortSchedule * co, course * sect);

int writeSchedule(node * cohortList, FILE * outFile);

course ** getSectionsArr(node * sectList, int ct);

cohortSchedule ** getCohortsArr(node * cohortList, clas * cl);

int tryCombination(node * classList, node * cohortList, node * orderedCl, node * orderedCo, FILE * outFile, int cohCt);

#endif