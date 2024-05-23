#pragma once
#include <U8g2lib.h>
#include <Constants.h>
#define LCD_RESET 33 // LCD reset, sometimes called RST or RSTB
#define LCD_CS 5     // LCD CS, sometimes called EN or SS
#define LCD_RS 27    // LCD RS, sometimes called A0 or DC

class DisplayManager
{
public:
    U8G2_ST7567_JLX12864_1_4W_HW_SPI u8g2{U8G2_R2,
                                      LCD_CS,
                                      LCD_RS,
                                      LCD_RESET};
    // U8G2_ST7567_JLX12864_1_4W_SW_SPI u8g2_lcd(U8G2_R0, 1,1,1,1,U8X8_PIN_NONE);
    void begin();
    void writeTemps(double &base, double &probe1, double &probe2, double &tempSet);
};

extern DisplayManager Display;