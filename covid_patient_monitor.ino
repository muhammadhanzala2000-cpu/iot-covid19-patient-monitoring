#include <Wire.h>
#include "MAX30100_PulseOximeter.h"
#include <SimpleTimer.h>
#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <LiquidCrystal_I2C.h>
#include "DHT.h"

#define DHTPIN 18
#define DHTTYPE DHT11

const int heartPin = 34;

// Replace with your own credentials. Never upload real tokens publicly.
char auth[] = "YOUR_BLYNK_AUTH_TOKEN";
char ssid[] = "YOUR_WIFI_NAME";
char pass[] = "YOUR_WIFI_PASSWORD";

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 16, 4);
WidgetLCD lcd1(V5);

#define ADC_VREF_mV 5000.0
#define ADC_RESOLUTION 4096.0
#define PIN_LM35 36

SimpleTimer timer;
PulseOximeter pox;
uint32_t tsLastReport = 0;
uint32_t tempReport = 0;

BLYNK_WRITE(V6)
{
  String text = param.asStr();
  Serial.print(text + "\n");
  lcd.clear();
  lcd.setCursor(1, 1);
  lcd.print(text);
  delay(10000);
}

void setup()
{
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass, "blynk.iot-cm.com", 8080);
  lcd.begin();
  lcd.backlight();
  dht.begin();
  pox.begin();
  Serial.print("Initializing Pulse Oximeter..");
  if (!pox.begin()) {
    Serial.println("FAILED");
    for (;;);
  } else {
    Serial.println("SUCCESS");
  }
  timer.setInterval(2000L, bpm);
  timer.setInterval(1000L, ecg);
  timer.setInterval(1000L, btemp);
  timer.setInterval(1000L, rtemp);
}

void loop()
{
  pox.update();
  Blynk.run();
  timer.run();
}

void bpm()
{
  pox.update();
  lcd.setCursor(0, 0);
  lcd.print("BPM:");
  lcd.print(int(pox.getHeartRate()));
  lcd.setCursor(6, 0);
  lcd.print(" SpO2:");
  lcd.print(pox.getSpO2());
  lcd.print("%");
  Blynk.virtualWrite(V0, int(pox.getHeartRate()));
  Blynk.virtualWrite(V1, pox.getSpO2());
  Serial.print("BPM");
  Serial.print(int(pox.getHeartRate()));
  Serial.print(" Sp02");
  Serial.print(pox.getSpO2());
}

void ecg()
{
  pox.update();
  int heartValue = analogRead(heartPin);
  Blynk.virtualWrite(V5, heartValue);
}

void btemp()
{
  pox.update();
  int adcVal = analogRead(PIN_LM35);
  int milliVolt = adcVal * (ADC_VREF_mV / ADC_RESOLUTION);
  int tempC = (milliVolt / 10);
  lcd.setCursor(0, 1);
  lcd.print("Body Temp:");
  lcd.print(tempC);
  lcd.print("\337C");
  Blynk.virtualWrite(V2, tempC);
  Serial.print(" Body Temperature");
  Serial.print(tempC);
}

void rtemp()
{
  pox.update();
  int h = dht.readHumidity();
  int t = dht.readTemperature();
  lcd.setCursor(16, 0);
  lcd.print("Humidity: ");
  lcd.print(h);
  lcd.print("%");
  lcd.setCursor(16, 1);
  lcd.print("Room Temp: ");
  lcd.print(t);
  lcd.print("\337C");
  Blynk.virtualWrite(V4, h);
  Blynk.virtualWrite(V3, t);
  Serial.print(" humidity");
  Serial.print(h);
  Serial.print(" room temp");
  Serial.println(t);
}
