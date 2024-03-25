from configs.broker_configs import mqtt_broker_configs
from paho.mqtt.client import Client
from paho.mqtt.client import MQTTMessage

def on_connect(client: Client, userdata, flags, rc):
    if rc == 0:
        print('Connected to MQTT Broker')
        client.subscribe(mqtt_broker_configs['TOPIC'])
    else:
        print(f'Unable to connect to MQTT Broker. Error code: {rc}')

def on_message(client: Client, userdata, message: MQTTMessage):
    print('Message received')
    print(client)
    print(message.payload.decode('ascii'))

