/*
 * lcd_i2c.h
 *
 *  Created on: 12-Apr-2026
 *      Author: aditi_raj
 */

#ifndef APPLICATION_USER_CORE_LCD_I2C_H_
#define APPLICATION_USER_CORE_LCD_I2C_H_

#ifndef LCD_H
#define LCD_H

#include "stm32f4xx_hal.h"
#include <string.h>

// Change this to your PCF8574 I2C address (typically 0x27 or 0x3F)
#define LCD_I2C_ADDR    (0x27 << 1)

// LCD commands
#define LCD_CLEAR           0x01
#define LCD_HOME            0x02
#define LCD_ENTRY_MODE      0x06
#define LCD_DISPLAY_ON      0x0C
#define LCD_FUNCTION_SET    0x28  // 4-bit, 2 lines, 5x8 dots
#define LCD_SET_DDRAM       0x80

// PCF8574 pin mapping
#define LCD_BACKLIGHT       0x08
#define LCD_ENABLE          0x04
#define LCD_RW              0x02
#define LCD_RS              0x01

void LCD_Init(I2C_HandleTypeDef *hi2c);
void LCD_Clear(void);
void LCD_SetCursor(uint8_t row, uint8_t col);
void LCD_Print(char *str);
void LCD_PrintChar(char c);

#endif

#endif /* APPLICATION_USER_CORE_LCD_I2C_H_ */
