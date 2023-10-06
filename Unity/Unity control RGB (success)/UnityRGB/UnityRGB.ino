#include <ESP8266WiFi.h>
#include "user_interface.h"
#include "wpa2_enterprise.h"

//web
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

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

//light
const int b = 12;// the number of the LED pin
const int g = 13;
const int r = 15;


//set the port to unity as 26
WiFiServer server(80);
WiFiClient client;

// Wifi and firebase
const char* ssid     = "HKU";
const char* username = "u3527836@hku.hk";
const char* password = "davidCHU1997";

void setup() {
  Serial.begin(115200);

  //initial monitor
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  display.clearDisplay();
  
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

  //For checking wifi connection
  display.begin(SSD1306_SWITCHCAPVCC, 0x78>>1);     // init done
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  //display.setTextColor(BLACK, WHITE); // 'inverted' text
  display.setCursor(0,0);
  display.println("Connecting");
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    display.print(".");
    display.display();
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());

  //output IP address on the monitor
  display.clearDisplay();
  display.setTextSize(2);      // Normal 1:1 pixel scale
  display.setTextColor(WHITE); // Draw white text
  display.setCursor(0, 0);     // Start at top-left corner
  display.cp437(true);         // Use full 256 char 'Code Page 437' font
  display.print("SSID:"); 
  display.println(ssid);
  display.print(WiFi.localIP());
  display.display();
  delay(5000);

  // Start the TCP server
  server.begin();

  //light
  pinMode(b, OUTPUT);
  pinMode(g, OUTPUT);
  pinMode(r, OUTPUT);

  digitalWrite(b, LOW);
  digitalWrite(g, LOW);
  digitalWrite(r, LOW);
}

  float blue = 0;
  float green = 0;
  float red = 0;

  char data[1500];
  int ind = 0;
  String c;

void loop() {
    // put your main code here, to run repeatedly:
    if(!client.connected())
  {
    //try to connect to a new client
    client = server.available();
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
      if ( c == "blue")
      { 
        if (digitalRead(b) == LOW)
        { 
          digitalWrite(b , HIGH);
        }
        else {
              digitalWrite(b, LOW);
            }
      }
      
      if ( c == "green")
      { 
        if (digitalRead(g) == LOW)
        { 
          digitalWrite(g , HIGH);
        }
        else {
              digitalWrite(g, LOW);
            }
      }
      
      if ( c == "red")
      { 
        if (digitalRead(r) == LOW)
        { 
          digitalWrite(r , HIGH);
        }
        else {
              digitalWrite(r, LOW);
            }
      }
      
      ind = 0;
      client.print("OK! Got your request."); //在client端回复
    }

  }
}
  
