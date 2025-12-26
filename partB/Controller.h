#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "MotorSimulator.h"
#include "Logger.h"

class Controller
{
private:
    MotorSimulator sim;
    Logger logger;
    int target;
    int maxLoops;
    int tolerance;

public:
    Controller(int targetADC, int loops = 100, int tol = 2);
    void run();
};

#endif
