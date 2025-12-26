#include "PIDController.h"
#include <cmath> // <<< thêm dòng này để dùng std::round

PIDController::PIDController(double p, double i, double d)
    : kp(p), ki(i), kd(d), integral(0.0), prevError(0.0) {}

int PIDController::compute(int error, int currentPWM)
{
    integral += error;
    double derivative = error - prevError;
    prevError = error;

    double out = kp * error + ki * integral + kd * derivative;

    int nextPWM = currentPWM + static_cast<int>(std::round(out));

    if (nextPWM < 0)
        nextPWM = 0;
    if (nextPWM > 100)
        nextPWM = 100;

    return nextPWM;
}
