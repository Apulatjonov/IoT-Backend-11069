#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

const char* ssid = "iPhone Abdulaziz";
const char* password = "bbbbbbbb";

void setup() {
  Serial.begin(115200);
  Serial1.begin(9600);  // Start the serial communication with Arduino Uno

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
}

void loop() {
  // if (Serial1.available() > 0) {
    Serial.println("Data available from Serial1");
    // String distance = "";
    // while (Serial1.available()) {
    //   char incomingByte = Serial1.read();
    //   distance += incomingByte;
    // }
    String distance = Serial1.readStringUntil('\n');
    distance.trim();  // Remove any leading/trailing whitespace

    // if (distance.length() > 0) {
    HTTPClient http;
    http.begin("http://172.20.10.4:5000/sendNotification");
    http.addHeader("Content-Type", "application/json");
    http.setTimeout(20000);  // 20 seconds


    Serial.print("Sending data to server: ");
    Serial.println(distance);

    DynamicJsonDocument doc(1024);
    doc["distance"] = 12;

    // Convert JSON object to string
    String jsonString;
    serializeJson(doc, jsonString);

    int httpResponseCode = http.POST(jsonString);

    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    if (httpResponseCode > 0) {
      String response = http.getString();
      Serial.print("Response from server: ");
      Serial.println(response);
    } else {
      Serial.print("Error on sending POST: ");
      Serial.println(httpResponseCode);
    }

    http.end();
    // } else {
    //   Serial.println("Received empty string from Serial1");
    // }
    // delay(10000);
  // }
  delay(1000);  // Shorter delay to keep checking Serial1 more frequently
}
