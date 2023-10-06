#include <ESP8266WiFi.h>
#include "user_interface.h"
#include "wpa2_enterprise.h"

//monitor
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

//web
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

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

//direction control
const int f = D5;// the number of the output pin
const int b = D6;
const int l = D8;
const int r = D7;


//set the port to unity as 26
WiFiServer server(80);
WiFiClient client;

// Wifi and firebase
const char* ssid     = "";
const char* username = "";
const char* password = "";

void setup() {
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

  //light
  pinMode(f, OUTPUT);
  pinMode(l, OUTPUT);
  pinMode(r, OUTPUT);
  pinMode(b, OUTPUT);

  digitalWrite(f, HIGH);
  digitalWrite(l, HIGH);
  digitalWrite(r, HIGH);
  digitalWrite(b, HIGH);
}

  char data[1500];
  int ind = 0;
  String c;

void loop() {
    // put your main code here, to run repeatedly:
    if(!client.connected())
  {
    //try to connect to a new client
    client = server.available();
    digitalWrite(f, HIGH);
    digitalWrite(l, HIGH);
    digitalWrite(r, HIGH);
    digitalWrite(b, HIGH);
  }
  else
  {
    if(client.available() > 0)
    {
      Serial.println("Connected to client");
      c = "";
      
      while(client.available())
      {
        data[ind] = client.read(); //读取client端发送的字符
        c += data[ind];
        ind++;
      }
      client.flush();

      Serial.println(c);
      if ( c == "front")
      { 
        if (digitalRead(f) == LOW)
        { 
          digitalWrite(f , HIGH);
          Serial.println(digitalRead(f));
        }
        else {
              digitalWrite(f, LOW);
              Serial.println(digitalRead(f));
            }
      }
      
      if ( c == "back")
      { 
        if (digitalRead(b) == LOW)
        { 
          digitalWrite(b , HIGH);
          Serial.println(digitalRead(b));
        }
        else {
              digitalWrite(b, LOW);
              Serial.println(digitalRead(b));
            }
      }
      
      if ( c == "left")
      { 
        if (digitalRead(l) == LOW)
        { 
          digitalWrite(l , HIGH);
          Serial.println(digitalRead(l));
        }
        else {
              digitalWrite(l, LOW);
              Serial.println(digitalRead(l));
            }
      }

      if ( c == "right")
      { 
        if (digitalRead(r) == LOW)
        { 
          digitalWrite(r , HIGH);
          Serial.println(digitalRead(r));
        }
        else {
              digitalWrite(r, LOW);
              Serial.println(digitalRead(r));
            }
      }
      
      ind = 0;
      client.print("OK! Got your request."); //在client端回复
    }

  }
}
  
