⚡ Energy Monitoring System
A real-time AC energy monitoring system built on the STM32F429ZI (NUCLEO-F429ZI) board. It measures AC voltage, current, and power using ZMPT101B and ACS712 sensors, displaying live readings on an I2C LCD.

📋 Features

Real-time AC Voltage measurement (ZMPT101B)
Real-time Current measurement (ACS712 20A)
Power calculation (P = V × I)
Live display on 16x2 I2C LCD
Auto-calibration of current sensor offset on startup


🛠️ Hardware Requirements
ComponentDescriptionSTM32F429ZINUCLEO-F429ZI Development BoardZMPT101BAC Voltage Sensor ModuleACS712 20ACurrent Sensor Module16x2 I2C LCDDisplay (I2C address: 0x27)Jumper WiresFor connections

📌 Pin Configuration
SensorSTM32 PinArduino HeaderADC ChannelZMPT101B (Voltage)PA3A0ADC1 CH3ACS712 (Current)PC0A1ADC1 CH10LCD SDAPB9-I2C1LCD SCLPB6-I2C1

⚡ Wiring Diagram
AC Mains
   │
   ├──── ZMPT101B ──── A0 (PA3) ──── STM32 ADC
   │
   └──── ACS712 IP+ ──── Load ──── ACS712 IP- ──── Neutral
              │
              └──── A1 (PC0) ──── STM32 ADC

⚠️ WARNING: Be extremely careful when working with AC mains voltage. Always use proper isolation and safety precautions.


💻 Software Requirements

STM32CubeIDE
STM32CubeMX
STM32 HAL Drivers (STM32F4xx)
GNU Tools for STM32 (14.3.rel1)
VS Code (for GitHub integration)


🚀 Getting Started
1. Clone the Repository
bashgit clone https://github.com/YOUR_USERNAME/Energy-monitoring-system.git
cd Energy-monitoring-system
2. Open in STM32CubeIDE

Open STM32CubeIDE
Go to File → Import → General → Existing Projects into Workspace
Browse to the STM32CubeIDE folder inside the cloned repo
Click Finish

3. Build the Project

Click Project → Build or press Ctrl+B
Flash to board using Run → Debug


📐 Sensor Formulas
Voltage (ZMPT101B)
V_rms = sqrt(mean(samples²)) × 311.13
Where 311.13 = 220V × √2 (peak voltage for 220V AC mains)
Current (ACS712 20A)
I_rms = sqrt(mean(samples²)) / sensitivity
sensitivity = 0.1 V/A  (100mV per Amp for 20A version)
Power
P = V_rms × I_rms  (in Watts)

📺 LCD Display Format
┌────────────────┐
│ V:220.0V I:2.50A│
│ P:550.0W        │
└────────────────┘

⚙️ Key Configuration
ParameterValueADC Resolution12-bit (0–4095)ADC Reference3.3VSampling500 samples per readingCurrent OffsetAuto-calibrated on bootDead Zone< 0.3A treated as 0MCU Clock168 MHzI2C Speed100 kHz

📁 Project Structure
Energy-monitoring-system/
├── Core/
│   ├── Inc/
│   │   └── main.h
│   └── Src/
│       ├── main.c          ← Main application code
│       ├── stm32f4xx_it.c  ← Interrupt handlers
│       └── stm32f4xx_hal_msp.c
├── Drivers/
│   ├── STM32F4xx_HAL_Driver/
│   └── CMSIS/
├── STM32CubeIDE/           ← IDE project files
├── Energy_Monitoring_system.ioc ← CubeMX config
└── README.md

🐛 Known Issues & Fixes

ADC DMA issue: Use uint32_t array for DMA buffer, not uint16_t
Float printf: Add -u _printf_float to linker flags
Current noise: Low-pass filter + 500 sample averaging applied
Workspace path: Always open STM32CubeIDE with Documents/Github/Energy-monitoring-system as workspace


🔮 Future Improvements

 Energy consumption over time (kWh calculation)
 UART data logging to PC
 Over-current alert with buzzer
 IoT integration via Ethernet (STM32F429 has built-in ETH)
 SD card data logging


👩‍💻 Author
Aditi Raj
STM32 Embedded Systems Project
NUCLEO-F429ZI Energy Monitoring System