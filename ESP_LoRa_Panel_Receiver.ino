#include <WiFi.h>
#include <PubSubClient.h>
#include <LoRa.h>

#define WIFI_SSID "WFI_SSID"
#define WIFI_PASSWORD "PASSWORD*"

#define MQTT_BROKER "MQTT_IP"
#define MQTT_PORT 1883
#define MQTT_USERNAME "PUT_USERNAME"
#define MQTT_PASSWORD "PUT_PASSWORD"
#define MQTT_TOPIC "lora/solar/temperature" <- //It's the topic name, you can leave it as is or change it

#define LORA_SS 4
#define LORA_RST 5
#define LORA_DIO0 2

unsigned long lastReconnectAttempt = 0;
const unsigned long reconnectInterval = 5000;

WiFiClient espClient;
PubSubClient client(espClient);

void setupWiFi() {
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected");
  Serial.println(WiFi.localIP());
}

void setupMQTT() {
  client.setServer(MQTT_BROKER, MQTT_PORT);
  while (!client.connected()) {
    Serial.print("Connecting to MQTT...");
    if (client.connect("LoRaReceiverClient", MQTT_USERNAME, MQTT_PASSWORD)) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      delay(2000);
    }
  }
}

boolean reconnectMQTT() {
  if (client.connect("LoRaReceiverClient", MQTT_USERNAME, MQTT_PASSWORD)) {
    Serial.println("MQTT reconnected");
    return true;
  }
  return false;
}

void checkWiFiConnection() {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi disconnected. Reconnecting...");
    WiFi.disconnect();
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    
    int attempts = 0;
    while (WiFi.status() != WL_CONNECTED && attempts < 20) {
      delay(500);
      Serial.print(".");
      attempts++;
    }
    
    if (WiFi.status() == WL_CONNECTED) {
      Serial.println("\nWiFi reconnected");
    } else {
      Serial.println("\nFailed to reconnect WiFi");
    }
  }
}

void setup() {
  Serial.begin(115200);
  
  setupWiFi();
  setupMQTT();
  
  Serial.println("Initializing LoRa...");
  LoRa.setPins(LORA_SS, LORA_RST, LORA_DIO0);
  if (!LoRa.begin(433E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
  Serial.println("LoRa receiver initialized.");
}

void loop() {
  checkWiFiConnection();
  
  if (!client.connected()) {
    unsigned long now = millis();
    if (now - lastReconnectAttempt > reconnectInterval) {
      lastReconnectAttempt = now;
      Serial.println("MQTT disconnected. Attempting to reconnect...");
      
      if (reconnectMQTT()) {
        lastReconnectAttempt = 0;
      } else {
        Serial.print("MQTT reconnection failed, rc=");
        Serial.println(client.state());
      }
    }
  } else {
    client.loop();
  }
  
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    String received = "";
    while (LoRa.available()) {
      received += (char)LoRa.read();
    }
    Serial.println("Received via LoRa: " + received);
    
    if (client.connected()) {
      if (client.publish(MQTT_TOPIC, received.c_str())) {
        Serial.println("Published to MQTT successfully");
      } else {
        Serial.println("Failed to publish to MQTT");
      }
    } else {
      Serial.println("MQTT not connected - message not published");
    }
  }
}