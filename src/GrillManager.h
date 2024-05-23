#pragma once
#include <RelayManager.h>
#include <PIDManager.h>
#include <Mode.h>
#include <Constants.h>
// #include <algorithm>

#define STARTUP_TIME 60
#define U_MIN 0.15
#define U_MAX 0.85
#define IGNITER_TEMP 100
#define IGNITER_TIMEOUT 360
#define SHUTDOWN_TIME 600
#define DEBUG_SWITCH 6000

#define STARTUP_MODE 0
#define SMOKE_MODE 1
#define IGNITE_MODE 2
#define HOLD_MODE 3
#define SHUTDOWN_MODE 4
#define OFF_MODE -1
// Parameters = {'mode': 'Off', 'target':225, 'PB': 60.0, 'Ti': 180.0,
//'Td': 45.0, 'CycleTime': 20, 'u': 0.15, 'PMode': 2.0, 'program': False, 'ProgramToggle': time.time()}  #60,180,45 held +- 5F
class GrillManager
{
public:
    // double pidOutput;
    // double currentTemp;
    Mode currentMode;

    // int grillMode = 0;
    // float target = 0;
    float cycleTime = 20;
    double u = 0.15;
    float pMode = 2;
    bool fanOn;
    bool augerOn;
    bool igniterOn;
    unsigned long augerChangeTime = 0;
    unsigned long fanChangeTime = 0;
    unsigned long igniterChangeTime = 0;
    unsigned long debugChangeTime = 0;

    PIDManager pidm;
    RelayManager relay;

    GrillManager();
    void begin(double &pidOutpout, double &currentTemp);
    void setMode(int i);
    void doMode(double pidOutput, double currentTemp);
    void doAugerControl();
    void checkIgniter();
    void doControl();
    void doDebugMode();
    void setAuger(bool state);
    void setFan(bool state);
    void setIgniter(bool state);
};

extern GrillManager Grill;