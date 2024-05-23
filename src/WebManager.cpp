#include <WebManager.h>

void WebManager::begin()
{
    WiFi.mode(WIFI_STA);
    WiFi.begin(SSID, PASSWORD);
    Serial.println("");

    // Wait for connection
    for (int i = 0; i < 5; i++)
    {
        if (WiFi.status() != WL_CONNECTED)
        {
            delay(500);
            Serial.print(".");
        } else {
            continue;
        }
    }

    Serial.println("");
    Serial.print("Connected to ");
    Serial.println(SSID);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());

    // server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
    //           { request->send(200, "text/plain", "Hi! I am ESP32."); });

    // // AsyncElegantOTA.begin(&server); // Start ElegantOTA
    // server.begin();
    // Serial.println("HTTP server started");

    // client.setClient(espClient);
    client.setServer(mqtt_server, 1883);
    // client.setCallback(std::bind(&WebManager::callback, this, 1));
    client.setCallback(this->callback);

    reconnect();
}

void WebManager::doWebStuff()
{
    // Serial.println("doWebStuff()");
    if (millis() - lastConnectionCheck > 20000)
    {
        if(!client.connected()){
            reconnect();
            lastConnectionCheck = millis();
        }
    }

    client.loop();

    long now = millis();
    if (now - lastMsg > 5000)
    {
        Serial.println("sending MQTT");
        lastMsg = now;

        double temperature = 123.321;
        StaticJsonDocument<1024> doc;

        doc["st"] = Consts.Temp1Avg;
        doc["p1"] = Consts.Probe1Avg;
        doc["p2"] = Consts.Probe2Avg;
        doc["t"] = Consts.Target;
        doc["cn"] = Consts.CookName + std::to_string(millis());
        doc["kp"] = Consts.ConservativeKP;
        doc["ki"] = Consts.ConservativeKI;
        doc["kd"] = Consts.ConservativeKD;
        doc["aO"] = Consts.augerOn;
        doc["fO"] = Consts.fanOn;
        doc["iO"] = Consts.igniterOn;
        doc["u"] = Consts.U;
        doc["m"] = ESP.getFreeHeap();
        doc["ut"] = millis() / 1000;
        doc["r0"] = Consts.resistance;
        doc["mo"] = Consts.mainProbeOffset;
        doc["p1o"] = Consts.probe1Offset;
        doc["p2o"] = Consts.probe2Offset;

        std::string output;
        serializeJson(doc, output);
        // Serial.println(output.c_str());
        // Serial.println(jsonData.c_str());
        // dtostrf(temperature, 1, 2, tempString);
        // Serial.print("Temperature: ");
        // Serial.println(tempString);
        client.publish("esp32/temperature", output.c_str());
    }
}

void WebManager::reconnect()
{
    Serial.println("reconnect()");
    // Loop until we're reconnected
    if (WiFi.status() != WL_CONNECTED)
    {
        Serial.println("WiFI disconnected");
        WiFi.disconnect();
        WiFi.begin(SSID, PASSWORD);
        // delay(500);
        Serial.print(".");
    }
    if (!client.connected())
    {
        Serial.print("Attempting MQTT connection...");
        // Attempt to connect
        if (client.connect("controller_r1"))
        {
            Serial.println("connected");
            // Subscribe
            client.subscribe("esp32/options/#");
            client.subscribe("esp32/mode");
            client.subscribe("esp32/tempsetting");
            client.subscribe("esp32/pidparams/#");
            client.subscribe("esp32/cookname");
        }
        else
        {
            Serial.print("failed, rc=");
            Serial.print(client.state());
            Serial.println(" try again in 4 seconds");
            // Wait 5 seconds before retrying
            // delay(5000);
        }
    }
}

void WebManager::callback(char *topic, byte *message, unsigned int length)
{
    Serial.print("Message arrived on topic: ");
    Serial.print(topic);
    Serial.print(". Message: ");
    String messageTemp;

    for (int i = 0; i < length; i++)
    {
        Serial.print((char)message[i]);
        messageTemp += (char)message[i];
    }
    Serial.println();

    if (strcmp(topic, "esp32/options/r0") == 0)
    {
        Serial.println("options message");
        Consts.resistance = atof(messageTemp.c_str());
    }
    if (strcmp(topic, "esp32/options/mo") == 0)
    {
        Serial.println("options message");
        Consts.mainProbeOffset = atof(messageTemp.c_str());
    }
    if (strcmp(topic, "esp32/options/p1o") == 0)
    {
        Serial.println("options message");
        Consts.probe1Offset = atof(messageTemp.c_str());
    }
    if (strcmp(topic, "esp32/options/p2o") == 0)
    {
        Serial.println("options message");
        Consts.probe2Offset = atof(messageTemp.c_str());
    }
    if (strcmp(topic, "esp32/tempsetting") == 0)
    {
        Serial.println("setting target");
        Consts.Target = atof(messageTemp.c_str());
        Serial.println(Consts.Target);
    }
    if (strcmp(topic, "esp32/pidparams/ki") == 0)
    {
        Serial.println("pidparams message");
        Consts.ConservativeKI = atof(messageTemp.c_str());
    }
    if (strcmp(topic, "esp32/pidparams/kp") == 0)
    {
        Serial.println("pidparams message");
        Consts.ConservativeKP = atof(messageTemp.c_str());
    }
    if (strcmp(topic, "esp32/pidparams/kd") == 0)
    {
        Serial.println("pidparams message");
        Consts.ConservativeKD = atof(messageTemp.c_str());
    }
    if (strcmp(topic, "esp32/cookname") == 0)
    {
        Serial.println("cookname message");
        Consts.CookName = messageTemp.c_str();
    }
    if (strcmp(topic, "esp32/mode") == 0)
    {
        Serial.println("mode message");
        Consts.GrillMode = atoi(messageTemp.c_str());
    }
}

WebManager Web;