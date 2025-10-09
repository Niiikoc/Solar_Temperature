# Solar_Temperature

🆕 Update (October 2025):
The project has been updated — the LoRa Receiver is now implemented using ESPHome, replacing the previous Arduino-based version.
This change makes setup easier, provides direct integration with Home Assistant.

This project provides a complete solution for wireless solar panel temperature monitoring using ESP32 microcontrollers, LoRa communication, and MQTT integration.

## 🧠 Project Purpose

The goal is to remotely monitor the temperature of a solar panel using a low-power sensor node and transmit the data wirelessly over long distances via LoRa.
The receiver then connects to WiFi and publishes the received temperature data to an MQTT broker (or directly into Home Assistant through ESPHome).

## ⚙️ Components Overview

- **solar-heater-receiver.yaml** Now implemented using ESPHome, replacing the previous Arduino-based MQTT receiver. Listens for LoRa packets and publishes received data through ESPHome sensors.
  
- **ESP_LoRa_Panel_Sender.ino**: Reads temperature from a DS18B20 sensor and transmits it via LoRa. The sender uses deep sleep to maximize battery life.
- **ESP_LoRa_Panel_Receiver.ino**: Receives LoRa packets, connects to WiFi, and publishes the temperature data to an MQTT topic.

## 🔩 Hardware Components

The following parts were used to build the Solar Temperature monitoring system:

2× ESP32-WROOM boards ([link](https://www.aliexpress.com/item/1005007284366887.html?spm=a2g0o.order_list.order_list_main.113.3e091802vgrkLc))

Used as microcontrollers — one acts as the LoRa sender and the other as the ESPHome receiver.

2× LoRa SX1278 433 MHz modules (10 km) ([link](https://www.aliexpress.com/item/1005004991920495.html?spm=a2g0o.order_list.order_list_main.118.3e091802vgrkLc))

Provide long-range wireless communication between the two ESP32s.

1× Solar panel ([link](https://www.aliexpress.com/item/1005007189713137.html?spm=a2g0o.order_list.order_list_main.123.3e091802vgrkLc))

Powers the sender node and recharges the battery.

1× 18650 battery holder ([link](https://www.aliexpress.com/item/1005007532672913.html?spm=a2g0o.order_list.order_list_main.108.3e091802vgrkLc))

Holds the rechargeable Li-ion cell for the sender.

1× TP4056 charging module ([link](https://www.aliexpress.com/item/1005006691207512.html?spm=a2g0o.order_list.order_list_main.98.3e091802vgrkLc))

Manages charging from the solar panel to the 18650 battery.

1× Resistor (4.7 kΩ)
Pull-up resistor for the DS18B20 data line.

1× DS18B20 temperature sensor ([link](https://www.aliexpress.com/item/1005004105448773.html?spm=a2g0o.productlist.main.1.3233QrfRQrfRVf&algo_pvid=6f710712-aff1-4bc8-a541-d637bc8b8c60&algo_exp_id=6f710712-aff1-4bc8-a541-d637bc8b8c60-0&pdp_ext_f=%7B%22order%22%3A%222491%22%2C%22eval%22%3A%221%22%2C%22fromPage%22%3A%22search%22%7D&pdp_npi=6%40dis%21EUR%215.74%215.45%21%21%216.53%216.20%21%402103847817600432844794128e4529%2112000028050941190%21sea%21GR%211699222720%21X%211%210%21n_tag%3A-29919%3Bd%3Ae491cca7%3Bm03_new_user%3A-29895&curPageLogUid=wSy2Dk6PVN8k&utparam-url=scene%3Asearch%7Cquery_from%3A%7Cx_object_id%3A1005004105448773%7C_p_origin_prod%3A))
Measures the surface temperature of the solar panel.


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

