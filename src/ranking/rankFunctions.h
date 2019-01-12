/**
 * MIT License
 * Copyright (c) 2018 Alex Markules, Jacob Kampf, Grant Farnsworth
 **/


#ifndef RANKFUNK
#define RANKFUNK
#define FUNKCOUNT 3
#include "../linkedList.h"

typedef int (*rankFunction)(node *nd);

rankFunction functions[FUNKCOUNT];

void initRankFunctions();
#endif