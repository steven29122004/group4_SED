#include "MotorSimulator.h"
#include <cstdlib>
#include <ctime>

MotorSimulator::MotorSimulator()
{
    pwm = 0;
    std::srand(static_cast<unsigned>(std::time(nullptr)));
}

void MotorSimulator::setPWM(int duty)
{
    if (duty < 0)
        duty = 0;
    if (duty > 100)
        duty = 100;
    pwm = duty;
}

// Simple simulated ADC: adc = pwm*10 + noise (-10..+10), clamp 0..1023
int MotorSimulator::readADC()
{
    int noise = (std::rand() % 21) - 10;
    int adc = pwm * 10 + noise;
    if (adc < 0)
        adc = 0;
    if (adc > 1023)
        adc = 1023;
    return adc;
}
