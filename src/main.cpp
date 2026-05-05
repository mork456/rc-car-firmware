#include<Arduino.h>
#include<Servo.h>
#include<SoftwareSerial.h>

void moveForward();
void moveBackward();
void turnLeft();
void turnRight();
void stopRobot();
void executeCommand(char c);

// Arduino pin 3 (ReceivePin) connects to HM-10 TXD
// Arduino pin 4 (TransmitPin) connects to HM-10 RXD (via voltage divider)
SoftwareSerial BLE(3, 4); 

Servo leftServo;
Servo rightServo;

void setup () {
    //Start serial for HM-10
    BLE.begin(9600);
    
    leftServo.attach(7);
    rightServo.attach(9);

    // Make sure motors are stopped at startup
    stopRobot();
}

unsigned long lastCommandTime = 0;

void loop() {
    // This loop runs while the HM-10 BLE device is connected (via virtual serial port)
    if (BLE.available()) {
        char cmd = BLE.read();
        executeCommand(cmd);
        lastCommandTime = millis(); // Record the time of the last command
    }
    // After 200ms of no received command, stop
    if (millis() - lastCommandTime > 200) {
        stopRobot();
    }
}

// Map received keyboard input to appropriate motion functions
void executeCommand(char c) {
    switch (c) {
        case 'w' : moveForward(); break;
        case 's' : moveBackward(); break;
        case 'a' : turnLeft(); break;
        case 'd' : turnRight(); break;
        case ' ' : stopRobot(); break; 
    }
} 

// Motion functions
void moveForward()  { leftServo.write(180); rightServo.write(0);   }
void moveBackward() { leftServo.write(0);   rightServo.write(180); }
void turnLeft()     { leftServo.write(0);   rightServo.write(0);   }
void turnRight()    { leftServo.write(180); rightServo.write(180); }
void stopRobot()    { leftServo.write(90);  rightServo.write(90);  }
