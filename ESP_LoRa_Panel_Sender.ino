#include <OneWire.h>
#include <DallasTemperature.h>
#include <LoRa.h>
#include <esp_sleep.h>

#define ONE_WIRE_BUS 14
#define LORA_SS 4
#define LORA_RST 5
#define LORA_DIO0 2

// Sleep time to microseconds (10 minutes = 10 minutes * 60 seconds * 1000000 μs)
#define SLEEP_TIME_DURATION 10 * 60 * 1000000

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

void setup() {
  Serial.begin(115200);

  sensors.begin();

  LoRa.setPins(LORA_SS, LORA_RST, LORA_DIO0);
  if (!LoRa.begin(433E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }

  sensors.requestTemperatures();
  float tempC = sensors.getTempCByIndex(0);

  // Send Data Via LoRa
  LoRa.beginPacket();
  LoRa.print(tempC);
  LoRa.endPacket();
  
  //Serial.println("Data sent, going to sleep...");
  Serial.flush();
  
  // Set Timer for Wake up
  esp_sleep_enable_timer_wakeup(SLEEP_TIME_DURATION);
  
  // Start Deep Sleep
  esp_deep_sleep_start();
}

void loop() {
}