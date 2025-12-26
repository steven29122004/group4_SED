#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <fstream>

class Logger
{
private:
    std::ofstream file;

public:
    Logger(const std::string &filename);
    ~Logger();
    void log(int loop, int pwm, int adc, int error);
};

#endif
