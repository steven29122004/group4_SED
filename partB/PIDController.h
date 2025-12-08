#ifndef PID_CONTROLLER_H
#define PID_CONTROLLER_H

class PIDController
{
private:
    double kp, ki, kd;
    double integral;
    double prevError;

public:
    PIDController(double p = 0.15, double i = 0.01, double d = 0.05);
    // compute new pwm given error and current pwm
    int compute(int error, int currentPWM);
};

#endif // PID_CONTROLLER_H
