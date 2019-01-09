/**
 * MIT License
 * Copyright (c) 2018 Alex Markules, Jacob Kampf, Grant Farnsworth
 **/

#include "timeBetweenClasses.h"
#include "../../readClasses.h"

void splitIntoDays(node* nd, vector<courseSection*>* days)
{
    for(int i = 0; i< s->getCourseCount(); i++)
    {
        for(int j = 0; j < 5; j++)
        {
            if(s->getEnrollments()[i]->OnDay(j))
            {
                days[j].push_back(s->getEnrollments()[i]);
            }
        }
    }
}

int sortSchedule(node* nd)
{

}

int timeBetweenClasses(node* nd)
{
    node *n = nd;
    int gapCount = 0;
    s->sortSchedule();
    vector<courseSection*> daySplit[5];
    splitIntoDays(s,daySplit);

    for(int i = 0; i < 5; i++)
    {
        for(int j = 0; j < daySplit[i].size() - 1; j++)
        {
            if(daySplit[i][j+1]->getStartTime() - daySplit[i][j]->getEndTime() >= 130)
                gapCount++;
        }
    }
    return gapCount;
}