/*
 * i2c_lcd.c
 *
 *  Created on: 12-Apr-2026
 *      Author: aditi_raj
 */

#include "lcd_i2c.h"

static I2C_HandleTypeDef *lcd_i2c;
static uint8_t backlight_state = LCD_BACKLIGHT;

// ── Low-level helpers ─────────────────────────────────────────────────────────

static void LCD_SendByte(uint8_t byte) {
    HAL_I2C_Master_Transmit(lcd_i2c, LCD_I2C_ADDR, &byte, 1, HAL_MAX_DELAY);
}

static void LCD_PulseEnable(uint8_t data) {
    LCD_SendByte(data | LCD_ENABLE);   // Enable HIGH
    HAL_Delay(1);
    LCD_SendByte(data & ~LCD_ENABLE);  // Enable LOW
    HAL_Delay(1);
}

static void LCD_SendNibble(uint8_t nibble, uint8_t rs) {
    uint8_t data = (nibble & 0xF0) | backlight_state | rs;
    LCD_PulseEnable(data);
}

static void LCD_SendCommand(uint8_t cmd) {
    LCD_SendNibble(cmd & 0xF0, 0x00);        // Upper nibble, RS=0
    LCD_SendNibble((cmd << 4) & 0xF0, 0x00); // Lower nibble, RS=0
}

static void LCD_SendData(uint8_t data) {
    LCD_SendNibble(data & 0xF0, LCD_RS);        // Upper nibble, RS=1
    LCD_SendNibble((data << 4) & 0xF0, LCD_RS); // Lower nibble, RS=1
}

// ── Public API ────────────────────────────────────────────────────────────────

void LCD_Init(I2C_HandleTypeDef *hi2c) {
    lcd_i2c = hi2c;
    HAL_Delay(50);  // Wait for LCD power-up

    // Init sequence (4-bit mode)
    LCD_SendNibble(0x30, 0x00); HAL_Delay(5);
    LCD_SendNibble(0x30, 0x00); HAL_Delay(1);
    LCD_SendNibble(0x30, 0x00); HAL_Delay(1);
    LCD_SendNibble(0x20, 0x00); HAL_Delay(1); // Switch to 4-bit

    // Configure display
    LCD_SendCommand(LCD_FUNCTION_SET);   // 4-bit, 2 lines, 5x8
    LCD_SendCommand(LCD_DISPLAY_ON);     // Display ON, cursor OFF, blink OFF
    LCD_SendCommand(LCD_CLEAR);          // Clear display
    HAL_Delay(2);                        // Clear needs extra time
    LCD_SendCommand(LCD_ENTRY_MODE);     // Left to right, no shift
}

void LCD_Clear(void) {
    LCD_SendCommand(LCD_CLEAR);
    HAL_Delay(2);
}

void LCD_SetCursor(uint8_t row, uint8_t col) {
    uint8_t row_offsets[] = {0x00, 0x40};  // Row 0 and Row 1 DDRAM offsets
    LCD_SendCommand(LCD_SET_DDRAM | (row_offsets[row] + col));
}

void LCD_PrintChar(char c) {
    LCD_SendData((uint8_t)c);
}

void LCD_Print(char *str) {
    while (*str) {
        LCD_SendData((uint8_t)(*str++));
    }
}
