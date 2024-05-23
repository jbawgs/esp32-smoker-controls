#pragma once
#include <ArduinoJson.h>
#include <WiFi.h>
// #include <WiFiClientSecure.h>
#include <AsyncTCP.h>
// #include <ESPAsyncWebServer.h>
#include <PubSubClient.h>
#include <Constants.h>

// #include <AsyncElegantOTA.h>

#define SSID "redacted"
#define PASSWORD "redacted"

class WebManager
{
public:
    const char *mqtt_server = "redacted";
    // WiFiClientSecure espClient;
    WiFiClient espClient;
    PubSubClient client{espClient};
    unsigned long lastMsg = 0;
    unsigned long lastConnectionCheck = 0;
    // char msg[50];
    // int value = 0;
    // AsyncWebServer server{80};
    static void callback(char* topic, byte* message, unsigned int length);
    void reconnect();
    void begin();
    void doWebStuff();
};

extern WebManager Web;