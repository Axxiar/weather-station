#include <DHT.h> // DHT sensor library by Adafruit
#include <RTClib.h>  // RTClib by Adafruit
 
RTC_DS3231 rtc;
 
#define DHTPIN 2
#define DHTTYPE DHT11
 
DHT dht(DHTPIN, DHTTYPE);
const int ldrPin = A0;
 
void setup()
{
  Serial.begin(9600);
  dht.begin();
  if (!rtc.begin())
  {
    Serial.println("Couldn't find RTC");
    while (1);
  }
  // rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); // adjust RTC time, first upload only
}
 
 
void loop()
{
  // Read light level
  // 🌑 Dark: 0–200
  // 🌥️ Dim room: 200–600
  // ☀️ Bright light: 600–1023
  int lightValue = analogRead(ldrPin);
 
  // Read DHT11
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();
 
  // Check if reading failed
  if (isnan(humidity) || isnan(temperature))
    Serial.println("Failed to read from DHT11!");
  else
  {
    DateTime now = rtc.now();
 
    Serial.print(now.day());
    Serial.print("/");
    Serial.print(now.month());
    Serial.print("/");
    Serial.print(now.year());
 
    Serial.print(" ");
 
    if (now.hour() < 10) Serial.print("0");
    Serial.print(now.hour());
    Serial.print(":");
 
    if (now.minute() < 10) Serial.print("0");
    Serial.print(now.minute());
    Serial.print(":");
 
    if (now.second() < 10) Serial.print("0");
    Serial.print(now.second());
 
    Serial.println();
 
 
 
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.print(" °C");
 
    Serial.print(" | Humidity: ");
    Serial.print(humidity);
    Serial.print(" %");
 
    Serial.print(" | Light: ");
    Serial.println(lightValue);
  }
 
  delay(2000);
}
 
