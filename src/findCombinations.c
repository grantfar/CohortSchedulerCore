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
	findAllSectionArrayCombos(classList, cohortList, NULL, outFile, ((clas *)classList->data)->offerings);
	fclose(outFile);
}

int findAllSectionArrayCombos(node * classList, node * cohortList, node * ordered, FILE * outFile, node * pool){
	//node * pool = ((clas *)classList->data)->offerings;
	/*node * cur = pool;
	node * before = NULL;
	while(cur){
		ordered = addNode(cur->data, ordered);
		if(pool->next == NULL){
			node * whoNeed = getNeededCohorts(cohortList, classList->data);
			findAllCohortCombos(classList, cohortList, ordered, 0, outFile, whoNeed, 0);
			node * toFree;
			while(whoNeed){
				toFree = whoNeed;
				whoNeed = whoNeed->next;
				free(toFree);
			}
		}else{
			//remove cur and pass
			if(before != NULL){
				before->next = before->next->next;
				findAllSectionArrayCombos(classList, cohortList, ordered, outFile, pool);
				cur->next = before->next;
				before->next = cur;
			}else{
				findAllSectionArrayCombos(classList, cohortList, ordered, outFile, pool->next);
			}
		}
		node * toFree = ordered;
		ordered = ordered->next;
		free(toFree);
		before = cur;
		cur = cur->next;
	}*/
	node * whoNeed = getNeededCohorts(cohortList, classList->data);
	findAllCohortCombos(classList, cohortList, pool, NULL, outFile, whoNeed, 0);
	return 0;
}

int findAllCohortCombos(node * classList, node * cohortList,node * orderedCl, node * ordered, FILE * outFile, node * pool, int ct){
	node * cur = pool;
	node * before = NULL;
	while(cur){
		ordered = addNode(cur->data, ordered);
		ct++;
		if(pool->next == NULL){
			tryCombination(classList,cohortList, orderedCl, ordered, outFile, ct);
		}else{
			if(before != NULL){
				before->next = before->next->next;
				findAllCohortCombos(classList, cohortList, orderedCl, ordered, outFile, pool, ct);
				cur->next = before->next;
				before->next = cur;
			}else{
				findAllCohortCombos(classList, cohortList, orderedCl, ordered, outFile, cur->next, ct);
			}
		}
		node * tf = ordered;
		ordered = ordered->next;
		ct--;
		free(tf);
		before = cur;
		cur = cur->next;
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
	char * days1 = sect->days;
	node * classes = co->classes;
	int start2;
	int end2;
	char campus2;
	char * name1 = sect->name;
	char * name2;
	char * days2;
	int sameDay = 0;
	while(classes){
		name2 = ((course *)classes->data)->name; 
		start2 = ((course *)classes->data)->startTime;
		end2 = ((course *)classes->data)->endTime;
		campus2 = ((course *)classes->data)->campus;
		days2 = ((course *)classes->data)->days;
		for(int i = 0; i < strlen(days1); i++){
			for(int j = 0; j < strlen(days2); j++){
				if(days2[j] == days1[i]){
					sameDay = 1;
				}
			}
		}
		if(sameDay){
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
		}
		sameDay = 0;
		classes = classes->next;
	}
	return 1;
}

int writeSchedule(node * cohortList, FILE * outFile){
	node * classes;
	fprintf(outFile, "\nSchedule:\n");
	cohortSchedule * curCo;
	course * curCl;
	while(cohortList){
		curCo = ((cohortSchedule *) cohortList->data);
		fprintf(outFile, "Cohort: %s\n", curCo->co->name);
		fprintf(outFile, "Classes: \n");
		classes = curCo->classes;
		while(curCo->classes){
			curCl = curCo->classes->data;
			fprintf(outFile, "%s, %d, %s, %d - %d, %c\n", curCl->name, curCl->section, curCl->days, curCl->startTime, curCl->endTime, curCl->campus);
			curCo->classes = curCo->classes->next;
		}
		curCo->classes = classes;
		cohortList = cohortList->next;
	}
	//printf("printed schedule\n");
	return 0;
}

course ** getSectionsArr(node * sectList, int ct){
	course ** toRet = malloc(sizeof(course *) * (1 + ct));
	for(int i = 0; i < ct; i++){
		toRet[i] = (course *) sectList->data;
		sectList = sectList->next;
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

node * getNeededCohorts(node * cohortList, clas * cl){
	node * toRet = NULL;
	node * cohorts = cohortList;
	int i = 0;
	while(cohorts && i < cl->cohortCt){
		node * cohortReqs = ((cohortSchedule *)cohorts->data)->co->cohortReqs;
		while(cohortReqs){
			if(strcmp(((cohortReq *)cohortReqs->data)->classReq,cl->name) == 0){
				toRet = addNode(cohorts->data, toRet);
			}
			cohortReqs = cohortReqs->next;
		}
		cohorts = cohorts->next;
	}
	return toRet;
}

int tryCombination(node * classList, node * cohortList, node * orderedCl, node * orderedCo, FILE * outFile, int cohCt){
	int addedArr[cohCt];
	for(int a = 0; a < cohCt; a++){
		addedArr[a] = 0;
	}
	if(cohCt != ((clas *)classList->data)->cohortCt){
		return 0;
	}
	int oInd = 0;
	int cInd = 0;
	int offCt = 0;
	node * cur = orderedCl;
	cohortSchedule ** coh = getCohortsArr(cohortList, classList->data);
	while(cur && cur->data){
		offCt++;
		cur = cur->next;
	}
	course ** off = getSectionsArr(orderedCl, offCt);
	
	while(cInd < cohCt && oInd < offCt){
		while(oInd < offCt && (!fitsInClass(coh[cInd], off[oInd]) || !fitsInSchedule(coh[cInd], off[oInd]))){
			oInd++;
		}
		if(oInd < offCt){
			addedArr[cInd] = 1;
			coh[cInd]->classes = addNode(off[oInd], coh[cInd]->classes);
			cInd++;
			oInd = 0;
		}
	}
	if(cInd == cohCt){
		if(classList->next == NULL){
			writeSchedule(cohortList, outFile);
		}else{
			findAllSectionArrayCombos(classList->next, cohortList, NULL, outFile, ((clas *)classList->next->data)->offerings);
		}
	}
	
	
	node * toFree;
	for(int m = 0; m < cohCt; m++){
		if(coh[m] != NULL && coh[m]->classes != NULL && addedArr[m]){
			toFree = coh[m]->classes;
			coh[m]->classes = coh[m]->classes->next;
			free(toFree);
		}
	}
	free(off);
	free(coh);
	return 0;
}
