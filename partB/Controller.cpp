#include "Controller.h"
#include <iostream>
#include <cmath>
#include <thread>
#include <chrono>

Controller::Controller(int targetADC, int loops, int tol)
    : target(targetADC), maxLoops(loops), tolerance(tol), sim(), logger("motor_log.csv")
{
}

void Controller::run()
{
    std::cout << "Starting feedback control...\n";
    int pwm = 50;
    sim.setPWM(pwm);

    for (int i = 1; i <= maxLoops; i++)
    {
        int adc = sim.readADC();
        int error = target - adc;

        if (error > tolerance)
            pwm += 1;
        else if (error < -tolerance)
            pwm -= 1;

        if (pwm > 100)
            pwm = 100;
        if (pwm < 0)
            pwm = 0;

        sim.setPWM(pwm);

        logger.log(i, pwm, adc, error);

        std::cout << "[Loop " << i << "] "
                  << "PWM=" << pwm << "%, "
                  << "ADC=" << adc << ", "
                  << "Error=" << error << "\n";

        if (std::abs(error) <= tolerance)
        {
            std::cout << "Target reached! Final PWM = " << pwm << "%\n";
            break;
        }


        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

    std::cout << "Control loop finished. Log saved to motor_log.csv\n";
}
