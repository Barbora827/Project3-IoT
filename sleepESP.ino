#include <ESP8266WiFi.h>
#include <PubSubClient.h>


const char* ssid = "";
const char* password = "";
const char* mqtt_server = "test.mosquitto.org";
char msg[50];

WiFiClient espClient;
PubSubClient client(espClient);


void setup_wifi(){
  delay(10);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void reconnect(){
  while (!client.connected()){
    if (!client.connect("SW")){
      Serial.print("Failed, rc=");
      Serial.print(client.state());
      delay(5000);
    }
  }
}

void wakeUp(){
  Serial.println("Waking up");
  delay(3000);
  Serial.println("Morning!");
  digitalWrite(LED_BUILTIN, HIGH); //LED goes on again cause the Arduino woke up
}


void setup(){
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  pinMode(A0, INPUT);
  pinMode(LED_BUILTIN, OUTPUT); //we're using built-in LED to demonstrate the sleep mode
  digitalWrite(LED_BUILTIN, LOW);
}


void loop(){
  if (!client.connected()){
    reconnect();
  }
  digitalWrite(LED_BUILTIN, HIGH);
  client.loop();
  delay(1000);
  int sensorValue = analogRead(A0);
  float voltage = sensorValue * (5.0 / 1023.0);
  snprintf(msg, 50, "%f", voltage);
  client.publish("SW", msg);
  if (voltage <= 1.5){ 
    Serial.println("Going to sleep");
    delay(1000);
    ESP.deepSleep(50e5);
    wakeUp();
    } 
}
