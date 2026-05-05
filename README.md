# STM32 Energy Monitor

A simple energy monitoring setup using the NUCLEO-F429ZI board. It reads voltage and current from two sensors and shows the values on a small LCD. Nothing fancy — just a clean starting point for anyone wanting to measure power consumption with an STM32.

---

## What it does

- Reads AC voltage via a **ZMPT101B** sensor
- Reads current via an **ACS712** sensor
- Converts raw ADC values to volts and amps
- Displays both on a **16x2 I2C LCD**, refreshed every 500ms
- Uses **DMA** for ADC sampling so the CPU isn't stuck waiting

---

## Hardware used

- NUCLEO-F429ZI (STM32F429ZI)
- ZMPT101B voltage sensor module
- ACS712 current sensor module (20A variant, 100mV/A)
- 16x2 LCD with I2C backpack (PCF8574)

---

## Wiring

| Sensor / Device | STM32 Pin | Notes |
|---|---|---|
| ZMPT101B output | PA3 (ADC1 CH3) | Voltage sensing |
| ACS712 output | PC0 (ADC1 CH10) | Current sensing |
| LCD SDA | PB9 | I2C1 |
| LCD SCL | PB8 | I2C1 |

---

## How the math works

**Voltage:**
```
voltage = (adc_raw / 4095.0) * 5.0 * 4.8
```

**Current:**
```
sensor_voltage = (adc_raw / 4095.0) * 5.0
current = (sensor_voltage - 1.643) / 0.1
```

The `1.643V` offset is what my ACS712 outputs at zero current — yours might be slightly different, measure it with a multimeter and update `CURRENT_OFFSET` in `main.c`. The `0.1` is the sensitivity for the 20A variant (100mV/A). If you're using a different variant, change `CURRENT_SENS` accordingly:

- 5A version → 0.185
- 20A version → 0.100
- 30A version → 0.066

---

## Project config

| Setting | Value |
|---|---|
| ADC resolution | 12-bit |
| ADC mode | Continuous scan + DMA |
| Sample time | 56 cycles |
| I2C speed | 100 kHz |
| UART baud rate | 115200 |
| System clock | 168 MHz (HSE + PLL) |

---

## Getting started

You'll need STM32CubeIDE (or any ARM GCC toolchain) and the STM32 HAL libraries. The project was built with CubeMX so opening it in CubeIDE should work out of the box.

```bash
git clone https://github.com/your-username/stm32-energy-monitor.git
```

Open in STM32CubeIDE, build, and flash via ST-Link.

---

## File structure

```
Core/
  Src/main.c          <- main application code
  Inc/main.h
Drivers/              <- HAL drivers (auto-generated)
lcd_i2c.c
lcd_i2c.h
```

---

## What's next

- Add RMS calculation for proper AC measurements instead of just reading raw ADC values
- Calculate and display real power (W) and accumulated energy (Wh) — the two numbers that actually matter
- Over-voltage and over-current alerts using the onboard LEDs or a buzzer, so the system can warn you without needing a screen
- Log readings over UART to a PC or save to an SD card for historical tracking
- Send data over the onboard Ethernet to a simple local dashboard — no cloud needed, just a browser on the same network
- Low-power mode between readings to make it viable for battery-powered setups