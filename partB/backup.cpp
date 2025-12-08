// #include "Controller.h"
// #include <iostream>
// #include <cmath>

// Controller::Controller(int target)
//     : pid(0.15, 0.01, 0.05), logger("motor_log.csv"), targetADC(target) {}

// void Controller::run()
// {
//     int loop = 0;
//     int pwm = 0;

//     while (true)
//     {
//         int adc = simulator.readADC();
//         if (adc < 0)
//         {
//             std::cout << "ADC ERROR! Simulator not running?\n";
//             break;
//         }

//         int error = targetADC - adc;
//         pwm = pid.compute(error, pwm);
//         simulator.setPWM(pwm);

//         logger.log(loop, pwm, adc, error);

//         std::cout << "====== PID CONTROL LOOP ======\n";
//         std::cout << "Target ADC: " << targetADC << "\n";
//         std::cout << "Loop      : " << loop << "\n";
//         std::cout << "ADC       : " << adc << "\n";
//         std::cout << "PWM       : " << pwm << "%\n";
//         std::cout << "Error     : " << error << "\n";
//         std::cout << "--------------------------------\n";

//         if (std::abs(error) <= 2)
//         {
//             std::cout << "Target reached!\n";
//             break;
//         }

//         loop++;
//     }
// }
