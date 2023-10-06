#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include "user_interface.h"
#include "wpa2_enterprise.h"
#include <DHT.h>

//monitor
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

//monitor define
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_MOSI  D1
#define OLED_CLK   D0
#define OLED_DC    D3
#define OLED_CS    D4
#define OLED_RESET D5
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT,
  OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);

// Wifi and firebase
#define FIREBASE_HOST "dht-sensor-b6add.firebaseio.com"
#define FIREBASE_AUTH "uaJeEQJL2UbYSS0JtugPAaBu6nnuQ460XVwgKX8k"
const char* ssid     = "";
const char* username = "";
const char* password = "";

//set the port to unity as 26
WiFiServer server(80);
WiFiClient client;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  //initial monitor
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  
  // connect to wifi.
  wifi_set_opmode(0x01);
  struct station_config wifi_config;
  memset(&wifi_config, 0, sizeof(wifi_config));
  strcpy((char*)wifi_config.ssid, ssid);
  wifi_station_set_config(&wifi_config);
  wifi_station_clear_cert_key();
  wifi_station_clear_enterprise_ca_cert();
  wifi_station_set_wpa2_enterprise_auth(1);
  wifi_station_set_enterprise_identity((uint8*)username, strlen((char*)username));
  wifi_station_set_enterprise_username((uint8*)username, strlen((char*)username));
  wifi_station_set_enterprise_password((uint8*)password, strlen((char*)password));
  wifi_station_connect();

  display.begin(SSD1306_SWITCHCAPVCC, 0x78>>1);     // init done
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  //display.setTextColor(BLACK, WHITE); // 'inverted' text
  display.setCursor(0,0);
  display.println("Connecting");
  
  //For checking wifi connection
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    display.print(".");
    display.display();
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  //output IP address on the monitor
  display.clearDisplay();    
  display.setTextSize(2);       
  display.setTextColor(WHITE);  
  display.setCursor(0,0);       
  display.print("SSID:"); 
  display.println(ssid);  
  display.setTextSize(2);      
  display.setTextColor(WHITE); 
  display.setCursor(0,18);      
  display.println(WiFi.localIP());
  display.display();

  // Start the TCP server
  server.begin();
}

#define DHTTYPE DHT11

// DHT Sensor
const int DHTPin = D7;

// Initialize DHT sensor.
DHT dht(DHTPin, DHTTYPE);

static char celsiusTemp[7];
static char fahrenheitTemp[7];
static char humidityTemp[7];

char data[1500];
int ind = 0;
float h = 0;
float t = 0;

void loop() {
    // put your main code here, to run repeatedly:
    if(!client.connected())
  {
    //try to connect to a new client
    client = server.available();
  }
  else
  {
    if(client)
    {
      //Serial.println("Connected to client");
      h = dht.readHumidity();
      t = dht.readTemperature();

      /*while(client.available())
      {
        data[ind] = client.read(); //读取client端发送的字符
        ind++;
      }
      client.flush();

      for(int j=0;j < ind; j++)
      {
        Serial.print(data[j]);
      }

      Serial.print("\n");
      ind = 0;*/
      client.print(h); //在client端回复
      client.print('\r');
      client.print(t); //在client端回复
      client.print('\r');
      delay(1000);
    }

  }
}

/*void loop() {
    // put your main code here, to run repeatedly:
    if(!client.connected())
  {
    //try to connect to a new client
    client = server.available();
  }
  else
  {
    if(client.connected())
    {

      client.flush();

      for(int j=0;j < ind; j++)
      {
        Serial.print(data[j]);
      }

      Serial.print("\n");
      ind = 0;
      float h = dht.readHumidity();
      client.print(h); //在client端回复
    }

  }
}*/
/*void loop(){
  client = server.available();
  
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (client){
  Serial.println("Client connected");
    while (client.connected())
    {
  client.flush();
  Serial.println(h);
  Serial.println(t);
  client.print(h);
  client.print('\r');
  delay(100);
    }
  }
  
}*/

/*void loop() {
  // put your main code here, to run repeatedly:
   client = server.available();

  if (client){
    Serial.println("Client connected");
    while (client.connected()){
      //read information from DHT sensor
      float h = dht.readHumidity();
      float t = dht.readTemperature();
      float f = dht.readTemperature(true);
      long tr = 123;
    
      client.write(tr);
      client.print('\r');
      Serial.println(tr);
      Serial.println(h);
      Serial.println(t);
      delay(100);
      }
    }
}*/
