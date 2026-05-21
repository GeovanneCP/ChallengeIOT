#include <WiFi.h>
#include <DHT.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

// --- Configurações do Sensor ---
#define DHTPIN 23
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

// --- Configurações da Rede Wi-Fi (Simulada pelo Wokwi) ---
#define WLAN_SSID       "Wokwi-GUEST"
#define WLAN_PASS       ""

// --- Configurações do Adafruit IO (COLE SEUS DADOS AQUI) ---
#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883
#define AIO_USERNAME    "GeovanneCP" 
#define AIO_KEY         "aio_oXBM35dRCf6avLYD2b8amohaZW7t"  

// Inicializa o cliente Wi-Fi e o cliente MQTT
WiFiClient client;
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

// Configura o Feed onde os dados serão gravados
Adafruit_MQTT_Publish temperatura_feed = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/temperatura");

void MQTT_connect();

void setup() {
  Serial.begin(115200);
  delay(10);
  
  Serial.println("Clyvo Care - Inicializando Sistema...");
  dht.begin();

  // Conexão Wi-Fi simulada
  Serial.print("Conectando ao Wi-Fi...");
  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWi-Fi Conectado com sucesso!");
}

void loop() {
  // Garante que a conexão MQTT está ativa
  MQTT_connect();

  // Lê a temperatura corporal do pet
  float t = dht.readTemperature();

  if (isnan(t)) {
    Serial.println("Erro ao ler o sensor DHT22!");
  } else {
    Serial.print("Temperatura lida: ");
    Serial.print(t);
    Serial.println(" °C");

    // Envia o dado via protocolo MQTT para a Nuvem
    Serial.print("Enviando dados para o Adafruit IO... ");
    if (! temperatura_feed.publish(t)) {
      Serial.println("Falhou.");
    } else {
      Serial.println("Sucesso!");
    }
  }

  // Envia dados a cada 10 segundos para não sobrecarregar a conta gratuita
  delay(10000); 
}

// Função que gerencia a conexão com o servidor MQTT
void MQTT_connect() {
  int8_t ret;
  if (mqtt.connected()) {
    return;
  }

  Serial.print("Conectando ao Broker MQTT... ");
  uint8_t retries = 3;
  while ((ret = mqtt.connect()) != 0) {
       Serial.println(mqtt.connectErrorString(ret));
       Serial.println("Tentando novamente em 5 segundos...");
       mqtt.disconnect();
       delay(5000);
       retries--;
       if (retries == 0) {
         while (1); // Trava se não conseguir conectar
       }
  }
  Serial.println("MQTT Conectado!");
}