# IoT Based COVID-19 Patient Health Monitoring System

Final Year Project, B.S. Electrical Engineering, HITEC University Taxila (Spring 2022).
Team project (4 members).

## Overview
An ESP32 based remote patient monitoring system. It measures vital signs and environmental conditions, shows them on an LCD, and sends them to the Blynk IoT app so a doctor can monitor the patient remotely.

## Measured Parameters
- Heart rate (BPM) and blood oxygen saturation (SpO2)
- Body temperature
- ECG signal
- Room temperature and humidity

## Hardware
- ESP32 (microcontroller with Wi-Fi)
- MAX30100 (heart rate and SpO2)
- LM35 (body temperature)
- DHT11 (room temperature and humidity)
- ECG sensor (analog)
- 16x4 I2C LCD (local display)

## Software
- Arduino C++ (ESP32)
- Blynk IoT app for remote dashboard
- Fritzing for circuit modelling

## My Role
Hardware assembly and coding.

## Setup
1. Install the Arduino libraries: MAX30100_PulseOximeter, SimpleTimer, Blynk, LiquidCrystal_I2C, DHT.
2. Open covid_patient_monitor.ino
3. Replace YOUR_BLYNK_AUTH_TOKEN, YOUR_WIFI_NAME and YOUR_WIFI_PASSWORD with your own values.
4. Upload to the ESP32.

Note: This is an academic prototype and is not a certified medical device.
