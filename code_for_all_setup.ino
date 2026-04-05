#include "DHT.h"
#include <ESP32Servo.h>
#include <TinyGPS++.h>

// ================== PIN DEFINITIONS ==================
#define DHTPIN 4       
#define DHTTYPE DHT11
#define FLAME_PIN 13   
#define SMOKE_PIN 34   
#define BUZZER_PIN 25  
#define SERVO_PIN 26   

// GPS RX TX
#define GPS_RX 16
#define GPS_TX 17

// SIM800 RX TX
#define SIM800_RX 27   
#define SIM800_TX 14

// RECEIVER PIN (NEW)
#define RX_PIN 35   

DHT dht(DHTPIN, DHTTYPE);
Servo dropperServo;

TinyGPSPlus gps;
HardwareSerial gpsSerial(2);
HardwareSerial sim800(1);

// ================== SETTINGS ==================
int closedAngle = 0;   
int openAngle = 90;    
int smokeThreshold = 1200;

// Prevent multiple SMS
bool alertSent = false;

// Receiver control
int receiverPulse = 0;
bool manualOverride = false;

void setup() {
  Serial.begin(115200);

  pinMode(FLAME_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(RX_PIN, INPUT);   // NEW

  dht.begin();

  dropperServo.attach(SERVO_PIN);
  dropperServo.write(closedAngle);

  // GPS start
  gpsSerial.begin(9600, SERIAL_8N1, GPS_RX, GPS_TX);

  // SIM800 start
  sim800.begin(9600, SERIAL_8N1, SIM800_RX, SIM800_TX);
  delay(1000);

  sim800.println("AT");
  delay(1000);
  sim800.println("AT+CMGF=1");
  delay(1000);

  Serial.println("🔥 Fire Detector + GPS + SMS + MANUAL CONTROL Started...");
}

void loop() {

  // ================= SENSOR READ =================
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();
  int flameValue = digitalRead(FLAME_PIN);
  int smokeValue = analogRead(SMOKE_PIN);

  // ================= GPS READ =================
  while (gpsSerial.available()) {
    gps.encode(gpsSerial.read());
  }

  double lat = gps.location.lat();
  double lng = gps.location.lng();

  // ================= RECEIVER READ =================
  receiverPulse = pulseIn(RX_PIN, HIGH, 25000);

  if (receiverPulse > 1500) {
    manualOverride = true;
  } else {
    manualOverride = false;
  }

  // ================= ERROR CHECK =================
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("⚠️ Failed to read from DHT sensor!");
  }

  // ================= GRAPH OUTPUT =================
  Serial.print(smokeValue);
  Serial.print(",");
  Serial.print(temperature);
  Serial.print(",");
  Serial.println(humidity);

  // ================= TEXT OUTPUT =================
  Serial.print("Temp: ");
  Serial.print(temperature);
  Serial.print(" | Smoke: ");
  Serial.print(smokeValue);
  Serial.print(" | Humidity: ");
  Serial.print(humidity);

  Serial.print(" | GPS: ");
  Serial.print(lat, 6);
  Serial.print(",");
  Serial.println(lng, 6);

  Serial.print(" | Receiver: ");
  Serial.println(receiverPulse);

  // ================= FIRE / MANUAL DETECTION =================
  if (((flameValue == LOW || smokeValue > smokeThreshold) || manualOverride) && !alertSent) {

    Serial.println("🚨 EMERGENCY / MANUAL TRIGGER!");

    digitalWrite(BUZZER_PIN, HIGH);

    delay(500);

    // Servo drop
    dropperServo.write(openAngle);  
    delay(2000);                    
    dropperServo.write(closedAngle);

    // ================= SMS SEND =================
    String message = "🔥 FIRE ALERT!\nLocation:\nhttps://maps.google.com/?q=" 
                     + String(lat, 6) + "," + String(lng, 6);

    sim800.println("AT+CMGS=\"+919974620709\"");
    delay(2000);

    sim800.print(message);
    delay(200);

    sim800.write(26);
    delay(5000);

    Serial.println("📩 SMS Sent!");

    alertSent = true;
  }

  // ================= SAFE =================
  else if (!manualOverride && flameValue != LOW && smokeValue <= smokeThreshold) {

    digitalWrite(BUZZER_PIN, LOW);
    alertSent = false;

    Serial.println("✅ Safe");
  }

  delay(2000);
}