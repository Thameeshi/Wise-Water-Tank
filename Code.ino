#include <HTTPClient.h>
#include <Ultrasonic.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <WiFi.h>
#include <ArduinoJson.h>
#include <time.h>

// Sensor Pin Definitions
#define TURBIDITY_SENSOR_PIN 34
#define FLOW_SENSOR_PIN 4
#define TEMPERATURE_SENSOR_PIN 32
#define MAIN_TANK_TRIG_PIN 18
#define MAIN_TANK_ECHO_PIN 19
#define SMALL_TANK_TRIG_PIN 22
#define SMALL_TANK_ECHO_PIN 23
#define WATER_LEVEL_SENSOR_PIN 33

// Relay Pin Definitions
const int RELAY_1_PIN = 13;
const int RELAY_2_PIN = 14;
const int RELAY_3_PIN = 27;

// Network Credentials
const char* ssid = "Galaxy M33 5G 31EF";
const char* password = "qebl8444";

// Firebase Credentials
const char* firebaseHost = "sajeewa-2e69e-default-rtdb.firebaseio.com";
const char* firebaseAuth = "AIzaSyDKI_u7Jd_40N_7C0o4tG2xGdsLI6xMwDM";

// Variables for water flow, temperature, and turbidity data
volatile unsigned long flowPulseCount = 0;
float flowRate = 0.0;
float totalLiters = 0.0;
float dailyLiters = 0.0;
float tempSum = 0.0;
int tempCount = 0;
float turbiditySum = 0.0;
int turbidityCount = 0;

// Timing Variables
unsigned long lastFlowCalcTime = 0;
unsigned long lastResetTime = 0;
unsigned long lastFirebaseUpdateTime = 0;
unsigned long last2HourUpdateTime = 0;

// Ultrasonic and Temperature Sensor Instances
Ultrasonic mainTankUltrasonic(MAIN_TANK_TRIG_PIN, MAIN_TANK_ECHO_PIN);
Ultrasonic smallTankUltrasonic(SMALL_TANK_TRIG_PIN, SMALL_TANK_ECHO_PIN);
OneWire oneWire(TEMPERATURE_SENSOR_PIN);
DallasTemperature sensors(&oneWire);

// Interrupt Service Routine for Flow Sensor
void IRAM_ATTR flowSensorISR() {
    flowPulseCount++;
}

// Setup Function
void setup() {
    Serial.begin(115200);
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Connecting to WiFi...");
    }
    Serial.println("Connected to WiFi");

    pinMode(RELAY_1_PIN, OUTPUT);
    pinMode(RELAY_2_PIN, OUTPUT);
    pinMode(RELAY_3_PIN, OUTPUT);
    pinMode(TURBIDITY_SENSOR_PIN, INPUT);

    digitalWrite(RELAY_1_PIN, HIGH);
    digitalWrite(RELAY_2_PIN, HIGH);
    digitalWrite(RELAY_3_PIN, HIGH);

    pinMode(FLOW_SENSOR_PIN, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(FLOW_SENSOR_PIN), flowSensorISR, RISING);
    pinMode(WATER_LEVEL_SENSOR_PIN, INPUT);

    configTime(19800, 0, "time.google.com");
    struct tm timeInfo;
    if (!getLocalTime(&timeInfo)) {
        Serial.println("Failed to obtain time");
        return;
    }

    sensors.begin();
}

// Helper Functions
float getWaterFlow();
void checkMidnight();
void remove();
void checkTur();
void fillMainTank();
void fillSmallTank();
void readSensorValue();
void updateStatusToFirebase();
void sendDataToFirebase();

// Main Loop
void loop() {
    unsigned long currentMillis = millis();
    if (currentMillis - lastFirebaseUpdateTime >= 2000) { // Update Firebase every 2 seconds
        updateStatusToFirebase();
        lastFirebaseUpdateTime = currentMillis;
    }
    readSensorValue();
}

// Other Helper Function Implementations

// Add the remaining function implementations here, ensuring each is well-documented.
