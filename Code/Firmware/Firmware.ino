#define BLYNK_TEMPLATE_ID           "ID"
#define BLYNK_DEVICE_NAME           "NAME"
#define BLYNK_AUTH_TOKEN            "TOKEN"

#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include "DHT.h"

char auth[] = BLYNK_AUTH_TOKEN; 
char ssid[] = "WIFI";
char pass[] = "PASSWORD";

BlynkTimer timer;
DHT dht;

BLYNK_WRITE(V0)
{
  int value = param.asInt();

  Blynk.virtualWrite(V1, value);
  
}

BLYNK_CONNECTED()
{
  Blynk.setProperty(V3, "offImageUrl", "https://static-image.nyc3.cdn.digitaloceanspaces.com/general/fte/congratulations.png");
  Blynk.setProperty(V3, "onImageUrl",  "https://static-image.nyc3.cdn.digitaloceanspaces.com/general/fte/congratulations_pressed.png");
  Blynk.setProperty(V3, "url", "https://docs.blynk.io/en/getting-started/what-do-i-need-to-blynk/how-quickstart-device-was-made");
}

void myTimerEvent()
{
  delay(dht.getMinimumSamplingPeriod());
  float humidity = dht.getHumidity(); // ความชื้น
  float temperature = dht.getTemperature(); // อุณหภูมิ

  Blynk.virtualWrite(V2, millis() / 1000);
  Blynk.virtualWrite(V5, humidity);
  Blynk.virtualWrite(V6, temperature);
}

void setup()
{
  Serial.begin(115200);
  dht.setup(2);
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(1000L, myTimerEvent);
}

void loop()
{
  Blynk.run();
  timer.run();
}

