#include <targets\AT91SAM7.h>
#include "pcf8833u8_lcd.h"

int main (){

InitLCD();
SetContrast(30);
LCDClearScreen();

LCDPutStr("Text 1", 10, 20, LARGE, BLACK, WHITE);
LCDPutStr("Text 2", 30, 20, MEDIUM, BLACK, WHITE);
LCDPutStr("Text 3", 50, 20, SMALL, BLACK, WHITE);

}