#ifndef READCLASSES_H
#define READCLASSES_H
#include "linkedList.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _course{
	char * name;
	int section;
	char * days;
	int startTime;
	int endTime;
	char campus;
	int classSize;
	int enrolled;
} course;

node * readCourses(char * file);

course * parseCourse(char * line);

void addParam(int index, char * value, course * obj);

#endif