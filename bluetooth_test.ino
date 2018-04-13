#include <SoftwareSerial.h>
#include <Servo.h>
//Curm 2018
char val; // variable to receive data from the serial port
int ledpin = 13; // LED connected to pin 48 (on-board LED)
Servo myservo;  // create servo object to control a servo

SoftwareSerial mySerial(10, 11); // RX, TX
void setup() {
  pinMode(ledpin, OUTPUT);  // pin 48 (on-board LED) as OUTPUT
  Serial.begin(9600);       // start serial communication at 9600bps
  mySerial.begin(9600);
    myservo.attach(9);  // attaches the servo on pin 9 to the servo object

  Serial.println("Ready to Receive");
}
void loop() {
    if (mySerial.available()) {
      int inputStr = mySerial.read();
      Serial.write(inputStr);
      myservo.write((inputStr%180));              // tell servo to go to position in variable 'pos'

  }
  if (Serial.available()) {
    digitalWrite(ledpin,HIGH);
    delay(300);
    digitalWrite(ledpin,LOW);
    mySerial.write(Serial.read());
  }
}
