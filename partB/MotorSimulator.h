#ifndef MOTOR_SIMULATOR_H
#define MOTOR_SIMULATOR_H

class MotorSimulator
{
private:
    int pwm; // 0..100
public:
    MotorSimulator();
    void setPWM(int duty);
    int readADC();
};

#endif // MOTOR_SIMULATOR_H
