#include "Logger.h"

Logger::Logger(const std::string &filename)
{
    file.open(filename, std::ios::out | std::ios::trunc);
    if (file.is_open())
    {
        file << "Loop,PWM,ADC,Error\n";
    }
}

Logger::~Logger()
{
    if (file.is_open())
        file.close();
}

void Logger::log(int loop, int pwm, int adc, int error)
{
    if (!file.is_open())
        return;
    file << loop << "," << pwm << "," << adc << "," << error << "\n";
}
