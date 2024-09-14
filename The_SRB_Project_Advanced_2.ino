// SRB PROJECT BY ZIYAD WALID

// Device 1 info
#define BLYNK_TEMPLATE_ID "TMPL2fOUuXITO"
#define BLYNK_TEMPLATE_NAME "SRB"
#define BLYNK_AUTH_TOKEN "g99TrlZAQbcrLGKZ5pUErXbmjWRvZKYK"

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial

// Libraries
#include <Servo.h>
#include <ESP8266_Lib.h>
#include <BlynkSimpleShieldEsp8266.h>

// Your WiFi credentials.
char ssid[] = "Ziyad Walid";
char pass[] = "ZIYAD_WALID";

// Software Serial on Uno, Nano...
#include <SoftwareSerial.h>
SoftwareSerial EspSerial(2, 3); // RX, TX

// Your ESP8266 baud rate:
#define ESP8266_BAUD 115200

ESP8266 wifi(&EspSerial);

// Create a servo motor object
Servo myServo;

// First ultrasonic sensor pins
const int triggerPin = 4;
const int echoPin = 5;
const int redLedPin = 6;
const int yellowLedPin = 7;
const int greenLedPin = 8;

// Second ultrasonic sensor pins
const int triggerPin2 = 9;
const int echoPin2 = 10;
const int servoPin = 11;

// Servo position constants
const int closedPos = 180;
const int openPos = 0;

// Global variables
int distance1;
int distance2;
bool trashOpen = false;

BlynkTimer timer;

void myTimer() {
  Blynk.virtualWrite(V0, distance1);   // Update Blynk app with distance
  Blynk.virtualWrite(V1, map(distance1, 0, 21, 100, 0));  // Update Blynk app with percentage
  Blynk.virtualWrite(V2, myServo.read());  // Update Blynk app with servo angle
}

BLYNK_WRITE(V3) {
  int openCommand = param.asInt();
  if (openCommand == 1 && !trashOpen) {
    openCloseTrash(true);
  } else if (openCommand == 0 && trashOpen) {
    openCloseTrash(false);
  }
}

void setup() {
  // Debug console
  Serial.begin(115200);
  
  // Set ESP8266 baud rate
  EspSerial.begin(ESP8266_BAUD);
  delay(10);

  Blynk.begin(BLYNK_AUTH_TOKEN, wifi, ssid, pass);

  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(redLedPin, OUTPUT);
  pinMode(yellowLedPin, OUTPUT);
  pinMode(greenLedPin, OUTPUT);

  pinMode(triggerPin2, OUTPUT);
  pinMode(echoPin2, INPUT);

  myServo.attach(servoPin);

  // Close Dustbin by default
  myServo.write(closedPos);

  // Send sensor data every 1 second
  timer.setInterval(1000L, myTimer);
}

void loop() {
  Blynk.run();
  timer.run();

  // Measure distance for first ultrasonic sensor
  distance1 = measureDistance(triggerPin, echoPin);

  // Check percentage range and control LEDs accordingly for the first ultrasonic sensor
  checkPercentage(distance1);

  // Measure the distance for the second ultrasonic sensor
  distance2 = measureDistance(triggerPin2, echoPin2);

  // Open and Close Logic
  if (distance2 >= 0 && distance2 <= 20)
    openCloseTrash(true);
  else
    openCloseTrash(false);

  delay(1000); // Delay for a moment to avoid too frequent readings
}

int measureDistance(int triggerPin, int echoPin) {
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  return (pulseIn(echoPin, HIGH) * 0.0343) / 2;
}

void checkPercentage(int distance) {
  int percentage = map(distance, 0, 21, 100, 0);

  if (percentage >= 75)
    ledControl(redLedPin, HIGH, yellowLedPin, LOW, greenLedPin, LOW);
  else if (percentage <= 20)
    ledControl(redLedPin, LOW, yellowLedPin, LOW, greenLedPin, HIGH);
  else
    ledControl(redLedPin, LOW, yellowLedPin, HIGH, greenLedPin, LOW);
}

void openCloseTrash(bool open) {
  unsigned long previousMillis = millis();
  int targetPos = open ? openPos : closedPos;
  int currentPos = myServo.read();
  int increment = open ? -1 : 1;

  while (currentPos != targetPos) {
    if (millis() - previousMillis >= 10) {
      currentPos += increment;
      myServo.write(currentPos);
      previousMillis = millis();
    }
  }

  trashOpen = open;
}

void ledControl(int redPin, int redState, int yellowPin, int yellowState, int greenPin, int greenState) {
  digitalWrite(redPin, redState);
  digitalWrite(yellowPin, yellowState);
  digitalWrite(greenPin, greenState);
}
