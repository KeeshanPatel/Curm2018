/*
 * ***********SCHEMATICS FOR HOVERBOT AS OF 04/13/2018**************
 * Bluetooth module used: DSD SC-08 bluetooth model(?)
 * Servo motor (myservo) used: **FILL THIS OUT**
 * Drone motor (mainMotor) used: *FILL THIS OUT**
 * All input values are in HEX and used through LightBlue application available on Iphone: tested on Iphone 6.
 * //below schematics are used in void function moveForward()
 * HEX B = Stop forward motion
 * HEX A = Shift wing to move left
 * HEX C = Shift wing to move right
 * //below schematics are used in void function loop()
 * HEX 1 = Shift wing to move left
 * HEX 2 = Move Forward
 * HEX 3 = Shift wing to move right
 */
#include <SoftwareSerial.h>
#include <Servo.h>
char val; // variable to receive data from the serial port
int ledpin = 13; // LED connected to pin 48 (on-board LED)
Servo myservo;  // create servo object to control a servo
Servo mainMotor; // main motor to power locomotion for the hovercraft.
SoftwareSerial mySerial(10, 11); 
void setup() {
  pinMode(ledpin, OUTPUT);  // pin 48 (on-board LED) as OUTPUT
  Serial.begin(9600);       // start serial communication at 9600bps
    mySerial.begin(9600);
    myservo.attach(9);  // attaches the servo on pin 9 to the servo object
    //setup the main motor.
    mainMotor.attach(12);  //Specify here the pin number on which the signal pin of ESC is connected.
    mainMotor.write(30);   //ESC arm command. ESCs won't start unless input speed is less during initialization.
    delay(3000);            //ESC initialization delay.
    //end with setup, let the user know
    Serial.println("Ready to Receive");
}
void loop() {
    if (mySerial.available()) {
      int input = mySerial.read();
      Serial.write(input);
      switch(input){
        case 1:
          Serial.println("Shifting for Left in Loop");
          reset();
          myservo.write((45)); 
          break;
        case 2:
          Serial.println("Shifting for Right in Loop");
          reset();
          moveForward();
          break;
        case 3:
        reset();
        myservo.write(-45);
        break;
        default:
        Serial.println("No known command entered through bluetooth while in loop function.");
        break;
      }
      delay(1); //for stablity
  }
  if (Serial.available()) {
    digitalWrite(ledpin,HIGH);
    delay(300);
    digitalWrite(ledpin,LOW);
    mySerial.write(Serial.read());
  }
}
void moveForward(){
  Serial.println("Starting moveForward for Hovercraft.");
  for(int x =1;x<=130;x++){
    mainMotor.write(x);    //gradually increase the speed of the motor to prvent intertia breaking the body!
    delay(20); //delay 20 ms 
  }
  int input = mySerial.read();
  boolean stopFlag = false;
  while(true){
    switch(input){
      case 11: //stop the forward motion
        stopFlag = true;
        break;
      case 10: //move left
        Serial.println("Shifting for Left in moveForward");
        reset(); 
        myservo.write((45)); 
        stopFlag = false;
        break;
      case 12:
        Serial.println("Shifting for Right in moveForward");
        stopFlag = false;
        reset();
        myservo.write(-45);
        break;
        default:
        Serial.println("No known command entered through bluetooth while in moveForward function.");
        break;
     }
      delay(1); //for stablity
     if(stopFlag)
      break;
  }
    for(int x =mainMotor.read();x>0;x--){
    mainMotor.write(x);    //gradually decrease the speed of the motor to prvent momentum breaking the body!
    delay(2); //delay 20 ms 
  }
  Serial.println("Completed Stop for HoverBoard.");
    return;
}
void reset(){
  myservo.write(0);//move it back to 0
}

