#include <main.h>

void setup()
{
  Serial.begin(115200);

  strip.begin();
  strip.setBrightness(255);
  strip.setPixelColor(0, strip.Color(50, 255, 0));
  strip.setPixelColor(1, strip.Color(50, 255, 0));
  strip.setPixelColor(2, strip.Color(50, 255, 0));
  strip.show();

  // Relay.begin();

  Temp.begin();

  PIDM.begin(Consts.Temp1Avg, Consts.PIDOutput, Consts.Target);
  Serial.print("begin grill from main with: ");
  Serial.print(Consts.PIDOutput);
  Serial.print(" ");
  Serial.println(Consts.Temp1Avg);
  Grill.begin(Consts.PIDOutput, Consts.Temp1Avg);
  Display.begin();

  // Files.begin();

  Web.begin();

  Input.begin();

  delay(1000);

  // xTaskCreatePinnedToCore(
  //   connectionTaskMethod,
  //   "connectionTask",
  //   10000,
  //   NULL,
  //   0,
  //   &connectionTask,
  //   0
  // );

  esp_task_wdt_init(WDT_TIMEOUT, true); // enable panic so ESP32 restarts
  esp_task_wdt_add(NULL);               // add current thread to WDT watch
  // esp_task_wdt_add(&connectionTask);
}

void loop()
{
  Temp.measureTemps();
  // delay(10);
  // Consts.Target = ((int)round(Input.getInput(Consts.Target)));
  // Consts.Target = tempSet;
  Display.writeTemps(Consts.Temp1Avg, Consts.Probe1Avg, Consts.Probe2Avg, Consts.Target);
  PIDM.calculate();
  Grill.doMode(Consts.PIDOutput, Consts.Temp1Avg);
  Web.doWebStuff();
  // float normalizedOutput = (pidOutput - 0) / (255 - 0);
  
  // Serial.print("Input: "); Serial.print(Temp.tempAvg); Serial.print(" Output: "); Serial.print(pidOutput);Serial.print(" Normalized Output: "); Serial.print(normalizedOutput); Serial.print(" Setpoint: "); Serial.println(tempSet);
  // Serial.println(ESP.getFreeHeap());
  // Serial.println("reset watchdog");
  esp_task_wdt_reset();
}

// void connectionTaskMethod(void * parameter){
//   for(;;){
//     Web.doWebStuff(Consts.Temp1Avg, Consts.Probe1Avg, Consts.Probe2Avg, Consts.Target);
//     esp_task_wdt_reset();
//   }
// }
