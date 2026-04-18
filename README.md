# Carbon-Aware Energy Monitor

A real-time energy monitoring system built on the STM32 Nucleo-F429ZI that measures AC voltage, current, and power — then computes live carbon emission estimates and displays them on an LCD. Designed as a research prototype for edge intelligence in sustainable energy systems.

## Overview

This project uses low-cost analog sensors interfaced with a Cortex-M4 microcontroller to capture true RMS voltage and current from a mains supply. 
Power consumption is computed and converted to a real-time CO2 emission estimate using the India national grid carbon intensity factor (0.82 kgCO2/kWh). 
All readings are displayed live on an LCD1602 and streamed over UART for 
dataset collection and offline analysis.

The system is the hardware foundation for ongoing research into edge AI-based 
energy anomaly detection on resource-constrained embedded platforms.

## Hardware

| Component         | Role                              |
|-------------------|-----------------------------------|
| Nucleo-F429ZI     | Main MCU — ARM Cortex-M4, 180MHz  |
| ACS712 (30A)      | AC/DC current sensing via Hall effect |
| ZMPT101B          | AC voltage sensing via transformer |
| LCD1602 + I2C     | Live display of power and CO2     |

## Measured Parameters

- AC RMS Voltage (V)
- AC RMS Current (A)
- Apparent Power (W)
- Real-time CO2 emission rate (kgCO2/hr)

## How It Works

Both sensors feed into ADC1 on the STM32 via DMA. 500 samples are collected 
per measurement cycle to compute true RMS values using the square-root of 
mean-squares method. A DC offset calibration is applied to both channels to 
remove the sensor bias voltage before RMS computation. The resulting power figure is multiplied by India's grid emission factor to produce a live carbon estimate.

Readings are refreshed every 500ms on the LCD and simultaneously streamed 
as CSV over USART2 (115200 baud) for PC-side logging and dataset collection.

## Calibration

The ZMPT101B scale factor and both sensor midpoints are calibrated against 
a reference plug-in energy meter. Calibration values are defined as constants 
in `Core/Inc/energy_config.h`.

## Repository Structure

energy-monitor/
├── Core/
│   ├── Src/
│   │   ├── main.c           # Main application loop
│   │   ├── energy.c         # RMS calculation, power, CO2
│   │   └── lcd_i2c.c        # LCD1602 I2C driver
│   └── Inc/
│       ├── energy.h
│       ├── energy_config.h  # Calibration constants
│       └── lcd_i2c.h
├── dataset/
│   └── sample_readings.csv  # Example logged data
├── tools/
│   └── uart_logger.py       # Python UART → CSV logger
├── docs/
│   └── wiring_diagram.png   # Hardware connection diagram
└── README.md

## Dataset Format

Data is logged via UART as CSV and captured using `tools/uart_logger.py`:

timestamp,voltage_V,current_A,power_W,co2_kgph
2026-04-16 15:23:01,229.4,1.24,284.3,0.000065

## Emission Factor

Carbon intensity used: **0.82 kgCO2/kWh** (India national grid average, 
Central Electricity Authority 2023). To adapt for UK grid (~0.23 kgCO2/kWh) 
or real-time grid intensity via the National Grid ESO API, update 
`GRID_EMISSION_FACTOR` in `energy_config.h`.

## Next Steps (Research Roadmap)

- [ ] Collect 4+ weeks of continuous load data
- [ ] Train TinyML anomaly detection model (TFLite Micro)
- [ ] Deploy inference on Nucleo-F429ZI — measure latency and RAM
- [ ] Benchmark INT8 quantized model vs float32 baseline
- [ ] Submit findings to IEEE ISGT or ACM BuildSys workshop

## Research Context

This project sits at the intersection of embedded systems engineering and 
sustainability science. The core research question driving the next phase is:

> *Can a sub-50KB machine learning model, running entirely on a 
> resource-constrained ARM Cortex-M4, detect energy anomalies with sufficient 
> accuracy to support real-time carbon-aware demand management — without any 
> cloud dependency?*

This question is the basis of a planned PhD research proposal targeting 
UK universities in the areas of sustainable energy systems, edge AI, and 
embedded intelligence.

## Tools & Dependencies

- STM32CubeIDE 1.14+
- STM32 HAL (included via CubeMX)
- Python 3.x + pyserial (for UART logging)
- TensorFlow 2.x + TFLite (for upcoming model training phase)

## Author

Embedded Engineer | MSc Sustainability Science (in progress)  
Research interests: TinyML, edge computing, sustainable IoT, carbon-aware systems