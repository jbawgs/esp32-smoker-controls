#include <RelayManager.h>

void RelayManager::begin()
{
    pinMode(FAN_RELAY, OUTPUT);
    pinMode(AUGER_RELAY, OUTPUT);
    pinMode(IGNITER_RELAY, OUTPUT);
}

void RelayManager::setRelay(u_int8_t relayNum, u_int8_t setting)
{
    Serial.print("Called SETRELAY: "); Serial.print(relayNum); Serial.print(" "); Serial.println(setting);
    digitalWrite(relayNum, setting);
    if(relayNum == FAN_RELAY) fanRelayStatus = setting;
    if(relayNum == AUGER_RELAY) augerRelayStatus = setting;
    if(relayNum == IGNITER_RELAY) igniterRelayStatus = setting;
}

RelayManager Relay;