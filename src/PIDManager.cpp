#include <PIDManager.h>

PIDManager::PIDManager() : myPID(&Input, &Output, &Setpoint, Consts.ConservativeKP, Consts.ConservativeKI, Consts.ConservativeKD, DIRECT){
    
}

void PIDManager::begin(double &input, double &output, double &setpoint)
{
    // Input = &input;
    // Output = &output;
    // Setpoint = &setpoint;
    // initialize the variables we're linked to
    // Input = analogRead(PIN_INPUT);
    myPID = PID(&Consts.Temp1Avg, &Consts.PIDOutput, &Consts.Target, Consts.ConservativeKP, Consts.ConservativeKI, Consts.ConservativeKD, DIRECT);
    // Setpoint = 100;
    // turn the PID on
    myPID.SetMode(AUTOMATIC);
}

float PIDManager::calculate()
{
    // Serial.println("PIDM.calculate()");
    unsigned long currentMillis = millis();

    if (currentMillis - previousMillis >= CALUCLATE_INTERVAL)
    {
        // Serial.println("PIDM calculate interval exceeded");
        // Serial.print("calculating pid on: "); Serial.println(Consts.Target);

        if(myPID.GetKd() != Consts.ConservativeKD || myPID.GetKi() != Consts.ConservativeKI || myPID.GetKp() != Consts.ConservativeKP){
            Serial.print("Set new tunings: ");Serial.print(Consts.ConservativeKD);Serial.print("kd  ");Serial.print(Consts.ConservativeKI);Serial.print("ki ");Serial.print(Consts.ConservativeKP);Serial.println("kp");
            myPID.SetTunings(Consts.ConservativeKP, Consts.ConservativeKI, Consts.ConservativeKD);
        }

        myPID.Compute();
        
        previousMillis = millis();
    }
    // Serial.print("pidOutputFromCalc");Serial.println(Output);
    return Output;
}

PIDManager PIDM;