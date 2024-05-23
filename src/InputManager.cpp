#include <InputManager.h>

InputManager::InputManager()
{
    // Rotary_Encoder = rotaryEncoder;
}

void IRAM_ATTR readEncoderISR()
{
    Input.rotaryEncoder->readEncoder_ISR();
}

void InputManager::begin()
{
  pinMode(ROTARY_ENCODER_A_PIN, INPUT_PULLUP);
  pinMode(ROTARY_ENCODER_B_PIN, INPUT_PULLUP);
  pinMode(ROTARY_ENCODER_BUTTON_PIN, INPUT_PULLUP);
  // pinMode(BUTTON_PIN, INPUT_PULLUP);

    rotaryEncoder->begin();
    rotaryEncoder->setup(readEncoderISR);
    numberSelector.attachEncoder(rotaryEncoder);
    numberSelector.setRange(0.0, 500.0, 1, false, 0);
    numberSelector.setValue(Consts.Target);
}

float InputManager::getFrequency()
{
  return (float)rotaryEncoder->readEncoder();
}

void InputManager::rotary_onButtonClick()
{
  static unsigned long lastTimePressed = 0;
  if (millis() - lastTimePressed < 200)
    return;
  lastTimePressed = millis();

  Serial.print("BUTTON CLICK! ");
  Serial.print(getFrequency());
  // Serial.println(" MHz ");
}

float InputManager::getInput(int tempSet)
{
    float input = (float)tempSet;
    if (rotaryEncoder->encoderChanged())
    {
        input = numberSelector.getValue();
        // Serial.print(tempSet, 1);
        Serial.println(" ENCODER TURNED! ");
    }
    if (rotaryEncoder->isEncoderButtonClicked())
    {
        rotary_onButtonClick();
    }

    return input;
}


InputManager Input;