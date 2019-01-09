/**
 * MIT License
 * Copyright (c) 2018 Alex Markules, Jacob Kampf, Grant Farnsworth
 **/

#include "timeBetweenClasses.h"
#include "../../readClasses.h"

void splitIntoDays(_node* nd, _node* out)
{
    _node* cur = nd;
    char * days;
    while(cur != NULL)
    {
        days = (_course*)(cur->data)
        for(int i = 0 )
    }
}

int sortSchedule(_node* nd)
{
    _node *cur;
    _node* min
    _node* start = nd;
    void* swap;
    while(start->next != NULL)
    {
        cur = start->next;
        min = start;
        while(cur != NULL)
        {
            if((_course*)(cur->data)->startTime < (_course*)(min)->startTime)
            {
                min = cur;
            }
        }
        
        swap = (_course*)(min)->data;
        (_course*)(min)->data = (_course*)(start)->data;
        (_course*)(start)->data = swap;
        start = start->next;
    }
}

int timeBetweenClasses(_node* nd)
{
    _node *n = nd;
    int gapCount = 0;
    sortSchedule(n);
    _node *daySplit[5];
    splitIntoDays(n,daySplit);

    for(int i = 0; i < 5; i++)
    {
        _node *cur = daySplit[i];
        while(cur->next != NULL)
        {
            if((_course*)(cur->next->data)->startTime - (_course*)(cur->data)->endTime > 130)
                gapCount++;
            cur = cur->next;
        }
    }
    return gapCount;
}