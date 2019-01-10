/**
 * MIT License
 * Copyright (c) 2018 Alex Markules, Jacob Kampf, Grant Farnsworth
 **/

#include "afterTime.h"
int afterTime(node* nd)
{
    int count = 0;
    node * cur = nd;
    while(cur != NULL)
    { 
        if(((course*)(cur->data))->endTime > 1900)
            count++;
    }
    return count;
}