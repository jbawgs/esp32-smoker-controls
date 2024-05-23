#pragma once
#include <Arduino.h>

#define FAN_RELAY 17
#define AUGER_RELAY 16
#define IGNITER_RELAY 15

class RelayManager
{
    public:
    u_int8_t fanRelayStatus;
    u_int8_t augerRelayStatus;
    u_int8_t igniterRelayStatus;

    void begin();
    void setRelay(u_int8_t relayNum, u_int8_t setting);
};

extern RelayManager Relay;