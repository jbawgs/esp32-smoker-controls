#include <DisplayManager.h>

void DisplayManager::begin()
{
    if (!u8g2.begin())
    {
        Serial.println("Failed to initialize DISPLAY.");
        while (1)
            ;
    }

    u8g2.setContrast(175); // This is extremely important
    u8g2.clearBuffer();
    u8g2.firstPage();
    u8g2.setFont(u8g2_font_helvB08_tr);

    char *text = "[ BOGzRULEz ]";
    u8g2_uint_t width = u8g2.getUTF8Width(text); // calculate the pixel width of the text

    u8g2.setFontMode(0); // enable transparent mode, which is faster

    // draw the constant part of the screen
    // this will not be overwritten later
    u8g2.firstPage();
    do
    {
        u8g2.drawUTF8((128 - width) / 2, 12, text); // This part will stay constantly on the screen
    } while (u8g2.nextPage());
}

void DisplayManager::writeTemps(double &base, double &probe1, double &probe2, double &tempSet)
{
    for (int i = 0; i < 6; i++)
    {
        // draw to lines 0...23 (3*8-1)
        // draw to the upper part of the screen
        std::string temp = "TEMP: " + std::to_string((int)round(Consts.Temp1Avg));
        if (isnan(base) || base > 1000 || base < -100)
        {
            temp = "Disc.";
        }
        std::string probe1Temp = "PRB1: " + std::to_string((int)round(Consts.Probe1Avg));
        if (isnan(probe1) || probe1 > 1000 || base < -100)
        {
            probe1Temp = "Disc.";
        }
        std::string probe2Temp = "PRB2: " + std::to_string((int)round(Consts.Probe2Avg));
        if (isnan(probe2) || probe2 > 1000 || probe2 < -100)
        {
            probe2Temp = "Disc.";
        }
        std::string setTempString = std::to_string((int)round(Consts.Target));
        temp += "   SET: " + setTempString;

        // Serial.print(temp.c_str());Serial.println(probe1Temp.c_str());

        u8g2.setBufferCurrTileRow(i);
        u8g2.clearBuffer();
        u8g2.drawUTF8(10, 24, temp.c_str());
        u8g2.drawUTF8(10, 36, probe1Temp.c_str());
        u8g2.drawUTF8(10, 48, probe2Temp.c_str());

        // but write the buffer to the lower part (offset 4*8 = 32)
        u8g2.setBufferCurrTileRow(2 + i);
        u8g2.sendBuffer();
    }
}

DisplayManager Display;