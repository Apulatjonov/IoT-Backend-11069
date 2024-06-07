#include <SPI.h>
#include <MFRC522.h>

const int trigPin = 9;
const int echoPin = 8;

void setup() {
  Serial.begin(9600);  // Initialize serial communications with the PC
  pinMode(trigPin, OUTPUT); // Set the trigPin as an OUTPUT
  pinMode(echoPin, INPUT);  // Set the echoPin as an INPUT
}

void loop() {
  long duration;
  int distance;
  
  // Clear the trigPin by setting it LOW for 2 microseconds
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  // Set the trigPin HIGH for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Read the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  
  // Calculate the distance
  distance = duration * 0.034 / 2;
  
  // Print the distance to the Serial Monitor
  // Serial.print(distance);
  // Serial.println(" cm");
  
  // Send the distance to ESP32
  Serial.print(distance);
  Serial.println();

  delay(3000); // Wait for a half second before measuring again
}
