#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "BIMAYURAISYAH";
const char* password = "rinisukemi";

const char* serverName = "http://192.168.100.12:5000/endpoint";

const int mq135AnalogPin = 22; // Analog pin connected to GPIO 22
const int mq135DigitalPin = 23; // Digital pin connected to GPIO 23

void setup() {
  // Initialize serial communication at 115200 baud rate
  Serial.begin(115200);
  
  // Configure the analog pin as input
  pinMode(mq135AnalogPin, INPUT);
  
  // Configure the digital pin as input
  pinMode(mq135DigitalPin, INPUT);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to Wi-Fi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("Connected to Wi-Fi");
}

void loop() {
  // Read sensor data
  int sensorValue = analogRead(mq135AnalogPin);

  // Convert the sensor value to a meaningful value if needed
  float airQuality = sensorValue * (3.3 / 4095.0); // Example conversion

  // Create JSON payload
  String jsonPayload = "{\"air_quality\": " + String(airQuality) + "}";

  // Send HTTP POST request
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(serverName);
    http.addHeader("Content-Type", "application/json");

    int httpResponseCode = http.POST(jsonPayload);

    if (httpResponseCode > 0) {
      String response = http.getString();
      Serial.println(httpResponseCode);
      Serial.println(response);
    } else {
      Serial.print("Error on sending POST: ");
      Serial.println(httpResponseCode);
    }
    http.end();
  } else {
    Serial.println("WiFi not connected");
  }
  delay(60000); // Send data every minute
}
