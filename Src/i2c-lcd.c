/*
 * i2c-lcd.c
 * Source file for I2C LCD driver implementing common LCD functions via I2C.
 */

#include "i2c-lcd.h"

// *** CONFIGURACIÓN ***
// Dirección I2C de la pantalla. Comúnmente 0x27 o 0x3F. Desplazado 1 bit a la izquierda para HAL.
// Si es 0x27 -> (0x27 << 1) = 0x4E
// Si es 0x3F -> (0x3F << 1) = 0x7E
#define SLAVE_ADDRESS_LCD (0x27 << 1)

// Variable externa del manejador I2C (definida en main.c)
extern I2C_HandleTypeDef hi2c1;

// Función interna para enviar datos crudos por I2C
void lcd_send_cmd(char cmd)
{
    char data_u, data_l;
    uint8_t data_t[4];
    data_u = (cmd & 0xf0);
    data_l = ((cmd << 4) & 0xf0);
    data_t[0] = data_u | 0x0C;  //en=1, rs=0
    data_t[1] = data_u | 0x08;  //en=0, rs=0
    data_t[2] = data_l | 0x0C;  //en=1, rs=0
    data_t[3] = data_l | 0x08;  //en=0, rs=0
    HAL_I2C_Master_Transmit(&hi2c1, SLAVE_ADDRESS_LCD, (uint8_t *)data_t, 4, 100);
}

void lcd_send_data(char data)
{
    char data_u, data_l;
    uint8_t data_t[4];
    data_u = (data & 0xf0);
    data_l = ((data << 4) & 0xf0);
    data_t[0] = data_u | 0x0D;  //en=1, rs=1
    data_t[1] = data_u | 0x09;  //en=0, rs=1
    data_t[2] = data_l | 0x0D;  //en=1, rs=1
    data_t[3] = data_l | 0x09;  //en=0, rs=1
    HAL_I2C_Master_Transmit(&hi2c1, SLAVE_ADDRESS_LCD, (uint8_t *)data_t, 4, 100);
}

void lcd_clear(void)
{
    lcd_send_cmd(LCD_CLEARDISPLAY);
    HAL_Delay(2); // El comando clear requiere más tiempo
}

void lcd_put_cur(int row, int col)
{
    switch (row)
    {
        case 0:
            col |= 0x80;
            break;
        case 1:
            col |= 0xC0;
            break;
    }
    lcd_send_cmd(col);
}

void lcd_init(void)
{
    // Inicialización según hoja de datos para modo 4-bit
    HAL_Delay(50);  // Esperar >40ms tras encendido
    lcd_send_cmd(0x30);
    HAL_Delay(5);   // Esperar >4.1ms
    lcd_send_cmd(0x30);
    HAL_Delay(1);   // Esperar >100us
    lcd_send_cmd(0x30);
    HAL_Delay(10);
    lcd_send_cmd(0x20); // Modo 4-bit
    HAL_Delay(10);

    // Configuración del display
    lcd_send_cmd(LCD_FUNCTIONSET | LCD_4BITMODE | LCD_2LINE | LCD_5x8DOTS); // 0x28
    HAL_Delay(1);
    lcd_send_cmd(LCD_DISPLAYCONTROL | LCD_DISPLAYOFF | LCD_CURSOROFF | LCD_BLINKOFF); // 0x08
    HAL_Delay(1);
    lcd_clear(); // 0x01
    HAL_Delay(2);
    lcd_send_cmd(LCD_ENTRYMODESET | LCD_MOVERIGHT | LCD_CURSORMOVE); // 0x06
    HAL_Delay(1);
    lcd_send_cmd(LCD_DISPLAYCONTROL | LCD_DISPLAYON | LCD_CURSOROFF | LCD_BLINKOFF); // 0x0C (Encender display)
}

void lcd_send_string(char *str)
{
    while (*str) lcd_send_data(*str++);
}

