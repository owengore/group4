#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <SPIFFS.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <SPIFFS.h>
#include <Adafruit_Sensor.h>
#include "DHT.h"
#include <Adafruit_BMP280.h>
#include <Wire.h>
#include <SPI.h>
#define DHTPIN 4
#define DHTTYPE DHT22
//#define factor 1000000
//#define sleep_time 30
DHT dht(DHTPIN, DHTTYPE);

#define BMP_SCK 13
#define BMP_MISO 12
#define BMP_MOSI 11
#define BMP_CS 10


Adafruit_BMP280 bmp; // I2C
//Adafruit_BME280 bme(BME_CS); // hardware SPI
//Adafruit_BME280 bme(BME_CS, BME_MOSI, BME_MISO, BME_SCK); // software SPI

// Replace with your network credentials
const char* ssid = "HUAWEI Mate 10 Pro";
const char* password = "Group4Uni";

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

String readBMP280Pressure() {
//  // Read temperature as Celsius (the default)
float p = bmp.readPressure();
//  // Convert temperature to Fahrenheit
//  //t = 1.8 * t + 32;
  if (isnan(p)) {    
    Serial.println("Failed to read from BMP280 sensor!");
    return "";
  }
  else {
    Serial.println(p);
    return String(p);
  }
} 
//String readBME280Humidity() {
//  float h = bme.readHumidity();
//  if (isnan(h)) {
//    Serial.println("Failed to read from BME280 sensor!");
//    return "";
//  }
//  else {
//    Serial.println(h);
//    return String(h);
//  }
//}
//
//String readBME280Pressure() {
//  float p = bme.readPressure() / 100.0F;
//  if (isnan(p)) {
//    Serial.println("Failed to read from BME280 sensor!");
//    return "";
//  }
//  else {
//    Serial.println(p);
//    return String(p);
//  }
//}
String readDHT22Temperature() {
  float t = dht.readTemperature();
  if (isnan(t)) {
    Serial.println("Failed to read from DHT22 sensor!");
    return "";
  }
  else {
    Serial.println(t);
    return String(t);
  }
}
String readDHT22Humidity() {
  float h = dht.readHumidity ();
  if (isnan(h)) {
    Serial.println("Failed to read from DHT22 sensor!");
    return "";
  }
  else {
    Serial.println(h);
    return String(h);
  }
}
//  float h= dht.readHumidity();
//  float t= dht.readTemperature();
void setup(){
  // Serial port for debugging purposes
  Serial.begin(115200);
  Serial.print("DHT22 Test!");
  dht.begin();
  bool status; 
  // default settings
  // (you can also pass in a Wire library object like &Wire2)
  status = bmp.begin(0x76);  
  if (!status) {
    Serial.println("Could not find a valid BMP280 sensor, check wiring!");
    while (1);
  }

  // Initialize SPIFFS
  if(!SPIFFS.begin()){
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }

  // Print ESP32 Local IP Address
  Serial.println(WiFi.localIP());

  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/index.html");
  });
  server.on("/temperature", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", readDHT22Temperature().c_str());
  });
  server.on("/humidity", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", readDHT22Humidity().c_str());
  });
  server.on("/pressure", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", readBMP280Pressure().c_str());
  });

  // Start server
  server.begin();
//  Serial.println("ESP32 going to Deep Sleep");
//  esp_sleep_enable_timer_wakeup(sleep_time*factor);
//  esp_deep_sleep_start();
}
 
void loop(){
  
}
