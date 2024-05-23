#pragma once
#include <string.h>
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_ADS1X15.h>
#include <vector>

class TestClass
{
public:
    Adafruit_ADS1115 ads;
    Adafruit_ADS1115 ads2;
    void localIP();
    void tempStuff();
    String things = "blahhhh";
    std::vector<double> tempArray;
    std::vector<double> probe1Array;
    std::vector<double> probe2Array;
    double tempAvg = 0;
    double probe1Avg = 0;
    double probe2Avg = 0;

private:
    unsigned long previousMillis = 0;
    double getTemp(Adafruit_ADS1115 &monitor, int set, int offset);
};

extern TestClass Test;