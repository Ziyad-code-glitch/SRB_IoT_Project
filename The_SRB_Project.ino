// SRB PROJECT BY ZIYAD WALID

// libraries 
#include <Servo.h>

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

// Global variable for percentage & distance2
int percentage = 0; 
int distance2;


void setup()
{
  Serial.begin(9600);

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
}

void loop()
{  
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
  int distance = (duration * 0.0343) / 2;

  // Calculate percentage for the first ultrasonic sensor
  percentage = map(distance, 0, 21, 100, 0);
  percentage = constrain(percentage, 0, 100);

  // Display the percentage on the Serial Monitor
  Serial.print("Percentage: ");
  Serial.print(percentage);
  Serial.print("%");
}

void checkPercentage(){
   if (percentage >= 75 && percentage <= 100) {
     Serial.print(" Full");
     digitalWrite(redLedPin, HIGH);
     digitalWrite(yelloLedPin, LOW);
     digitalWrite(greenLedPin, LOW);
  } else if (percentage >= 0 && percentage <= 25) {
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
}

void closeTrash(){
    while (servoPos < closedPos){
      myServo.write(servoPos);
      servoPos +=1;
      delay(10);
  } 
}