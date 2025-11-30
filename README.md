# ESP32 Plant Monitoring System

This project is a plant monitoring system based on the ESP32 microcontroller. It measures environmental data such as temperature, humidity, and soil moisture using sensors and sends this data to both Blynk and a local MQTT broker. The data is further processed and visualized using Node-RED, stored in MongoDB, and displayed using Grafana.

## Features

- Reads temperature and humidity using a DHT11 sensor  
- Measures soil moisture using an analog soil sensor  
- Sends sensor data to:
  - **Blynk** app (for real-time mobile dashboard)
  - **MQTT Broker** (for local processing)
- Uses **Node-RED** to:
  - Subscribe to MQTT data
  - Process and store data in **MongoDB**
  - Forward to **Grafana** for dashboard visualization

## Hardware Required

- ESP32 development board  
- DHT11 sensor  
- Analog soil moisture sensor  
- Micro-USB cable  
- Wi-Fi connection  

## Software Stack

- Arduino IDE (for ESP32 programming)
- Blynk (mobile app)
- Mosquitto (MQTT broker)
- Node-RED (data pipeline)
- MongoDB (data storage)
- Grafana (data visualization)

## Pin Connections

| Component        | ESP32 Pin |
|------------------|-----------|
| DHT11 Data       | GPIO 33   |
| Soil Moisture    | GPIO 34   |
| VCC (both)       | 3.3V      |
| GND (both)       | GND       |


##Pin Diagram of ESP32
![esp32_pinout](esp32_pinout.jpeg)

## Installation and Setup

### 1. Flash ESP32

- Install libraries: `DHT`, `Blynk`, `PubSubClient`, and `WiFi`
- Upload the code provided in the project

### 2. Configure Blynk

- Create a new project on Blynk
- Add 3 widgets:
  - Value Display for Temperature (`V0`)
  - Value Display for Humidity (`V1`)
  - Value Display for Soil Moisture (`V2`)
- Use the same `BLYNK_AUTH_TOKEN` in your code

### 3. Setup MQTT Broker

- Install Mosquitto and run it locally:
  ```bash
  mosquitto -v

##4. Node-Red Setup
![Node-Red setup](Screenshot 2025-11-30 183352.png)
