#include <Arduino.h>

#include "setupFunctions.hpp"

#define BUTTON 18

#define WIFI_SSID "CPEJr"
#define WIFI_PASSWD "Cpejr@123"

#define MQTT_USERNAME "cpejr"
#define MQTT_PASSWD "cpejr123"

#define MQTT_SERVER "test.mosquitto.org"
#define MQTT_PORT 1883
#define TOPIC "gestao/teste"

WiFiClient espClient;
PubSubClient pbClient(espClient);

void setup() 
{
  Serial.begin(115200); 

  setup_wifi(WIFI_SSID, WIFI_PASSWD);
  pbClient.setServer(MQTT_SERVER, MQTT_PORT);

  pinMode(BUTTON, INPUT_PULLUP);
}

void loop()
{
  if (!pbClient.connected()) 
  {
    reconnect(pbClient, MQTT_USERNAME, MQTT_PASSWD);
  }
  pbClient.loop();

  pbClient.publish(TOPIC, "teste", true);

  delay(500);
}
