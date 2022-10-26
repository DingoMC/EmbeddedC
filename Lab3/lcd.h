#ifndef LCD_H
#define LCD_H
void LCD_init(void);
void LCD_sendCommand(unsigned char data);
void LCD_sendChar(unsigned char data);
void LCD_sendString (char *str);
void pisz_1(char *str);
void pisz_2(char *str);
void pisz_xy(char *str, unsigned int wiersz, unsigned int kolumna);
void LCD_clr_1();
void LCD_clr_2();
void LCD_clr_xy();
void LCD_clear();
#endif
