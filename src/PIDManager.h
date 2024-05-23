#pragma once
#include <PID_v1.h>
#include <math.h>
#include <Arduino.h>
#include <Constants.h>

#define CALUCLATE_INTERVAL 20000

class PIDManager
{
public:
    double Setpoint, Input, Output;
    // double aggKp = 4, aggKi = 0.2, aggKd = 1;
    // double consKp = 1.5, consKi = 0.2, consKd = 0.5;
    PIDManager();
    PID myPID;
    void begin(double &input, double &output, double &setpoint);
    float calculate();
    private:
    unsigned long previousMillis = 0;
};

extern PIDManager PIDM;