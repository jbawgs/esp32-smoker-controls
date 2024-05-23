#pragma once
//#define BLYNK_DEBUG
// #define APP_DEBUG
#define NEOPIXEL_PIN 3
#define WDT_TIMEOUT 20

// #include <WiFi.h>
// #include <WiFiClient.h>

#include <esp_task_wdt.h>
#include <TempReadings.h>
// #include <RelayManager.h>
#include <WebManager.h>
#include <DisplayManager.h>
#include <InputManager.h>
#include <FileManager.h>
#include <PIDManager.h>
#include <GrillManager.h>
#include <Constants.h>

#include <Adafruit_NeoPixel.h>

char ssid[] = "boggsmesh";
char pass[] = "dudemanbro";

TaskHandle_t connectionTask;

double tempSet = 250;
double pidOutput = 0.0;
Adafruit_NeoPixel strip = Adafruit_NeoPixel{3, NEOPIXEL_PIN, NEO_GRB};

// void connectionTaskMethod(void * parameter);

