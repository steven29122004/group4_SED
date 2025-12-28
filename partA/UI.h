#ifndef UI_H
#define UI_H

#include <vector>
#include "TrafficSystemAPI.h"
#include "Users.h"

struct SystemData {
    vector<Intersection> intersections;
    vector<int> assignedOp; 
};

void runUI(SystemData& data);

#endif

