//--WIFI--
#include <ESP8266WiFi.h>
const char* ssid = "Dragonsreach";
const char* password = "no#lollygagging!1337";
WiFiClient nodeMCU;

//--MQTT--
#include <PubSubClient.h>
const char* mqtt_broker = "192.168.2.116";
const char* mqtt_clientID = "TopTerm";
PubSubClient client(nodeMCU);
const char* topicTemp = "top/term";
const char* topicHumid = "top/humid";

//-- DHT --
#include <DHT.h>
#define DHTPIN D3
#define DHTTYPE DHT11 //Select type of DHT sensor
DHT dht(DHTPIN, DHTTYPE);
int hum, tmp;

//--DISPLAY--
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// -- SET-UP --
void setup() {
    //Serial.begin(115200);
    //Set-up Display
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    display.setTextColor(WHITE);
    display.clearDisplay();
    //Set-up DHT
    dht.begin();
    connectWiFi();
    client.setServer(mqtt_broker, 1883);
}

// -- MAIN LOOP --
void loop() {
  if (!client.connected()){
    reconnectMQTT();
  }
  readTempHum();
  publishTempHumid();
  displayInfo();
}

// -- Auxiliary Functions --

// Config and Connect
void connectWiFi(){
  delay(10);
  display.setTextSize(2);
  display.setCursor(0,0);
  display.print("Connect");
  display.display();
  WiFi.begin(ssid, password);
  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    display.print(".");
    display.display();
  }
}

// Reconnect
void reconnectMQTT(){
  while (!client.connected()){
    client.connect(mqtt_clientID);
  }
}

//Show temp and hum on display
void displayInfo(){
  showOnDisplay("Temper: ",tmp,"C");
  showOnDisplay("Humdty:",hum,"%"); 
}

//Show on Display
void showOnDisplay(const char* text1, int measurm, const char* text2){
  display.clearDisplay();
  
  display.setTextSize(2);
  display.setCursor(0,0);
  display.print(text1);
  
  display.setTextSize(3);
  display.setCursor(20,20);
  display.print(measurm);
  display.print(text2);
  
  display.display();
  delay(2000);
}

//Publish Temp and Humid
void publishTempHumid(){
  client.publish(topicTemp, String(tmp).c_str(), true); 
  client.publish(topicHumid, String(hum).c_str(), true);
}

//Read temperature and humidity
void readTempHum(){
    hum = dht.readHumidity();
    tmp = dht.readTemperature();
    delay(2000);   
}
