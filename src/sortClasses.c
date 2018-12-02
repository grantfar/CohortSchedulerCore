#include "sortClasses.h"

node * sortClasses(node * cohortList, node * classList){
	node * cList = arrangeClasses(cohortList, classList);
	node * cur = cList;
	node * best = NULL;
	node * before = NULL;
	node * final = NULL;
	best = cur;
	while(cList){
		cur = cList;
		best = cur;
		while(cur->next){
			if(((clas *)cur->next->data)->cohortCt < ((clas *)best->data)->cohortCt){
				best = cur->next;
				before = cur;
			}
			cur = cur->next;
		}
		final = addNode(best->data,final);
		if(before != NULL){
			before->next = best->next;
		}else{
			cList = best->next;
		}
		before = NULL;
	}
	return final;
}

node * arrangeClasses(node * cohortList, node * classList){
	//find unique class names, call gatherOfferings for each
	char ** unique;
	node * toRet = NULL;
	int i = 0;
	node * cur = classList;
	while(cur){
		i++;
		cur = cur->next;
	}
	unique = malloc((i+1)* sizeof(char *));
	*unique = NULL;
	cur = classList;
	i = 0;
	while(cur){
		if(!arrContains(unique, ((course *)cur->data)->name)){
			unique[i] = ((course *)cur->data)->name;
			i++;
			unique[i] = NULL;
		}
		cur = cur->next;
	}
	for(int j = 0; j < i; j++){
		toRet = addNode(gatherOfferings(classList, unique[j], cohortList), toRet);
	}
	return toRet;
}

clas * gatherOfferings(node * classList, char * className, node * cohortList){
	clas * cl = malloc(sizeof(clas));
	cl->name = className;
	cl->cohortCt = 0;
	cl->offeringCt = 0;
	cl->cohorts = NULL;
	cl->offerings = NULL;

	while(classList != NULL){
		if(strcmp(((course *)classList->data)->name, className)==0){
			cl->offerings = addNode(classList->data, cl->offerings);
			cl->offeringCt++;
		}		
		classList = classList->next;
	}
	return gatherCohorts(cl, cohortList);

}

clas * gatherCohorts(clas * cl, node * cohortList){
	//for each cohort, if class is needed, add to cl->cohorts
	while(cohortList !=NULL){
		if(needsClass(((cohort *)cohortList->data)->cohortReqs, cl->name)){
			cl->cohorts = addNode((cohort *)cohortList->data, cl->cohorts);
			cl->cohortCt++;
		}
		cohortList = cohortList->next;
	}
	return cl;
}

int needsClass(node * cohortReqs, char * name){
	while(cohortReqs != NULL){
		if(strcmp(((cohortReq *)cohortReqs->data)->classReq, name)==0){
			return 1;
		}
		cohortReqs = cohortReqs->next;
	}
	return 0;
}