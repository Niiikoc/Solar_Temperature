# Solar_Temperature

🆕 Update (October 2025):
The project has been updated — the LoRa Receiver is now implemented using ESPHome, replacing the previous Arduino-based version.
This change makes setup easier, provides direct integration with Home Assistant.

This project provides a complete solution for wireless solar panel temperature monitoring using ESP32 microcontrollers, LoRa communication, and MQTT integration.

## Project Purpose

The goal is to remotely monitor the temperature of a solar panel using a low-power sensor node and transmit the data wirelessly over long distances via LoRa.
The receiver then connects to WiFi and publishes the received temperature data to an MQTT broker (or directly into Home Assistant through ESPHome).

## Components

- **solar-heater-receiver.yaml** Now implemented using ESPHome, replacing the previous Arduino-based MQTT receiver. Listens for LoRa packets and publishes received data through ESPHome sensors.
  
- **ESP_LoRa_Panel_Sender.ino**: Reads temperature from a DS18B20 sensor and transmits it via LoRa. The sender uses deep sleep to maximize battery life.
- **ESP_LoRa_Panel_Receiver.ino**: Receives LoRa packets, connects to WiFi, and publishes the temperature data to an MQTT topic.

## Features

✅ Low-power, battery-friendly LoRa sender node

📡 Long-range communication (433 MHz)

🌐 Automatic WiFi + MQTT integration through ESPHome

🧩 Home Assistant auto-discovery support

⚙️ Simple YAML configuration — no Arduino code needed for receiver

🔌 DS18B20 sensor support (1-Wire)

## Usage

- Sender Setup
  1. **Upload** `ESP_LoRa_Panel_Sender.ino` to the sender ESP32 and connect a DS18B20 sensor to GPIO 14.

- Receiver Setup

  **EspHome Receiver**
    1. Add the **solar-heater-receiver.yaml** file to your ESPHome Builder.
    2. After uploading, the receiver will automatically appear in Home Assistant and start displaying live temperature readings.
  
  **Old Way Receiver**
    1. **Configure** WiFi and MQTT credentials in `ESP_LoRa_Panel_Receiver.ino`. 
    2. **Upload** `ESP_LoRa_Panel_Receiver.ino` to the receiver ESP32.

## Dependencies

- OneWire
- DallasTemperature
- LoRa
- PubSubClient

## Receiver

ESPHome (handles MQTT, WiFi, and LoRa integration natively)

## License

MIT License

