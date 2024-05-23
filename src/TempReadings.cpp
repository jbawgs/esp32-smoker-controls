#include <TempReadings.h>

void TempReadings::begin()
{
  while (!ads.begin(0x48))
  {
    Serial.println("Failed to initialize ADS1.");
    // while (1)
    delay(500);
  }
  ads.setDataRate(RATE_ADS1115_250SPS);
  ads.setGain(GAIN_TWOTHIRDS);
  // Temp.ads.setGain(GAIN_TWO);

  // if (!ads2.begin(0x4A))
  // {
  //   Serial.println("Failed to initialize ADS2.");
  //   while (1)
  //     ;
  // }
  // ads2.setDataRate(RATE_ADS1115_250SPS);
}

void TempReadings::measureTemps()
{

  mainTempAverage.add(getTemp(ads, 1, Consts.mainProbeOffset));
  // delay(10);
  // Serial.println("get temp 1");
  probe1Average.add(getTemp(ads, 2, Consts.probe1Offset));
  // delay(10);
  // Serial.println("get temp 2");
  probe2Average.add(getTemp(ads, 3, Consts.probe2Offset));
  Consts.Temp1Avg = mainTempAverage.get_avg();
  Consts.Probe1Avg = probe1Average.get_avg();
  Consts.Probe2Avg = probe2Average.get_avg();

  unsigned long currentMillis = millis();

  if (currentMillis - this->previousMillis >= READING_INTERVAL)
  {
    // Serial.println("get main temp");

    previousMillis = currentMillis;
  }
}

double TempReadings::getTemp(Adafruit_ADS1115 &monitor, int set, int offset)
{
  // Serial.print("Getting Temp ");Serial.print(set);Serial.println(offset);
  int16_t adc0, adc1;
  double volts0, volts1, volts2, volts3;

  if (set == 1)
  {
    adc0 = monitor.readADC_SingleEnded(0);
    adc1 = monitor.readADC_SingleEnded(1);
  }
  else if (set == 2)
  {
    adc0 = monitor.readADC_SingleEnded(0);
    adc1 = monitor.readADC_SingleEnded(2);
  }
  else if (set == 3)
  {
    adc0 = monitor.readADC_SingleEnded(0);
    adc1 = monitor.readADC_SingleEnded(3);
  }

  Serial.print("adc0: ");Serial.print(adc0);Serial.print(" adc1: ");Serial.println(adc1);
  volts0 = monitor.computeVolts(adc0);
  volts1 = monitor.computeVolts(adc1);
  Serial.print("volts0: ");Serial.print(volts0); Serial.print(" volts1: ");Serial.println(volts1);
  double resistance = 0;
  if (volts0 != 0 && volts1 != 0)
  {
    resistance = Consts.resistance * (1.0F / ((volts0 / volts1) - 1.0F));
  }
  resistance -= offset;
  Serial.print("resistance: ");Serial.println(resistance);

  double t = 0;
  double tempF = 0;
  if (resistance - R0 != 0 && R0 != 0)
  {
    t = (resistance - R0) / (R0 * 0.00385);
    tempF = (t * (9.0F / 5.0F)) + 32.0F;
  }

  // Serial.print("Temp is: ");Serial.println(tempF);
  return tempF;
}

TempReadings Temp;