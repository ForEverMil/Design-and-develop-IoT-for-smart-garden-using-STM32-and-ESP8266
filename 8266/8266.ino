#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>

DynamicJsonDocument doc(1024);


const char *ssid = "Redmi"; // Enter your WiFi name
const char *password = "aabbccdd";  // Enter WiFi password
const char *mqtt_broker = "mqtt-dashboard.com";
const int mqtt_port = 1883;
const char *topic = "esp8266/sensor";
const char *topic1 = "esp8266/control";
WiFiClient espClient;
PubSubClient client(espClient);

char count_string = 0;
char arr_received1[50]= {0}, count_string1 = 0;
unsigned int Count_Time = 0, Split_count = 0;
char temp_char, arr_received[15], *temp[15];

void Send_ControlRelay(unsigned char Relay1_Stt);
void callback(char *topic, byte *payload, unsigned int length);

void setup() {
  Serial.begin(9600);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }

client.setServer(mqtt_broker, mqtt_port);
client.setCallback(callback);
while (!client.connected()) {
    String client_id = "esp8266-client-";
    client_id += String(WiFi.macAddress());
    client.publish(topic,topic);
    if (client.connect(client_id.c_str())) {
    } else {
        delay(2000);
    }
}
  client.publish(topic, "hello emqx");//
  client.subscribe(topic1);
  arr_received1[0] ='0';
  arr_received1[2]='0';
}

void callback(char *topic, byte *payload, unsigned int length) {
  for (int i = 0; i < length; i++) 
  {
    char temp_char1 =  (char)payload[i];
    arr_received1[count_string1++] = temp_char1;
  }
  if(arr_received1[0] == '0')
  {
    Send_ControlRelay(0);
  }
  else  if(arr_received1[0] == '1')
  {
    Send_ControlRelay(1);
  }
   count_string1 = 0;
}

void loop() {
if (Serial.available())
  {
    char temp_char = Serial.read();
    if (temp_char == '!')
    {
      char Buffer[1000];
      unsigned int Len_Buffer;
      String ESP32_to_Web_Json = "";
      Split_count = 0;
      count_string = 0;
      temp[0] = strtok(arr_received, " ");
      while (temp[Split_count] != NULL)
      {
        Split_count++;
        temp[Split_count] = strtok(NULL, " ");
      }
      ESP32_to_Web_Json = "{\"Temp\":\"" + String(temp[0]) + "\"," "\"Humi\":\"" + String(temp[1]) + "\"," "\"Soil\":\"" + String(temp[2])+ "\"," "\"Relay\":\"" + String(arr_received1[2]) + "\" }";
      Len_Buffer = ESP32_to_Web_Json.length()+1;
      ESP32_to_Web_Json.toCharArray(Buffer,Len_Buffer);
      ESP32_to_Web_Json.toCharArray(Buffer,Len_Buffer);
      client.connect("ESP8266Client1");
      client.publish(topic, Buffer);
      memset(arr_received, 0, sizeof(arr_received));
      
    }
    else
    {
       arr_received[count_string++] = temp_char;
    }
  }

  client.loop();
}

void Send_ControlRelay(unsigned char Relay1_Stt)
{
  char ArrData[10] = "";
  sprintf(ArrData, "%d!", Relay1_Stt);
  Serial.print(ArrData);
}