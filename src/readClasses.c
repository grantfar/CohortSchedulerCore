#include "readClasses.h"

node * readCourses(char * fname){
	node * head = NULL;
	FILE * file = fopen(fname, "r");
	char * line;
	if(file == NULL){
		printf("Failed to open classes file\n");
		return NULL;
	}
	line = malloc(256 * sizeof(char));
	fgets(line, 255, file);
	free(line);
	line = malloc(256 * sizeof(char));
	fgets(line, 255, file);
	do{
		head = addNode((void *)parseCourse(line), head);
		free(line);
		line = malloc(256 * sizeof(char));
		line = fgets(line, 255, file);
	}while(line != NULL);
	free(line);
	fclose(file);
	return head;
}
//takes in a line of the csv file and returns a course struct with that info
course * parseCourse(char * line){
	course * toRet = malloc(sizeof(course));
	char * buff = malloc(strlen(line) * sizeof(char));
	int lineCt = 0;
	int buffCt = 0;
	int parmCt = 0;
	while(line[lineCt]!= '\n' && line[lineCt] != '\0' && line[lineCt] != EOF){
		while(line[lineCt] != ',' && line[lineCt] != '\n' && line[lineCt] != '\0' && line[lineCt] != EOF){
			buff[buffCt] = line[lineCt];
			buffCt++;
			lineCt++;
		}
		buff[buffCt] = '\0';
		addParam(parmCt, buff, toRet);
		parmCt++;
		buffCt = 0;
		if(line[lineCt]== ','){
			lineCt++;
		}
	}
	free(buff);
	return toRet;
}
//adds value to obj at the element specified by index
void addParam(int index, char * value, course * obj){
	if(index == 0){
		obj->name = malloc((2+strlen(value)) *sizeof(char));
		strcpy(obj->name, value);
	}else if(index == 1){
		obj->section = atoi(value);
	}else if(index == 2){
		obj->days = malloc((2+strlen(value)) *sizeof(char));
		strcpy(obj->days, value);
	}else if(index == 3){
		obj->startTime = atoi(value);
	}else if(index == 4){
		obj->endTime = atoi(value);
	}else if(index == 5){
		obj->campus = value[0];
	}else if(index == 6){
		obj->classSize = atoi(value);
		obj->enrolled = 0;
	}
}