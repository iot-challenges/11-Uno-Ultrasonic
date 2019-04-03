/**
 *
 *****************************************************************
 * IOT Challenges - https://instagram.com/iotchallenges          *
 *****************************************************************
 * Evandro Fruhauf                                               *
 *  GitHub - https://github.com/evandrodp                        *
 *  LinkedIn - http://linkedin.com/in/evandrofruhauf             *
 *****************************************************************
 * This code can contain parts from other open-sources projects, *
 * whenever possible it will be quoted.                          *
 *****************************************************************
 *
 * Ultrasonic Sensor
 *
 * Challenge: Use the ultrasonic sensor to simulate a park assistant
 *
 * This code uses Servo library.
 * Source base: https://create.arduino.cc/projecthub/onyx/ultrasonic-sensor-alarm-1ec0f3
 *
**/
#include <Arduino.h>

// define Ultrasonic pins
#define sensorEcho 8
#define sensorTrig 9

//define buzzer and led
int buzzer = 6;
int led = 7;

//initialise vars
int durationSensor, distance, delayms;
int durationBuzzer = 200;

int readDistance();

void setup() {
  // Define the output and input objects(devices)
  pinMode(sensorEcho, INPUT);
  pinMode(sensorTrig, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(led, OUTPUT);
}

void loop() {
  distance = readDistance();
  // Ignore distance above 10 and below 0 cm
  if (distance > 10 || distance <= 0) {
    digitalWrite(buzzer,LOW);
    digitalWrite(led,LOW);
  } else {
    // turn the led on
    digitalWrite(led, HIGH);
    // play the buzzer
    tone(buzzer, 400, durationBuzzer);
    delayms = distance * 50;
    if (delayms >= durationBuzzer) {
      delay(durationBuzzer);
      digitalWrite(led, LOW);
      delay(delayms-durationBuzzer);
    }
  }
}

int readDistance() {
  digitalWrite(sensorTrig, HIGH);
  delayMicroseconds(10);
  digitalWrite(sensorTrig, LOW);
  durationSensor = pulseIn(sensorEcho, HIGH);
  return (durationSensor/2) / 29.1;
}