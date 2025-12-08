#include "Controller.h"
#include <iostream>
#include <cmath>
#include <thread>
#include <chrono>

Controller::Controller(int target)
    : simulator(), pid(0.15, 0.01, 0.05), logger("motor_log.csv"), targetADC(target) {}

void Controller::run()
{
    int loop = 0;
    int pwm = 0;

    // initial pwm
    simulator.setPWM(pwm);

    while (true)
    {
        int adc = simulator.readADC();
        if (adc < 0)
        {
            std::cerr << "ADC read error\n";
            break;
        }

        int error = targetADC - adc;
        pwm = pid.compute(error, pwm);

        // ensure clamp (redundant but safe)
        if (pwm < 0)
            pwm = 0;
        if (pwm > 100)
            pwm = 100;

        simulator.setPWM(pwm);

        // log
        logger.log(loop, pwm, adc, error);

        // realtime one-line display
        std::cout << "[" << loop << "] PWM=" << pwm << "%, ADC=" << adc << ", Error=" << error << std::endl;

        // std::cout << "====== PID CONTROL LOOP ======\n";
        // std::cout << "Target ADC: " << targetADC << "\n";
        // std::cout << "Loop      : " << loop << "\n";
        // std::cout << "ADC       : " << adc << "\n";
        // std::cout << "PWM       : " << pwm << "%\n";
        // std::cout << "Error     : " << error << "\n";
        // std::cout << "--------------------------------\n";

        // stop condition
        if (std::abs(error) <= 2 && adc != 0)
        {
            std::cout << "Target reached!\n";
            break;
        }

        ++loop;
        std::this_thread::sleep_for(std::chrono::milliseconds(150));
    }
}
