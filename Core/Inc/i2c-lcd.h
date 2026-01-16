#ifndef INC_I2C_LCD_H_
#define INC_I2C_LCD_H_

#include "stm32f4xx_hal.h"

// Comandos comunes de la LCD
#define LCD_CLEARDISPLAY 0x01
#define LCD_RETURNHOME 0x02
#define LCD_ENTRYMODESET 0x04
#define LCD_DISPLAYCONTROL 0x08
#define LCD_CURSORSHIFT 0x10
#define LCD_FUNCTIONSET 0x20
#define LCD_SETCGRAMADDR 0x40
#define LCD_SETDDRAMADDR 0x80

// Flags para control del display
#define LCD_DISPLAYON 0x04
#define LCD_DISPLAYOFF 0x00
#define LCD_CURSORON 0x02
#define LCD_CURSOROFF 0x00
#define LCD_BLINKON 0x01
#define LCD_BLINKOFF 0x00

// Flags para movimiento de cursor/display
#define LCD_DISPLAYMOVE 0x08
#define LCD_CURSORMOVE 0x00
#define LCD_MOVERIGHT 0x04
#define LCD_MOVELEFT 0x00

// Flags para function set
#define LCD_8BITMODE 0x10
#define LCD_4BITMODE 0x00
#define LCD_2LINE 0x08
#define LCD_1LINE 0x00
#define LCD_5x10DOTS 0x04
#define LCD_5x8DOTS 0x00

// Flags para retroiluminación
#define LCD_BACKLIGHT 0x08
#define LCD_NOBACKLIGHT 0x00

// Prototipos de funciones públicas
void lcd_init(void);   // initialize lcd
void lcd_send_cmd(char cmd);  // send command to the lcd
void lcd_send_data(char data);  // send data to the lcd
void lcd_send_string(char *str);  // send string to the lcd
void lcd_put_cur(int row, int col);  // put cursor at the entered position row (0 or 1), col (0-15)
void lcd_clear(void); // clear display

#endif
