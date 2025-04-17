#include <WiFi.h>
#include <WiFiClient.h>
#include <HTTPClient.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

int counter = 0;
LiquidCrystal_I2C lcd(0x27, 16, 2);

WiFiClient client;
HTTPClient http;

String url;
String API = "YOUR_API_KEY";
int fieldno = 1;

#define inSensor 18
#define outSensor 19
#define relay 2
#define backlightPin 9

int countin = 0;
int countout = 0;
int now;

unsigned long inSensorDebounce = 0;
unsigned long outSensorDebounce = 0;
unsigned long debounceDelay = 2000;

void connectToWifi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin("SSID", "PASSWORD");
  while (WiFi.status() != WL_CONNECTED) {
    delay(200);
  }
}

void setup() {
  Wire.begin(21, 22);
  Serial.begin(115200);
  connectToWifi();

  lcd.begin(16, 2);
  lcd.backlight();
  lcd.print("Initializing..");
  delay(2000);
  lcd.clear();

  pinMode(inSensor, INPUT);
  pinMode(outSensor, INPUT);
  pinMode(relay, OUTPUT);
  digitalWrite(relay, HIGH);
}

void loop() {
  SendGetRequest(now);
  delay(1000);

  unsigned long currentMillis = millis();
  if (digitalRead(inSensor) == LOW && currentMillis - inSensorDebounce > debounceDelay) {
    countin++;
    inSensorDebounce = currentMillis;
  }

  if (digitalRead(outSensor) == LOW && currentMillis - outSensorDebounce > debounceDelay) {
    countout++;
    outSensorDebounce = currentMillis;
  }

  now = countin - countout;
  if (now < 0) now = 0;

  digitalWrite(relay, now > 0 ? HIGH : LOW);
  lcd.setCursor(0, 0); lcd.print("Total person:");
  lcd.setCursor(0, 1); lcd.print(now);
  delay(1000); lcd.clear();
}

void SendGetRequest(int data) {
  url = "http://api.thingspeak.com/update?api_key=" + API + "&field" + fieldno + "=" + String(data);
  http.begin(client, url);
  http.GET();
  http.end();
}
