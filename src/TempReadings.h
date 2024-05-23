#pragma once
#include <string.h>
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_ADS1X15.h>
#include <vector>
#include <Constants.h>
#include <Smooth.h>

#define READING_INTERVAL 1
#define R0 1000.0F              //ptd1000
#define R1 7500.0F              //bridge
#define SH_A 3.90802E-03
#define SH_B -5.80195E-07
#define SH_C -4.27350E-12

class TempReadings
{
public:
    Adafruit_ADS1115 ads;
    Smooth mainTempAverage{20};
    Smooth probe1Average{20};
    Smooth probe2Average{20};
    void begin();
    void measureTemps();
    String things = "blahhhh";
    // std::vector<double> tempArray;
    // std::vector<double> probe1Array;
    // std::vector<double> probe2Array;
    // double tempAvg = 0;
    // double probe1Avg = 0;
    // double probe2Avg = 0;

private:
    unsigned long previousMillis = 0;
    double getTemp(Adafruit_ADS1115 &monitor, int set, int offset);
};

extern TempReadings Temp;