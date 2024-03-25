#include <Arduino.h>

#include "setupFunctions.hpp"

#define USE_BUTTON 18
#define MAINTENANCE_BUTTON 25

#define WIFI_SSID "Wokwi-GUEST"
#define WIFI_PASSWD ""

#define MQTT_SERVER "test.mosquitto.org"
#define MQTT_PORT 1883
#define TOPIC "gestao/teste"
#define CLIENT_ID "esp_cpejr"

WiFiClient espClient;
PubSubClient mqttClient(espClient);

// Responsavel por identificar o esp no aplicativo
// HACK: esse random ai ta paia, tem que mudar
String espID = "esp" + String(random(0xffff), HEX);

// Estados possíveis para a maquina
enum state 
{
  FREE,
  INUSE,
  MAINTENANCE
};

void publishState(PubSubClient& mqttClient, String mqttTopic, state currentState, String espID)
{
  String messageString = espID + " " + String(currentState);
  mqttClient.publish(TOPIC, messageString.c_str());
}

// Estados atual e anterior da maquina
state currentState = FREE;
state previousState = INUSE;

void setup() 
{
  Serial.begin(115200); 

  setup_wifi(WIFI_SSID, WIFI_PASSWD);
  mqttClient.setServer(MQTT_SERVER, MQTT_PORT);

  pinMode(USE_BUTTON, INPUT_PULLUP);
  pinMode(MAINTENANCE_BUTTON, INPUT_PULLUP);
}

void loop()
{
  if (!mqttClient.connected()) 
  {
    reconnect(mqttClient, CLIENT_ID);
  }
  mqttClient.loop();

  previousState = currentState;
  if (digitalRead(MAINTENANCE_BUTTON)) currentState = MAINTENANCE;
  else if (digitalRead(USE_BUTTON)) currentState = INUSE;
  else currentState = FREE;

  if (currentState != previousState) publishState(mqttClient, TOPIC, currentState, espID.c_str());

  delay(500);
}
