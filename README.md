This is my esp32 smoker controller firmware and kicad drawings for the pcb.
It works, I used it all last summer, if you define "works" very loosely. I cooked the display and didn't care to replace it (and never finished its code) as I was perfectly fine using MQTT to control it, and also use that MQTT feed to populate a database for reporting purposes, which is not in the files here because I can't get into the ec2 instance it was hosted on atm ¯\_(ツ)_/¯ 
If a crazy person were to build this mess, i used an app on android called IOT MQTT Panel Pro to control everything remotely

Despite sucking at cpp, this thing was stable as a rock and held temps withing 3 degrees of target on my giant vertical smoker for days at a time, at least as soon as I realized I should move the tangle of ribbon cables away from the 120vac lines at the relay. As soon as it was usable I stopped development because I was tired boss, so its a mess. But maybe something of interest to see in there. My first swing at any hardware development as well as CPP, I was pretty proud at the time.
Anywhere you see the word "redacted" I pulled out a hard-coded password, key or SSID of some kind lmao

parts are a 30 pin ESP32, ads1115, 4 channel relay board, a 5v psu, capacitor for smoothing power into the ads board, assorted resistors for the voltage divider for temp probes, pt1000 temp probes, a crapload of headers, two miles of wires, a mini12864 3d printer display like this one:

https://www.amazon.com/gp/product/B09BKY5K84/ref=ppx_yo_dt_b_search_asin_title?ie=UTF8&psc=1

Combo rotary encoder! you can see how everything is wired up in the kicad schematic except for the display, I made a custom ribbon cable for that as the pin headers on that board are a wreck imo (not an expert) but you can see the pinouts here:

https://www.bjonnh.net/article/20221126_mini_12864/

Main control loop inspired by Dan Borello on his pismoker project, awesome

Libraries:

	https://github.com/me-no-dev/ESPAsyncWebServer.git
	ayushsharma82/AsyncElegantOTA@^2.2.7
	adafruit/Adafruit ADS1X15@^2.4.0
	olikraus/U8g2@^2.34.17
	adafruit/Adafruit SSD1306@^2.5.7
	adafruit/Adafruit GFX Library@^1.11.5
	https://github.com/igorantolic/ai-esp32-rotary-encoder
	https://github.com/ripred/Smooth/
	adafruit/SdFat - Adafruit Fork@^2.2.1
	br3ttb/PID@^1.2.1
	knolleary/PubSubClient@^2.8
	bblanchon/ArduinoJson@^6.21.2
	adafruit/Adafruit NeoPixel@^1.11.0
