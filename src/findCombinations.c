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
	findCombosForHeadCohort(classList, cohortList, outFile, NULL);
	fclose(outFile);
}

int findCombosForHeadCohort(node * classList, node * cohortList, FILE * outFile, node * assigned){
	cohortSchedule * cur = (cohortSchedule *) cohortList->data;
	node * needed = getClassesFromReqs(cur->co->cohortReqs, classList);
	assigned = addNode(cohortList->data, assigned);
	pickClass(classList, cohortList, outFile, assigned, needed);
	node * tf = assigned;
	assigned = assigned->next;
	free(tf);
	while(needed){
		tf = needed;
		needed = needed->next;
		free(tf);
	}
	return 0;
}

int pickClass(node * classList, node * cohortList, FILE * outFile, node * assigned, node * needed){
	node * offerings = ((clas *) needed->data)->offerings;
	while(offerings){
		((cohortSchedule *)assigned->data)->classes = addNode(offerings->data, ((cohortSchedule *)assigned->data)->classes);
		if(needed->next){
			pickClass(classList, cohortList, outFile, assigned, needed->next);
		}else{
			tryCombination(classList, cohortList, outFile, assigned);
		}
		node * tf = ((cohortSchedule *)assigned->data)->classes;
		((cohortSchedule *)assigned->data)->classes = ((cohortSchedule *)assigned->data)->classes->next;
		offerings = offerings->next;
		free(tf);
	}
	return 0;
}

node * getClassesFromReqs(node * reqs, node * classList){
	node * needed = NULL;
	node * curReq = reqs;
	node * curClass = classList;
	while(curReq){
		curClass = classList;
		while(curClass){
			if(strcmp(((clas *)curClass->data)->name, ((cohortReq *)curReq->data)->classReq) == 0){
				needed = addNode(curClass->data, needed);
				break;
			}
			curClass = curClass->next;
		}
		curReq = curReq->next;
	}
	return needed;
}

int fitsInClass(cohortReq * coh, course * sect){
	if(sect->enrolled + coh->nbrOfSeats > sect->classSize){
		return 0;
	}else{
		return 1;
	}
}

int fitsInSchedule(node * classes, course * sect){
	int start1 = sect->startTime;
	int end1 = sect->endTime;
	char campus1 = sect->campus;
	char * days1 = sect->days;
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

			if(arePair(name1,name2)){

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
	static long int counter = 0;
	node * classes;
	//fprintf(outFile, "\nSchedule:\n");
	cohortSchedule * curCo;
	course * curCl;
	while(cohortList){
		curCo = ((cohortSchedule *) cohortList->data);
		//fprintf(outFile, "Cohort: %s\n", curCo->co->name);
		//fprintf(outFile, "Classes: \n");
		classes = curCo->classes;
		while(curCo->classes){
			curCl = curCo->classes->data;
			//fprintf(outFile, "%s, %d, %s, %d - %d, %c\n", curCl->name, curCl->section, curCl->days, curCl->startTime, curCl->endTime, curCl->campus);
			curCo->classes = curCo->classes->next;
		}
		curCo->classes = classes;
		cohortList = cohortList->next;
	}
	counter++;
	if(counter % 1000 == 0){
		printf("found %ld valid schedules\n",counter);
	}
	return 0;
}

int tryCombination(node * classList, node * cohortList, FILE * outFile, node * assigned){
	//the below var is a list of course structs
	node * schedule = ((cohortSchedule *)assigned->data)->classes;
	cohortReq * coh = NULL;
	int fit = 1;
	node * classes = NULL;
	node * cohReqs = ((cohortSchedule *)assigned->data)->co->cohortReqs;
	while(schedule && fit){
		while(cohReqs){
			if(strcmp(((cohortReq *)cohReqs->data)->classReq,((course *)schedule->data)->name)==0){
				coh = (cohortReq *) cohReqs->data;
				break;
			}else{
				cohReqs = cohReqs->next;
			}
		}
		if(coh == NULL){
			fit = 0;
			break;
		}else{
			cohReqs = ((cohortSchedule *)assigned->data)->co->cohortReqs;
		}
		if(fitsInSchedule(classes, schedule->data)&&fitsInClass(coh, schedule->data)){
			classes = addNode(schedule->data,classes);
		}else{
			fit = 0;
			break;
		}
		schedule = schedule->next;
		coh = NULL;
	}
	node * tf;
	while(classes){
		tf = classes;
		classes = classes->next;
		free(tf);
	}
	//either next one in or back up based on fit
	if(fit && (cohortList->next == NULL)){
		writeSchedule(assigned, outFile);
	}
	else if(fit){
		findCombosForHeadCohort(classList,cohortList->next,outFile,assigned);
	}
	return 0;
}

int arePair(char * name1, char * name2){
	int retVal = 1;
	int i = 0;
	while(isalpha(name1[i])){
		if(name1[i]!=name2[i]){
			retVal = 0;
		}
		i++;
	}
	return retVal;
}
