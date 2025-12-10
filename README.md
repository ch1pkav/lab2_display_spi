# Lab 2: SPI Display

This lab is a continuation of lab1 which integrates GPS data with the ILI9341 SPI TFT display.

## Building:
```bash
mkdir build
```
```bash
cd build
```
```bash
cmake ..
```
```bash
cmake --build .
```
## Flashing
```bash
cd build; cmake --build --target flash
```

## Components and pinout:
- `STM32F411EDISCOVERY`
- `GY-GPS6MV2` - PA10: RX, PA15: TX
- Blue onboard LED (USART DMA IRQ indicator) - PD15, internal pull-up
- `ILI9341`: 
  - Backlight pin tied to VCC.
  - PC3: MOSI - SPI master out / slave in
  - PC4: RST - Display reset pin, internal pull-up
  - PC5: CS - SPI chip select, internal pull-up
  - PB0: DC - Data / command, internal pull-up
  - PB10: CLK - SPI clock.

## SPI Logic analysis

A capture of the SPI traffic via the saleae spi analyzer can be viewed in [lab2_spi.sal](lab2_spi.sal). Some screenshots of the capture are provided below:

SPI traffic, device reset in the middle:

<img width="1099" height="292" alt="image" src="https://github.com/user-attachments/assets/426a7006-acdb-4b3d-9e60-71bcd25e91cd" />

SPI traffic, periodic refreshes:

<img width="822" height="380" alt="image" src="https://github.com/user-attachments/assets/0b0c7e14-a834-463f-ae9f-913db26fed75" />

Analyzer data table:

<img width="843" height="975" alt="image" src="https://github.com/user-attachments/assets/4c8d19be-c6cf-4926-a5b7-cc222647bda5" />
