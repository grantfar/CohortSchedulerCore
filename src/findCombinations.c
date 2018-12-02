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
	int cohortCt = ((clas *)classList->data)->cohortCt;
	int offeringCt = ((clas *)classList->data)->offeringCt;
	//sort em into arrays
	course ** sections = getSectionsArr((clas *)classList->data);
	cohortSchedule ** whoNeed = getCohortsArr(cohortList, classList->data);
	//iterate through combos
	for(int i = 0; i < offeringCt; i++){
		for(int j = 0; j < cohortCt; j++){
			tryCombination(sections, whoNeed, offeringCt, cohortCt, i, j, classList, cohortList, outFile);
		}
	}
	return 0;
}

int fitsInClass(cohortSchedule * coh, course * sect){
	int cohortSize = 0;
	node * reqs = coh->co->cohortReqs;
	while(reqs){
		if(strcmp(((cohortReq *)reqs->data)->name, sect->name)==0){
			cohortSize = ((cohortReq *)reqs->data)->nbrOfSeats;
		}
		reqs = reqs->next;
	}
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
	char * name1 = sect->name;
	char * name2;
	while(classes){
		name2 = ((course *)classes->data)->name; 
		start2 = ((course *)classes->data)->startTime;
		end2 = ((course *)classes->data)->endTime;
		campus2 = ((course *)classes->data)->campus;
		if(name1[0]=='M' && name2[0] == 'M'){

		}else if(start1 < start2){
			if(campus1 == campus2){
				if(end1 + 10 > start2){
					return 0;
				}
			}else{
				if(end1 + 40 > start2){
					return 0;
				}else if(end1 + 80 > start2 && (start2/100)>(end1/100)){
					return 0;
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
					return 0;
				}
			}
		}
		classes = classes->next;
	}
	return 1;
}

int writeSchedule(node * cohortList, FILE * outFile){
	//make sure its valid
	node * cohortCopy = cohortList;
	node * classes;
	while(cohortCopy){
		classes = ((cohortSchedule *)cohortCopy->data)->classes;
		if(classes == NULL || classes->next == NULL || classes->next->next == NULL){
			return 1;
		}
		cohortCopy = cohortCopy->next;
	}

	fprintf(outFile, "\nSchedule:\n");
	cohortSchedule * curCo;
	course * curCl;
	while(cohortList){
		curCo = ((cohortSchedule *) cohortList->data);
		fprintf(outFile, "Cohort: %s\n", curCo->co->name);
		fprintf(outFile, "Classes: \n");
		while(curCo->classes){
			curCl = curCo->classes->data;
			fprintf(outFile, "%s, %d, %s, %d - %d, %c\n", curCl->name, curCl->section, curCl->days, curCl->startTime, curCl->endTime, curCl->campus);
			curCo->classes = curCo->classes->next;
		}
		cohortList = cohortList->next;
	}
	return 0;
}

course ** getSectionsArr(clas * cl){
	course ** toRet = malloc(sizeof(course *) * (1 + cl->offeringCt));
	node * offerings = cl->offerings;
	for(int i = 0; i<cl->offeringCt && offerings != NULL; i++){
		toRet[i] = (course *) offerings->data;
		toRet[i+1] = NULL;
		offerings = offerings->next;
	}
	return toRet;
}

cohortSchedule ** getCohortsArr(node * cohortList, clas * cl){
	cohortSchedule ** toRet = malloc(sizeof(cohortSchedule *) * (1 + cl->cohortCt));
	node * cohorts = cohortList;
	int i = 0;
	while(cohorts && i < cl->cohortCt){
		node * cohortReqs = ((cohortSchedule *)cohorts->data)->co->cohortReqs;
		while(cohortReqs){
			if(strcmp(((cohortReq *)cohortReqs->data)->classReq,cl->name) == 0){
				toRet[i] = (cohortSchedule *) cohorts->data;
				i++;
			}
			cohortReqs = cohortReqs->next;
		}
		cohorts = cohorts->next;
	}
	return toRet;
}

void tryCombination(course ** off, cohortSchedule ** coh, int offCt, int cohCt, int i, int j, node * classList, node * cohortList, FILE * outFile){
	int oInd = 0;
	int cInd = 0;
	while(cInd < cohCt){
		while(!fitsInClass(coh[(cInd + j)%cohCt], off[(oInd + i)%offCt])&&oInd < offCt){
			oInd++;
		}
		/*if(fitsInSchedule(coh[(cInd + j)%cohCt], off[(oInd + i)%offCt])&& oInd < offCt){
			coh[(cInd + j)%cohCt]->classes = addNode(off[(oInd + i)%offCt], coh[(cInd + j)%cohCt]->classes);
		}*/
		coh[(cInd + j)%cohCt]->classes = addNode(off[(oInd + i)%offCt], coh[(cInd + j)%cohCt]->classes);
		cInd++;
		oInd = 0;
	}
	if(classList->next == NULL){
		writeSchedule(cohortList, outFile);
	}else{
		findSchedulesForClass(classList->next, cohortList, outFile);
	}
	
	for(int k = 0; k< cInd; k++){
		if(coh[(j + k)%cohCt]->classes != NULL){
			coh[(j + k)%cohCt]->classes = coh[(j + k)%cohCt]->classes->next;
		}
	}
}