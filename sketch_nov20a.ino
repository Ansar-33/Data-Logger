#include <SPI.h>
#include <SD.h>
#include "DHT.h"
#include <Wire.h>
#include <RTClib.h>

// --- DHT11 Settings ---
#define DHTPIN 16
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// --- SD Card ---
#define CS_PIN 17
bool sdAvailable = false;

// --- RTC ---
RTC_DS1307 rtc;

// Create timestamp string
String getTimestamp(DateTime now) {
  char buffer[25];
  sprintf(buffer, "%04d-%02d-%02d %02d:%02d:%02d",
          now.year(), now.month(), now.day(),
          now.hour(), now.minute(), now.second());
  return String(buffer);
}

// Safe DHT read
void safeDHTRead(float &t, float &h) {
  h = dht.readHumidity();
  t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    delay(300);
    h = dht.readHumidity();
    t = dht.readTemperature();
  }
}

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("\n--- ESP32 DHT11 + DS1307 + SD Data Logger ---");

  Wire.begin(21, 22);   
  

  // RTC INIT
  if (!rtc.begin()) {
    Serial.println("ERROR: RTC NOT detected!");
    while (1);
  }

  if (!rtc.isrunning()) {
    Serial.println("RTC not running → setting compile time");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));   // SET RTC TIME (Step 1)
  }

  Serial.println("RTC OK.");
  delay(200);

  // SD INIT
  if (SD.begin(CS_PIN)) {
    sdAvailable = true;
    Serial.println("SD Card Ready.");

    if (!SD.exists("/datalog.txt")) {
      File f = SD.open("/datalog.txt", FILE_WRITE);
      if (f) {
        f.println("Timestamp, Temperature (C), Humidity (%)");
        f.close();
        Serial.println("Created log file.");
      }
    }
  } else {
    sdAvailable = false;
    Serial.println("SD Card NOT Detected. Skipping SD logging.");
  }

  dht.begin();
  Serial.println("DHT11 initialized.\n");
}

void loop() {
  float temperature = 0, humidity = 0;
  safeDHTRead(temperature, humidity);

  DateTime now = rtc.now();
  String timestamp = getTimestamp(now);

  String logLine;
  if (isnan(humidity) || isnan(temperature)) {
    logLine = timestamp + ", ERROR, ERROR";
  } else {
    logLine = timestamp + ", " + String(temperature, 1) + ", " + String(humidity, 1);
  }

  Serial.println(logLine);

  if (sdAvailable) {
    File dataFile = SD.open("/datalog.txt", FILE_APPEND);
    if (dataFile) {
      dataFile.println(logLine);
      dataFile.close();
    } else {
      Serial.println("ERROR: SD Write Failed.");
      sdAvailable = false;
    }
  }

  delay(2000);
}
