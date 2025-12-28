#ifndef TRAFFIC_SYSTEM_API_H
#define TRAFFIC_SYSTEM_API_H

#include <iostream>
#include <string>
#include <vector>
using namespace std;

enum class LightState {
    RED,
    YELLOW,
    GREEN
};

enum class ControlMode {
    AUTO,
    MANUAL
};


struct TrafficLight {
    LightState state;
};

struct Intersection {
    string name;

    TrafficLight lights[4];   // 0:N, 1:E, 2:S, 3:W
    int greenDuration;
    int yellowDuration;

    ControlMode mode;
    int currentDirection;
    int timeRemaining;


};

// API FUNCTION

// Intersection management
void initIntersection(Intersection &i, const string &name);
void setDurations(Intersection &i, int green, int yellow);

// Automatic control
void updateAuto(Intersection &i);

// Manual control
void setManualGreen(Intersection &i, int direction);

// Utility
string lightStateToString(LightState state);
string directionToString(int dir);

// Logging
void logChange(const string &intersection,
               const string &direction,
               const string &state);


#endif