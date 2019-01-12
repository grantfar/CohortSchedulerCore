/**
 * MIT License
 * Copyright (c) 2018 Alex Markules, Jacob Kampf, Grant Farnsworth
 **/

#include "stackRank.h"
#include "../../readClasses.h"
int score(int toScore)
{
    if(toScore <=2)
        return 0;
    if(toScore == 3)
        return 2;
    if(toScore == 4)
        return 7;
    return 99;
}


int stackRank(node* nd)
{
    int dayRanks[5];
    node* n = nd;
    for(int i = 0; i<5; i++)
    {
        dayRanks[i] = 0;
    }

    while(n != NULL)
    {
        course* tmp = (course *)(n->data);
        for(int i = 0; tmp->days[i]!= '\0' && i < 5; i++)
        {
            if(tmp->days[i] == 'm' || tmp->days[i] == 'M')
                dayRanks[0] ++;
            if(tmp->days[i] == 't' || tmp->days[i] == 'T')
                dayRanks[1] ++;
            if(tmp->days[i] == 'w' || tmp->days[i] == 'W')
                dayRanks[2] ++;
            if(tmp->days[i] == 'r' || tmp->days[i] == 'R')
                dayRanks[3] ++;
            if(tmp->days[i] == 'f' || tmp->days[i] == 'F')
                dayRanks[4] ++;
        }
    }

    return score(dayRanks[0]) + score(dayRanks[1]) + score(dayRanks[2]) + score(dayRanks[3]) + score(dayRanks[4]);
}


