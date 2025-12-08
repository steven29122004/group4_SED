#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "MotorSimulator.h"
#include "PIDController.h"
#include "Logger.h"

class Controller
{
private:
    MotorSimulator simulator;
    PIDController pid;
    Logger logger;
    int targetADC;

public:
    explicit Controller(int target);
    void run();
};

#endif // CONTROLLER_H
