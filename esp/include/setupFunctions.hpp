#include <PubSubClient.h>
#include <WiFi.h>

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

void reconnect(PubSubClient& pbClient, String clientID) {
  // Loop until we're reconnected
  while (!pbClient.connected()) 
  {
    Serial.print("Attempting MQTT connection...");

    if (pbClient.connect(clientID.c_str())) 
    {
      Serial.println("connected");
    }
    else {
      Serial.print("failed, rc=");
      Serial.print(pbClient.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}
