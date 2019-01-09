/**
 * MIT License
 * Copyright (c) 2018 Alex Markules, Jacob Kampf, Grant Farnsworth
 **/

#include "rank.h"
#include "rankFunctions.h"
int rankSchedule(node* nd)
{
    int rankVal = 0;
    for(int i = 0; i < FUNKCOUNT; i++)
    {
        rankVal += functions[i](nd);
    }
    return rankVal;
}

void initRank()
{
    initRankFunctions();
}