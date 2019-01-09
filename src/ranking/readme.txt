/**
 * MIT License
 * Copyright (c) 2018 Alex Markules, Jacob Kampf, Grant Farnsworth
 **/

This is the folder for ranking functions.

each ranking function is registered in rankFunctions.cpp and the makefile. 
each ranking function must take a schedule memory pointer and return a int.

to register a function your write a line like this into rankFunctions.cpp

rank::Functions.push_back(
        rankFunction{
            "To Many Classes In one Day",*stackRank
        }
    );

    the first string is a desctription of the function, followed by a memory pointer to your rank Function;

this aproche is to make it easier for more ranking critera to be added later.

rank::rankSchedules is runs all the registered rankFunctions on the schedule and adds them togather;