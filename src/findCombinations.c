#include "findCombinations.h"

void findAll(node * classList, node * cohortList, char * out){
	node * cur = cohortList;
	cohortList = NULL;
	cohortSchedule * coSch;
	while(cur){
		coSch = malloc(sizeof(cohortSchedule));
		coSch->co = cur->data;
		coSch->classes = NULL;
		cohortList = addNode(coSch, cohortList);
		cur = cur->next;
	}
	FILE * outFile = fopen(out, "w");
	findSchedulesForClass(classList, cohortList, outFile);
}

int findSchedulesForClass(node * classList, node * cohortList, FILE * outFile){
	//sort em into arrays
	course ** sections = malloc((1 + ((clas *)classList->data)->offeringCt) * sizeof(course *));
	cohortSchedule ** whoNeed = malloc((1 + ((clas *)classList->data)->cohortCt) * sizeof(cohortSchedule *));

	

	//iterate through combos

	//in each valid combo, call recursively for next class down the line
	//if last class, print instead of recurse


}

int fitsInClass(int cohortSize, course * sect){
	int size = sect->enrolled + cohortSize;
	return sect->classSize - size;
}

int fitsInSchedule(cohortSchedule * co, course * sect){
	int start1 = sect->startTime;
	int end1 = sect->endTime;
	char campus1 = sect->campus;
	node * classes = co->classes;
	int start2;
	int end2;
	char campus2;
	while(classes){
		start2 = ((course *)classes->data)->startTime;
		end2 = ((course *)classes->data)->endTime;
		campus2 = = ((course *)classes->data)->campus;
		if(start1 < start2){
			if(campus1 == campus2){
				if(end1 + 10 > start2){
					return 0;
				}
			}else{
				if(end1 + 40 > start2){
					return 0;
				}else if(end1 + 80 > start2 && (start2/100)>(end1/100)){
					return 0
				}
			}
		}else{
			if(campus1 == campus2){
				if(end2 + 10 > start1){
					return 0;
				}
			}else{
				if(end2 + 40 > start1){
					return 0;
				}else if(end2 + 80 > start1 && (start1/100) > (end2/100)){
					return 0
				}
			}
		}
		classes = classes->next;
	}
	return 1;
}

int writeSchedule(node * cohortList, FILE * outFile){
	fprintf(outFile, "\nSchedule:\n");
	cohortSchedule * curCo;
	course * curCl;
	while(cohortList){
		curCo = (cohortSchedule) * cohortList->data;
		fprintf(outFile, "Cohort: %s\n", curCo->co->name);
		fprintf(outFile, "Classes: \n");
		while(curCo.classes){
			curCl = curCo.classes->data;
			fprintf("%s, %d, %s, %d - %d, %c", curCl->name, curCl->section, curCl->days, curCl->startTime, curCl->endTime, curCl->campus);
			curCo.classes = curCo.classes->next;
		}
		cohortList = cohortList->next;
	}
}