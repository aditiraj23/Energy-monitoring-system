/*
 * i2c_lcd.c
 *
 *  Created on: 12-Apr-2026
 *      Author: aditi_raj
 */

#include "lcd_i2c.h"

static I2C_HandleTypeDef *lcd_i2c;
static uint8_t backlight_state = LCD_BACKLIGHT;

// ── Low-level helpers ─────────────────────────────────────────

static void LCD_SendByte(uint8_t byte) {
    HAL_I2C_Master_Transmit(lcd_i2c, LCD_I2C_ADDR, &byte, 1, HAL_MAX_DELAY);
}

static void LCD_PulseEnable(uint8_t data) {
    LCD_SendByte(data | LCD_ENABLE);
    for (volatile int i = 0; i < 50; i++);  // small delay

    LCD_SendByte(data & ~LCD_ENABLE);
    for (volatile int i = 0; i < 50; i++);  // small delay
}

static void LCD_SendNibble(uint8_t nibble, uint8_t rs) {
    uint8_t data = (nibble & 0xF0) | backlight_state | rs;
    LCD_PulseEnable(data);
}

static void LCD_SendCommand(uint8_t cmd) {
    LCD_SendNibble(cmd & 0xF0, 0x00);
    LCD_SendNibble((cmd << 4) & 0xF0, 0x00);

    if (cmd == LCD_CLEAR || cmd == LCD_RETURN_HOME) {
        HAL_Delay(2); // required delay
    }
}

static void LCD_SendData(uint8_t data) {
    LCD_SendNibble(data & 0xF0, LCD_RS);
    LCD_SendNibble((data << 4) & 0xF0, LCD_RS);
}

// ── Public API ────────────────────────────────────────────────

void LCD_Init(I2C_HandleTypeDef *hi2c) {
    lcd_i2c = hi2c;
    HAL_Delay(50);  // LCD power-up delay

    // Initialization sequence
    LCD_SendNibble(0x30, 0x00); HAL_Delay(5);
    LCD_SendNibble(0x30, 0x00); HAL_Delay(1);
    LCD_SendNibble(0x30, 0x00); HAL_Delay(1);
    LCD_SendNibble(0x20, 0x00); HAL_Delay(1);

    LCD_SendCommand(LCD_FUNCTION_SET);
    LCD_SendCommand(LCD_DISPLAY_ON);
    LCD_SendCommand(LCD_CLEAR);
    LCD_SendCommand(LCD_ENTRY_MODE);
}

void LCD_Clear(void) {
    LCD_SendCommand(LCD_CLEAR);
}

void LCD_SetCursor(uint8_t row, uint8_t col) {
    uint8_t row_offsets[] = {0x00, 0x40, 0x14, 0x54};

    if (row > 3) row = 3;
    if (col > 19) col = 19;

    LCD_SendCommand(LCD_SET_DDRAM | (row_offsets[row] + col));
}

void LCD_PrintChar(char c) {
    LCD_SendData((uint8_t)c);
}

void LCD_Print(const char *str) {
    while (*str) {
        LCD_SendData((uint8_t)(*str++));
    }
}

void LCD_Backlight(uint8_t state) {
    backlight_state = state ? LCD_BACKLIGHT : 0x00;
    LCD_SendByte(backlight_state);
}

void LCD_Printf(const char *fmt, ...) {
    char buffer[64];

    va_list args;
    va_start(args, fmt);
    vsnprintf(buffer, sizeof(buffer), fmt, args);
    va_end(args);

    LCD_Print(buffer);
}
