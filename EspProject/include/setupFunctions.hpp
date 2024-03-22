#include <WiFi.h>
#include <PubSubClient.h>

void setup_wifi(char* ssid, char* passwd)
{
  delay(10);

  Serial.println();
  Serial.println("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, passwd);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void reconnect(PubSubClient& pbClient, char* username, char* passwd) {
  // Loop until we're reconnected
  while (!pbClient.connected()) 
  {
    Serial.print("Attempting MQTT connection...");

    String clientID = "ESP_CPEJR";

    if (pbClient.connect(clientID.c_str(), username, passwd)) 
    {
      Serial.println("connected");
      Serial.println(pbClient.connected());
    }
    else {
      Serial.print("failed, rc=");
      Serial.print(pbClient.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}
