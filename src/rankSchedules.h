#ifndef RANKSCHEDULES_H
#define RANKSCHEDULES_H

//node is defined in "linkedList.h"
//the data field of each node will contain a classSchedule pointer (defined in findCombinations.h)
//each classSchedule struct has a linked list (node *) of course structs (defined in readClasses.h)
int rankSchedules(node * schedules);

#endif
