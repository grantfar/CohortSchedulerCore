/**
 * MIT License
 * Copyright (c) 2018 Alex Markules, Jacob Kampf, Grant Farnsworth
 **/

#include "timeBetweenClasses.h"
#include "../../readClasses.h"

void splitIntoDays(node* nd, node** out)
{
    node* cur = nd;
    char * days;
    for(int i = 0; i<5; i++)
    {
        out[i] = NULL;
    }
    while(cur != NULL)
    {
        days = ((course*)(cur->data))->days;
        for(int i = 0; days[i] != '\0' && i < 5; i++)
        {
            if(days[i]=='M' || days[i] == 'm')
            {
                if(out[0] == NULL)
                {
                    out[0] = malloc(sizeof(node));
                    out[0]->next = NULL;
                    out[0]->data = cur->data;
                }
                else
                    addNode(cur->data,out[0]);
            }

            if(days[i]=='T' || days[i] == 't')
            {
                if(out[1] == NULL)
                {
                    out[1] = malloc(sizeof(node));
                    out[1]->next = NULL;
                    out[1]->data = cur->data;
                }
                else
                    addNode(cur->data,out[1]);
            }

            if(days[i]=='W' || days[i] == 'w')
            {
                if(out[2] == NULL)
                {
                    out[2] = malloc(sizeof(node));
                    out[2]->next = NULL;
                    out[2]->data = cur->data;
                }
                else
                    addNode(cur->data,out[2]);
            }

            if(days[i]=='R' || days[i] == 'r')
            {
                if(out[3] == NULL)
                {
                    out[3] = malloc(sizeof(node));
                    out[3]->next = NULL;
                    out[3]->data = cur->data;
                }
                else
                    addNode(cur->data,out[3]);
            }

            if(days[i]=='F' || days[i] == 'f')
            {
                if(out[4] == NULL)
                {
                    out[4] = malloc(sizeof(node));
                    out[4]->next = NULL;
                    out[4]->data = cur->data;
                }
                else
                    addNode(cur->data,out[4]);
            }
        }

        
    }
}

int sortSchedule(node* nd)
{
    node *cur;
    node* min;
    node* start = nd;
    void* swap;
    while(start->next != NULL)
    {
        cur = start->next;
        min = start;
        while(cur != NULL)
        {
            if(((course*)(cur->data))->startTime < ((course*)(min))->startTime)
            {
                min = cur;
            }
        }
        
        swap = (course*)(min)->data;
        min->data = start->data;
        start->data = swap;
        start = start->next;
    }
}

int timeBetweenClasses(node* nd)
{
    node *n = nd;
    int gapCount = 0;
    sortSchedule(n);
    node *daySplit[5];
    splitIntoDays(n,daySplit);

    for(int i = 0; i < 5; i++)
    {
        node *cur = daySplit[i];
        while(cur->next != NULL)
        {
            if(((course*)(cur->next->data))->startTime - ((course*)(cur->data))->endTime > 130)
                gapCount++;
            cur = cur->next;
        }
    }
    return gapCount;
}