#include <WiFi.h>
#include <DHT.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

// --- Configurações do Sensor ---
#define DHTPIN 23
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

// --- Configurações da Rede Wi-Fi (Wokwi) ---
#define WLAN_SSID       "Wokwi-GUEST"
#define WLAN_PASS       ""


#define MQTT_SERVER      "broker.hivemq.com"
#define MQTT_SERVERPORT  1883
#define MQTT_TOPIC       "clyvocompanion/pet/temperatura" 

WiFiClient client;
Adafruit_MQTT_Client mqtt(&client, MQTT_SERVER, MQTT_SERVERPORT);
Adafruit_MQTT_Publish temperatura_feed = Adafruit_MQTT_Publish(&mqtt, MQTT_TOPIC);

void MQTT_connect();

void setup() {
  Serial.begin(115200);
  delay(10);
  
  Serial.println("Clyvo Companion - Inicializando Node-RED Integration...");
  dht.begin();

  Serial.print("Conectando ao Wi-Fi...");
  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWi-Fi Conectado!");
}

void loop() {
  MQTT_connect();

  float t = dht.readTemperature();

  if (isnan(t)) {
    Serial.println("Erro ao ler o sensor!");
  } else {
    Serial.print("Temperatura: ");
    Serial.print(t);
    Serial.println(" °C");

    Serial.print("Enviando para o Node-RED... ");
    if (! temperatura_feed.publish(t)) {
      Serial.println("Falhou.");
    } else {
      Serial.println("Sucesso!");
    }
  }
  delay(5000); // Envia a cada 5 segundos para o Node-RED responder rápido
}

void MQTT_connect() {
  int8_t ret;
  if (mqtt.connected()) return;

  Serial.print("Conectando ao Broker... ");
  while ((ret = mqtt.connect()) != 0) {
       Serial.println("Erro. Tentando novamente em 5s...");
       mqtt.disconnect();
       delay(5000);
  }
  Serial.println("Conectado ao Broker do Clyvo Companion com sucesso!");
}