# STM32 Energy Monitor

An embedded energy monitoring project built on the **NUCLEO-F429ZI** board. It reads voltage and current sensor data, calculates electrical values, and displays them on a 16x2 I2C LCD.

This project is useful for learning STM32 ADC, DMA, I2C, LCD interfacing, and basic FreeRTOS task scheduling.

## Features

- Measures voltage using a **ZMPT101B** sensor
- Measures current using an **ACS712** sensor
- Uses **ADC with DMA** for continuous sampling
- Calculates RMS voltage, RMS current, and power
- Displays live values on a **16x2 I2C LCD**
- Runs measurement and display logic inside a **FreeRTOS task**
- Built using STM32 HAL and STM32CubeIDE

## Hardware

| Component | Purpose |
|---|---|
| STM32 NUCLEO-F429ZI | Main controller |
| ZMPT101B | Voltage sensing |
| ACS712 20A | Current sensing |
| 16x2 I2C LCD | Display output |

## Wiring

| Device | STM32 Pin |
|---|---|
| ZMPT101B output | PA3 / ADC1 CH3 |
| ACS712 output | PC0 / ADC1 CH10 |
| LCD SDA | PB9 |
| LCD SCL | PB8 |

## Software Used

- STM32CubeIDE
- STM32 HAL Driver
- FreeRTOS
- C language

## Project Highlights

- ADC runs in scan mode with DMA
- Two analog channels are sampled continuously
- FreeRTOS manages the measurement task
- LCD updates periodically with voltage, current, and power
- Code is kept simple and easy to modify for future features

## How to Build

1. Open the project in STM32CubeIDE.
2. Build the project.
3. Flash it to the NUCLEO-F429ZI board using ST-Link.
4. Connect the sensors and LCD as shown in the wiring table.

## Main Files

| File | Description |
|---|---|
| `Core/Src/main.c` | Main application logic |
| `Core/Src/i2c_lcd.c` | LCD driver |
| `Core/Inc/lcd_i2c.h` | LCD driver header |
| `Core/Inc/FreeRTOSConfig.h` | FreeRTOS configuration |

## Future Improvements

- Add energy calculation in Wh or kWh
- Add over-voltage and over-current alerts
- Send data over UART, Ethernet, or cloud dashboard
- Store readings for history and analysis
