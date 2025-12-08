#ifndef LOGGER_H
#define LOGGER_H

#include <fstream>
#include <string>

class Logger
{
private:
    std::ofstream file;

public:
    explicit Logger(const std::string &filename);
    ~Logger();
    void log(int loop, int pwm, int adc, int error);
};

#endif // LOGGER_H
