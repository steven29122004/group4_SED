#include <iostream>
#include "TrafficSystemAPI.h"
#include <fstream>
#include <ctime>
using namespace std;

// ===== INITIALIZATION =====
void initIntersection(Intersection &i, const string &name) {
    i.name = name;
    i.greenDuration = 20;
    i.yellowDuration = 3;
    i.mode = ControlMode::AUTO;
    i.currentDirection = 0;
    i.timeRemaining = i.greenDuration;

    for (int d = 0; d < 4; d++) {
        i.lights[d].state = LightState::RED;
    }

    i.lights[0].state = LightState::GREEN;
}

// CONFIGURATION 
void setDurations(Intersection &i, int green, int yellow) {
    i.greenDuration = green;
    i.yellowDuration = yellow;
}

// AUTO MODE
void updateAuto(Intersection &i) {
    if (i.mode != ControlMode::AUTO)
        return;
    i.timeRemaining--;

    if (i.timeRemaining > 0)
        return;
    LightState &currentState = i.lights[i.currentDirection].state;

    if (currentState == LightState::GREEN) {
        currentState = LightState::YELLOW;
        i.timeRemaining = i.yellowDuration;

        logChange(i.name,
                  directionToString(i.currentDirection),  "YELLOW");
    }
    else if (currentState == LightState::YELLOW) {
        currentState = LightState::RED;

        i.currentDirection = (i.currentDirection + 1) % 4;
        i.lights[i.currentDirection].state = LightState::GREEN;
        i.timeRemaining = i.greenDuration;

        logChange(i.name, directionToString(i.currentDirection), "GREEN");
    }
}

// MANUAL MODE 
void setManualGreen(Intersection &i, int direction) {
    i.mode = ControlMode::MANUAL;

    for (int d = 0; d < 4; d++) {
        i.lights[d].state = LightState::RED;
    }

    i.currentDirection = direction;
    i.lights[direction].state = LightState::GREEN;
    i.timeRemaining = i.greenDuration;

    logChange(i.name, directionToString(direction), "GREEN (MANUAL)");
}

// UTILITIES 
string lightStateToString(LightState state) {
    if (state == LightState::RED) return "RED";
    if (state == LightState::YELLOW) return "YELLOW";
    return "GREEN";
}

string directionToString(int dir) {
    switch (dir) {
        case 0: 
        return "North";
        case 1:
            return "East";
        case 2:
            return "South";
        case 3:
            return "West";
        default: 
            return "Unknown";
    }
}

// LOG
void logChange(const string &intersection,
               const string &direction,
               const string &state) {

    std::ofstream file("traffic_log.txt", std::ios::app);
    if (!file) return;

    time_t now = time(nullptr);
    tm *t = localtime(&now);

    char timeStr[10];
    strftime(timeStr, sizeof(timeStr), "%H:%M:%S", t);

    file << timeStr << ", "
         << intersection << ", "
         << direction << ", "
         << state << "\n";
}