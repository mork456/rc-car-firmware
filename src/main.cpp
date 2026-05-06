#include<Arduino.h>
#include<Servo.h>
#include<SoftwareSerial.h>

void stopRobot();

// Arduino pin 3 (ReceivePin) connects to HM-10 TXD
// Arduino pin 4 (TransmitPin) connects to HM-10 RXD (via voltage divider)
SoftwareSerial BLE(3, 4); 

Servo leftServo;
Servo rightServo;

void setup () {
    // Start serial for HM-10 with baud rate 9600
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
        String data = BLE.readStringUntil('\n');
        int commaIndex = data.indexOf(','); // Record commaIndex, if not found returns -1
        if (commaIndex != -1) { // Runs only if the data is correctly formatted
            int leftSpeed = data.substring(0, commaIndex).toInt(); // Read the first part of string and convert to integer to save in leftSpeed
            int rightSpeed = data.substring(commaIndex + 1).toInt(); // Read the last part of string starting from commaIndex + 1 and convert to integer to save in rightSpeed
            leftServo.write(leftSpeed);
            rightServo.write(rightSpeed);
            lastCommandTime = millis();
        }

   }
    // After 200ms of no received command, stop
    if (millis() - lastCommandTime > 200) {
        stopRobot();
    }
}

void stopRobot()    { leftServo.write(90);  rightServo.write(90);  }
