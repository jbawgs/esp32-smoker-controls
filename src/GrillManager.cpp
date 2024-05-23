#include <GrillManager.h>

GrillManager::GrillManager()
{
    // pidOutput = 0;
    // currentTemp = 0;
}

void GrillManager::begin(double &pidOutput, double &currentTemp)
{
    Serial.println("GRILL BEGIN!");
    // this->pidOutput = pidOutput;
    // this->currentTemp = currentTemp;
    Serial.print("begin grill on self with: ");
    Serial.print(pidOutput);
    Serial.print(" ");
    Serial.println(currentTemp);

    Relay.begin();
    delay(10);
    Relay.setRelay(FAN_RELAY, LOW);
    Relay.setRelay(IGNITER_RELAY, LOW);
    Relay.setRelay(AUGER_RELAY, LOW);
    setMode(STARTUP_MODE);
}

void GrillManager::setMode(int i)
{
    // Serial.print("SettingMode: ");
    // Serial.println(i);
    Consts.GrillMode = i;

    Mode nextMode;

    if (i == 0)
    {
        nextMode = ModeSelect.Startup;
    }
    else if (i == 1)
    {
        nextMode = ModeSelect.Smoke;
    }
    else if (i == 2)
    {
        nextMode = ModeSelect.Ignite;
    }
    else if (i == 3)
    {
        nextMode = ModeSelect.Hold;
    }
    else if (i == 4)
    {
        nextMode = ModeSelect.Shutdown;
    }
    else if(i == 97){
        nextMode = ModeSelect.DebugFan;
    }
    else if(i == 98){
        nextMode = ModeSelect.DebugAuger;
    }
    else if(i == 99){
        nextMode = ModeSelect.DebugIgniter;
    }
    else if(i == 100){
        nextMode = ModeSelect.DebugAll;
    }
    else
    {
        nextMode = ModeSelect.Off;
    }

    if (currentMode.Name == nextMode.Name)
    {
        // Serial.println("mode is the same !");
        return;
    }

    // Serial.print("Mode CHANGED: ");
    Serial.println(nextMode.Name);
    currentMode = nextMode;
    setFan(currentMode.fanOn);
    setAuger(currentMode.augerOn);
    setIgniter(currentMode.igniterOn);
    cycleTime = currentMode.cycleTime;
    u = currentMode.u;
}

void GrillManager::doMode(double pidOutput, double currentTemp)
{
    // Serial.println("DO MODE!");
    // Serial.print("currentTemp: "); Serial.println(*currentTemp);
    // Serial.print("pidOutput: "); Serial.println(*pidOutput);
    // this->pidOutput = pidOutput;
    // this->currentTemp = currentTemp;

    setMode(Consts.GrillMode);

    // Serial.print("set dubs to: "); Serial.print(pidOutput); Serial.print(" "); Serial.println(currentTemp);
    // Serial.print("dubs are: "); Serial.print(this->pidOutput); Serial.print(" "); Serial.println(this->currentTemp);
    if (currentMode.Name == "Off")
    {
        // Serial.println("OFF");
        return;
    }
    else if (currentMode.Name == "Shutdown mode")
    {
        // Serial.println("Shutdown");
        if (millis() - fanChangeTime > SHUTDOWN_TIME)
        {
            setMode(OFF_MODE);
        }
    }
    else if (currentMode.Name == "Startup")
    {
        // Serial.println("Startup mode");
        doAugerControl();
        // setIgniter(true);

        if (currentTemp > 115)
        {
            setMode(HOLD_MODE);
        }
    }
    else if (currentMode.Name == "Smoke")
    {
        // Serial.println("Smoke Mode");
        doAugerControl();
    }
    else if (currentMode.Name == "Ignite")
    {
        // Serial.println("Ignite Mode");
        doAugerControl();
        // setIgniter(true);
    }
    else if (currentMode.Name == "Hold")
    {
        // Serial.println("Hold Mode");
        doControl();
        doAugerControl();
    }
    else if(currentMode.Name == "DebugAll"){
        // Serial.println("DEBUG ALL Mode");
        doDebugMode();
    }
}

void GrillManager::doAugerControl()
{
    // Serial.println("DO AUGER CONTROL!");
    if (augerOn && (millis() - augerChangeTime > cycleTime * u * 1000))
    {
        Serial.print("Shutting off Auger after interval: ");
        Serial.println(cycleTime * u * 1000);
        setAuger(false);
        checkIgniter();
    }

    if (!augerOn && (millis() - augerChangeTime > cycleTime * (1 - u) * 1000))
    {
        Serial.print("Activating Auger after interval: ");
        Serial.println(cycleTime * (1 - u) * 1000);
        setAuger(true);
        checkIgniter();
    }
}

void GrillManager::checkIgniter()
{
    // Serial.print("CHECK IGNITER AND DO NOTHING: ");
    // Serial.println(Consts.Temp1Avg);
    unsigned long igniterOnTime = millis() - igniterChangeTime;
    if (Consts.Temp1Avg < IGNITER_TEMP && igniterOnTime < IGNITER_TIMEOUT * 1000)
    {
        Serial.print("currentTemp");
        Serial.print(Consts.Temp1Avg);
        Serial.print(" igniterOnTime: ");
        Serial.print(igniterOnTime);
        Serial.println("Turn On Igniter");
        setIgniter(true);
    }
    else if (Consts.Temp1Avg > IGNITER_TEMP && igniterOnTime < IGNITER_TIMEOUT * 1000)
    {
        Serial.print("currentTemp");
        Serial.print(Consts.Temp1Avg);
        Serial.print(" igniterOnTime: ");
        Serial.print(igniterOnTime);
        Serial.println("Turn OFF Igniter");
        setIgniter(false);
    }

    if (igniterOnTime > IGNITER_TIMEOUT * 1000 && igniterOn)
    {
        Serial.print("IGNITER TIME OUT! ");
        Serial.print("currentTemp");
        Serial.print(Consts.Temp1Avg);
        Serial.print(" igniterOnTime: ");
        Serial.print(igniterOnTime);
        Serial.println("Turn OFF Igniter");
        setIgniter(false);
        setMode(SHUTDOWN_MODE);
    }
}

void GrillManager::doControl()

{
    // Serial.println("DO CONTROL!");
    // *pidOutput = PIDM.calculate();

    // Serial.print("PID Setpoint: "); Serial.print(PIDM.Setpoint); Serial.print(" Input: "); Serial.print(PIDM.Input); Serial.print(" Output: ");Serial.println(PIDM.Output);
    double previousU = u;
    u = (Consts.PIDOutput - 0) / (255 - 0);
    // Serial.print("pidOUtput: "); Serial.println(Consts.PIDOutput);Serial.print(" pidUValue: ");Serial.println(u);
    // u = 0.25;
    Consts.U = u;
    if (u > U_MAX)
        u = U_MAX;
    if (u < U_MIN)
        u = U_MIN;

    // Serial.print("previous u: "); Serial.print(previousU); Serial.print(" current u: "); Serial.print(u); Serial.print(" pidOutput: "); Serial.println(Consts.PIDOutput);

    if (u != previousU)
    {
        // Serial.print("pid output! changed doControl(): ");
        // Serial.println(u);
    }
}

void GrillManager::doDebugMode(){
    // Serial.println("doDebugMode");
    if(millis() - debugChangeTime > DEBUG_SWITCH){
        debugChangeTime = millis();
        setAuger(!augerOn);
        setFan(!fanOn);
        setIgniter(!igniterOn);
    }
}

void GrillManager::setAuger(bool state)
{
    // Serial.println("setAuger()");
    if (augerOn == state)
        return;

    augerOn = state;
    Consts.augerOn = augerOn;
    if (state == true)
    {
        // Serial.println("setting auger relay on/low");
        Relay.setRelay(AUGER_RELAY, LOW);
    }
    else
    {
        // Serial.println("setting auger relay off/high");
        Relay.setRelay(AUGER_RELAY, HIGH);
    }
    augerChangeTime = millis();
    Serial.print("Setting Auger To: ");
    Serial.println(augerOn);
}

void GrillManager::setFan(bool state)
{
    // Serial.println("setFan()");
    if (fanOn == state)
        return;

    fanOn = state;
    Consts.fanOn = fanOn;
    if (state == true)
    {
        Relay.setRelay(FAN_RELAY, LOW);
    }
    else
    {
        Relay.setRelay(FAN_RELAY, HIGH);
    }
    fanChangeTime = millis();
    Serial.print("Setting Fan To: ");
    Serial.println(fanOn);
}

void GrillManager::setIgniter(bool state)
{
    // Serial.println("setIgniter");
    if (igniterOn == state)
        return;

    igniterOn = state;
    Consts.igniterOn = igniterOn;

    if (state == true)
    {
        Relay.setRelay(IGNITER_RELAY, LOW);
    }
    else
    {
        Relay.setRelay(IGNITER_RELAY, HIGH);
    }
    igniterChangeTime = millis();
    Serial.print("Setting Igniter To: ");
    Serial.println(igniterOn);
}

GrillManager Grill;