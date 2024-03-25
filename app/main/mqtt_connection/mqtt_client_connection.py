import paho.mqtt.client as mqtt
from .callbacks import on_connect, on_message

class MqttClientConnection:
    def __init__(self,
                 broker_ip: str,
                 port: int,
                 client_name: str,
                 keepalive=60):
        self.__broker_ip = broker_ip
        self.__port = port
        self.__client_name = client_name
        self.__keepalive = keepalive
        self.__mqtt_client = None

    def start_connection(self) -> None:
        mqtt_client = mqtt.Client(self.__client_name)
        mqtt_client.connect(host = self.__broker_ip,
                            port = self.__port,
                            keepalive = self.__keepalive)
        
        # callbacks
        mqtt_client.on_connect = on_connect
        mqtt_client.on_message = on_message

        self.__mqtt_client = mqtt_client
        self.__mqtt_client.loop_start()
