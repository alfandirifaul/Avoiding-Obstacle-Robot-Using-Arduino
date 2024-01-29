#include <Servo.h> // include the Servo library
#include <NewPing.h> // include the NewPing library for ultrasonic sensor

//pin for buzzer
const int buzzer = 7; // define the pin number for the buzzer

// pin for motor
const int leftForward = 10; // define the pin number for the left motor forward
const int leftBackward = 11; // define the pin number for the left motor backward
const int rightForward = 12; // define the pin number for the right motor forward
const int rightBackward = 13; // define the pin number for the right motor backward

// pin for distance using ultrasonic
const int trigPin = 5; // define the pin number for the ultrasonic sensor trigger
const int echoPin = 6; // define the pin number for the ultrasonic sensor echo
const int MAX_DISTANCE = 200; // define the maximum distance to measure in centimeters
int distance = 50; // declare a variable to store the distance value

//servo pin
const int servoPin = 8; // define the pin number for the servo motor

NewPing sonar(trigPin, echoPin, MAX_DISTANCE); // create a NewPing object with the specified pins and distance
Servo myservo; // create a Servo object

//////////////////////////////////////////////
int readPing(){
  delay(20); // wait for 20 milliseconds
  int cm = 0; // declare a variable to store the distance in centimeters
  cm = sonar.ping_cm(); // get the distance from the ultrasonic sensor in centimeters
  if(cm == 0){ // if the distance is zero
    cm = 300; // set it to a large value
  }
  return cm; // return the distance value
}

int lookRight(){
  myservo.write(20); // move the servo to 20 degrees
  delay(400); // wait for 400 milliseconds
  int distance = readPing(); // get the distance from the ultrasonic sensor
  delay(50); // wait for 50 milliseconds
  myservo.write(90); // move the servo back to 90 degrees
  return distance; // return the distance value
}

int lookLeft(){
  myservo.write(170); // move the servo to 170 degrees
  delay(400); // wait for 400 milliseconds
  int distance = readPing(); // get the distance from the ultrasonic sensor
  delay(50); // wait for 50 milliseconds
  myservo.write(90); // move the servo back to 90 degrees
  return distance; // return the distance value
}

void moveForward(){
  digitalWrite(leftForward,HIGH); // turn on the left motor forward
  digitalWrite(rightForward,HIGH); // turn on the right motor forward
  digitalWrite(leftBackward,LOW); // turn off the left motor backward
  digitalWrite(rightBackward,LOW); // turn off the right motor backward
}

void moveBackward(){
  digitalWrite(leftForward,LOW); // turn off the left motor forward
  digitalWrite(rightForward,LOW); // turn off the right motor forward
  digitalWrite(leftBackward,HIGH); // turn on the left motor backward
  digitalWrite(rightBackward,HIGH); // turn on the right motor backward
}

void turnLeft(){
  digitalWrite(leftForward,LOW); // turn off the left motor forward
  digitalWrite(leftBackward,HIGH); // turn on the left motor backward
  digitalWrite(rightForward,HIGH); // turn on the right motor forward
  digitalWrite(rightBackward,LOW); // turn off the right motor backward
}

void turnRight(){
  digitalWrite(leftForward,HIGH); // turn on the left motor forward
  digitalWrite(leftBackward,LOW); // turn off the left motor backward
  digitalWrite(rightForward,LOW); // turn off the right motor forward
  digitalWrite(rightBackward,HIGH); // turn on the right motor backward
}

void moveStop(){
  digitalWrite(leftForward,LOW); // turn off the left motor forward
  digitalWrite(leftBackward,LOW); // turn off the left motor backward
  digitalWrite(rightForward,LOW); // turn off the right motor forward
  digitalWrite(rightBackward,LOW); // turn off the right motor backward
}
//////////////////////////////////////////////

void setup(){
  pinMode(leftForward,OUTPUT); // set the left motor forward pin as output
  pinMode(leftBackward,OUTPUT); // set the left motor backward pin as output
  pinMode(rightForward,OUTPUT); // set the right motor forward pin as output
  pinMode(rightBackward,OUTPUT); // set the right motor backward pin as output
  pinMode(buzzer,OUTPUT); // set the buzzer pin as output
  moveStop(); // stop the motors

  myservo.attach(servoPin); // attach the servo to the servo pin

  myservo.write(0); // move the servo to 0 degrees
  delay(1000); // wait for 1000 milliseconds
  myservo.write(180); // move the servo to 180 degrees
  delay(1000); // wait for 1000 milliseconds
  myservo.write(90); // move the servo to 90 degrees
  delay(1000); // wait for 1000 milliseconds

  distance = readPing(); // get the distance from the ultrasonic sensor
  delay(50); // wait for 50 milliseconds
  distance = readPing(); // get the distance from the ultrasonic sensor
  delay(50); // wait for 50 milliseconds
  distance = readPing(); // get the distance from the ultrasonic sensor
  delay(50); // wait for 50 milliseconds
}

void loop(){
  distance = readPing(); // get the distance from the ultrasonic sensor
  delay(10); // wait for 10 milliseconds

  int distanceRight = 0; // declare a variable to store the distance to the right
  int distanceLeft = 0; // declare a variable to store the distance to the left
  delay(10); // wait for 10 milliseconds

  if(distance <= 25){ // if the distance is less than or equal to 25 centimeters
    digitalWrite(buzzer,HIGH); // turn on the buzzer
    moveStop(); // stop the motors
    delay(300); // wait for 300 milliseconds

    moveBackward(); // move backward
    delay(400); // wait for 400 milliseconds
    digitalWrite(buzzer,LOW); // turn off the buzzer

    moveStop(); // stop the motors
    delay(100); // wait for 100 milliseconds

    distanceRight = lookRight(); // get the distance to the right
    delay(500); // wait for 500 milliseconds

    distanceLeft = lookLeft(); // get the distance to the left
    delay(500); // wait for 500 milliseconds

    if(distanceRight < distanceLeft){ // if the distance to the right is less than the distance to the left
      turnLeft(); // turn left
      delay(500); // wait for 500 milliseconds
      moveStop(); // stop the motors
    }
    else{ // otherwise
      turnRight(); // turn right
      delay(500); // wait for 500 milliseconds
      moveStop(); // stop the motors
    }
  } 
  else{ // otherwise
    moveForward(); // move forward
  }
  delay(50); // wait for 50 milliseconds
}
