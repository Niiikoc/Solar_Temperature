# Solar_Temperature

This project provides a complete solution for wireless solar panel temperature monitoring using ESP32 microcontrollers, LoRa communication, and MQTT integration.

## Project Purpose

The goal is to remotely monitor the temperature of a solar panel using a low-power sensor node and transmit the data wirelessly over long distances. The data is then received, connected to WiFi, and published to an MQTT broker for integration with dashboards or home automation systems.

## Components

- **ESP_LoRa_Panel_Sender.ino**: Reads temperature from a DS18B20 sensor and transmits it via LoRa. The sender uses deep sleep to maximize battery life.
- **ESP_LoRa_Panel_Receiver.ino**: Receives LoRa packets, connects to WiFi, and publishes the temperature data to an MQTT topic.

## Features

- Low-power, battery-friendly sensor node
- Long-range LoRa wireless communication (433 MHz)
- MQTT publishing for easy integration with IoT platforms
- Configurable WiFi and MQTT settings

## Usage

1. **Configure** WiFi and MQTT credentials in `ESP_LoRa_Panel_Receiver.ino`.
2. **Upload** `ESP_LoRa_Panel_Sender.ino` to the sender ESP32 and connect a DS18B20 sensor to GPIO 14.
3. **Upload** `ESP_LoRa_Panel_Receiver.ino` to the receiver ESP32.
4. **Monitor** the temperature data on your MQTT broker under the topic `lora/solar/temperature`.

## Dependencies

- OneWire
- DallasTemperature
- LoRa
- PubSubClient

## License

MIT License

