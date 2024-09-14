// SRB PROJECT BY ZIYAD WALID

// device 1 info
#define BLYNK_TEMPLATE_ID "TMPL2fOUuXITO"
#define BLYNK_TEMPLATE_NAME "SRB"
#define BLYNK_AUTH_TOKEN "g99TrlZAQbcrLGKZ5pUErXbmjWRvZKYK"

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial

// libraries 
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

// first function
const int triggerPin = 4;
const int echoPin = 5;
const int redLedPin = 6;
const int yelloLedPin = 7;
const int greenLedPin = 8;

// second function
const int triggerPin2 = 9;
const int echoPin2 = 10;
const int servoPin = 11;
     
// servo postion
int servoPos;
const int closedPos =  180;
const int openPos = 0;

// Global variable 
int percentage = 0;
int distance1;
int distance2;
bool trashOpen = false;

BlynkTimer timer;

void myTimer(){
  Blynk.virtualWrite(V0, distance1); // Update Blynk app with distance
  Blynk.virtualWrite(V1, percentage); // Update Blynk app with percentage
  Blynk.virtualWrite(V2, servoPos); // Update Blynk app with servo angle   
}

BLYNK_WRITE(V3) {
  int openCommand = param.asInt();
  if (openCommand == 1 && !trashOpen) {
    openTrash();
  } else if (openCommand == 0 && trashOpen) {
    closeTrash();
  }
}

void setup()
{
  // Debug console
  Serial.begin(115200);
  
  // Set ESP8266 baud rate
  EspSerial.begin(ESP8266_BAUD);
  delay(10);

  Blynk.begin(BLYNK_AUTH_TOKEN, wifi, ssid, pass);

  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(redLedPin, OUTPUT);
  pinMode(yelloLedPin, OUTPUT);
  pinMode(greenLedPin, OUTPUT);

  pinMode(triggerPin2, OUTPUT);
  pinMode(echoPin2, INPUT);

  // Attach the servo to its pin
  myServo.attach(servoPin); 

  // Close Dustbin by default
  servoPos = closedPos;
  myServo.write(servoPos);

  // Send sensor data every 1 seconds 
  timer.setInterval(1000L, myTimer); 

}

void loop()
{
  Blynk.run();
  timer.run();  

  // measure distance for first ultrasonic sensor and get perecentage 
  ultrasonicSensor_1();
  
  // Check percentage range and control LEDs accordingly for the first ultrasonic sensor
  checkPercentage(); 

  // Measure the distance for the second ultrasonic sensor
  ultrasonicSensor_2();

  // Open and Close Logic
  openAndclose_Trash();

  Serial.println(); // Move to the next line in the Serial Monitor
  delay(1000); // Delay for a moment to avoid too frequent readings
}

void ultrasonicSensor_1(){
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  int duration = pulseIn(echoPin, HIGH);
  distance1 = (duration * 0.0343) / 2;

  // Calculate percentage for the first ultrasonic sensor
  percentage = map(distance1, 0, 21, 100, 0);
  percentage = constrain(percentage, 0, 100);

  // Display the percentage on the Serial Monitor
  Serial.print("Percentage: ");
  Serial.print(percentage);
  Serial.print("%");
}

void checkPercentage(){
   if (percentage >= 75 && percentage <= 100) {
    Blynk.logEvent("full");
    Serial.print(" Full");
    digitalWrite(redLedPin, HIGH);
    digitalWrite(yelloLedPin, LOW);
    digitalWrite(greenLedPin, LOW);

  } else if (percentage >= 0 && percentage <= 20) {
    Serial.print(" Empty");
    digitalWrite(redLedPin, LOW);
    digitalWrite(yelloLedPin, LOW);
    digitalWrite(greenLedPin, HIGH);

   } else {
    Serial.print(" Normal");
    digitalWrite(redLedPin, LOW);
    digitalWrite(yelloLedPin, HIGH);
    digitalWrite(greenLedPin, LOW);
   }
 }

void ultrasonicSensor_2(){
  digitalWrite(triggerPin2, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin2, LOW);
  int duration2 = pulseIn(echoPin2, HIGH);
  distance2 = (duration2 * 0.0343) / 2;
}

void openAndclose_Trash(){
  if (distance2 >= 0 && distance2 <= 20 ){
    openTrash();
    delay(5000);
  } else{
    closeTrash();
  }
}

void openTrash(){
  while (servoPos > openPos){
    myServo.write(servoPos);
    servoPos -=1;
    delay(10);
  } 
  trashOpen = true;
}

void closeTrash(){
  while (servoPos < closedPos){
    myServo.write(servoPos);
    servoPos +=1;
    delay(10);
  } 
  trashOpen = false;
}