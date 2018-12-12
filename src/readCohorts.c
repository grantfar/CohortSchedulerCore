#include "readCohorts.h"

node * readCohorts(char * fname){
	node * head = NULL;
	FILE * file = fopen(fname, "r");
	char * line;
	if(file == NULL){
		printf("Failed to open cohorts file\n");
		return NULL;
	}
	line = malloc(256 * sizeof(char));
	fgets(line, 255, file);
	free(line);
	line = malloc(256 * sizeof(char));
	fgets(line, 255, file);
	do{
		head = addNode((void *)parseLine(line), head);
		free(line);
		line = malloc(256 * sizeof(char));
		line = fgets(line, 255, file);
	}while(line != NULL);
	free(line);
	fclose(file);
	return head;
}

cohortReq * parseLine(char * line){
	char * buff = malloc(strlen(line) * sizeof(char));
	int lineCt = 0;
	int buffCt = 0;
	int parmCt = 0;
	cohortReq * retVal = malloc(sizeof(cohortReq));
	while(line[lineCt] != '\0'){
		while(line[lineCt] != '\0'&& line[lineCt] != ','){
			buff[buffCt] = line[lineCt];
			buffCt++;
			lineCt++;
		}
		buff[buffCt] = '\0';
		retVal = addField(parmCt, buff, retVal);
		parmCt++;
		buffCt = 0;
		if(line[lineCt] == ','){
			lineCt++;
		}
	}
	free(buff);
	return retVal;
}

cohortReq * addField(int index, char * value, cohortReq * obj){
	if(index == 0){
		obj->name = malloc((2 + strlen(value)) * sizeof(char));
		strcpy(obj->name, value);
	}else if(index == 1){
		obj->classReq = malloc((2 + strlen(value)) * sizeof(char));
		strcpy(obj->classReq, value);
	}else if(index == 2){
		obj->nbrOfSeats = atoi(value);
	}
	return obj;
}

node * sortCohorts(node * cohortReqs){
	char ** unique;
	node * cur = cohortReqs;
	node * toRet = NULL;
	int i = 0;
	int j = 0;
	while(cur != NULL){
		i++;
		cur = cur->next;
	}
	cur = cohortReqs;
	unique = malloc((1 + i) * sizeof(char *));
	*unique = 0;
	i = 0;
	while(cur != NULL){
		if(!arrContains(unique, ((cohortReq *)cur->data)->name)){
			unique[i] = ((cohortReq *)cur->data)->name;
			i++;
			unique[i] = NULL;
		}
		cur = cur->next;
	}
	for(j=0;j<i;j++){
		toRet = addNode(gatherReqs(unique[j], cohortReqs),toRet);
	}
	return toRet;
}

int arrContains(char ** arr, char * name){
	int i = 0;
	while(arr[i]!=NULL){
		if(strcmp(arr[i], name)==0){
			return 1;
		}
		i++;
	}
	return 0;
}

cohort * gatherReqs(char * name, node * cohortReqs){
	node * cur = cohortReqs;
	cohort * toRet = malloc(sizeof(cohort));
	toRet->name = name;
	toRet->reqCt = 0;
	toRet->cohortReqs = NULL;
	while(cur != NULL){
		if(strcmp(((cohortReq *)cur->data)->name,name)==0){
			toRet->cohortReqs = addNode(cur->data, toRet->cohortReqs);
		}
		cur = cur->next;
		toRet->reqCt++;
	}
	return toRet;
}
