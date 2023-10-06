//barcode
#include <SoftwareSerial.h>

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
#define OLED_RESET D2
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT,
  OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);

SoftwareSerial mySerial(D7, D8);

// Wifi
const char* ssid     = "";
const char* username = "";
const char* password = "";

//set the port to unity as 80
WiFiServer server(80);
WiFiClient client;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  mySerial.begin(9600);
  //Serial.println("Start");

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

char data[1500];
int ind = 0;
int i = 0;
String a;
char temp;

void loop() {
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

      //client.flush();

      /*for(int j=0;j < ind; j++)
      {
        Serial.print(data[j]);
      }*/

      //Serial.print("\n");
      //ind = 0;
      //h = dht.readHumidity();
      //t = dht.readTemperature();
      while (mySerial.available()) {
          if (i < 3)
          {
            temp = mySerial.read();
            //Serial.write(temp);
            //Serial.println();
            client.write(temp);
            a += Serial.write(temp);
            i = i+1;
          }
      }
      
      if (i == 3)
        {
          client.print('\r');    
          Serial.println(a);
          a = ""; 
          i =0;
        }
        
      
      
      //client.print(h); //在client端回复
      //client.print('\r');
      //client.print(t); //在client端回复
      //client.print('\r');
      //delay(1000);
    }

  }
}

/*char a[5];
int i = 0;

void loop() {
  // put your main code here, to run repeatedly:
  while (mySerial.available()) {
          a[i] = Serial.write(mySerial.read());
          i = i+1;
  }
      
  if (i == 5){
    for (int j =0; j<5; j++)
      {
        if (j < 4 )
          Serial.print(a[j]);
        else Serial.println(a[j]);
       }
     i =0;
  }
}*/
