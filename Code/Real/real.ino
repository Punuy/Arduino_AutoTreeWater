#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <Wire.h>
#include <BlynkSimpleEsp8266.h>
#include <BH1750FVI.h>
#include <DHT.h>   

char auth[] = ""; // Token
char ssid[] = ""; // Wi-Fi Name
char pass[] = ""; // SSiD

#define DHTPIN 14 // D5
#define DHTTYPE DHT11

BH1750FVI LightSensor(BH1750FVI::k_DevModeContLowRes);

DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;
 
void sendSensor() {
  float h = dht.readHumidity();
  float t = dht.readTemperature(); // or dht.readTemperature(true) for Fahrenheit
 
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V0, t);
  Blynk.virtualWrite(V1, h);
  Serial.print(h);
  Serial.println(" h");
  Serial.print(t);
  Serial.println(" t");
}

void setup() {
  Serial.begin(115200);
  Wire.begin();
  Blynk.begin(auth, ssid, pass, "muhaha.ddns.net", 8080);
  LightSensor.begin();
  dht.begin();
  timer.setInterval(1000L, sendSensor);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
}

void loop() {
  timer.run();
  Blynk.run();
  Blynk.virtualWrite(12,HIGH);
  Blynk.virtualWrite(13,HIGH);
  uint16_t lux = LightSensor.GetLightIntensity();j
  Serial.print("Light: ");
  Serial.print(lux);
  Serial.println(" lux");
  Blynk.virtualWrite(V3, lux);
  delay(500);
}