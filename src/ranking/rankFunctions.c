/**
 * MIT License
 * Copyright (c) 2018 Alex Markules, Jacob Kampf, Grant Farnsworth
 **/

#include "rank.h"
#include "rankFunctions.h"
#include "afterTime/afterTime.h"
#include "moreClassesInDay/stackRank.h"
#include "timeBetweenClasses/timeBetweenClasses.h"


void initRankFunctions()
{

    functions[0] = *afterTime;

    functions[1] = *stackRank;

    functions[2] = *timeBetweenClasses;

}