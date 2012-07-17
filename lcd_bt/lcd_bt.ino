#include <LiquidCrystal.h> 
#include <SoftwareSerial.h>
#include <AFMotor.h>

SoftwareSerial mySerial(2, 3);

LiquidCrystal lcd(7, 8, 9, 10, 11, 12);


AF_DCMotor motor(4, MOTOR12_64KHZ); // create motor #2, 64KHz pwm
AF_DCMotor motor2(2, MOTOR12_64KHZ); // create motor #2, 64KHz pwm

void setup() { 
Serial.begin(9600);           // set up Serial library at 9600 bps
 // Serial.println("Motor test!");
  mySerial.begin(9600);
        lcd.begin(16, 2); // Set the display to 16 columns and 2 rows 
 motor.setSpeed(200);     // set the speed to 200/255
  motor2.setSpeed(255);     // set the speed to 200/255
} 

char value ;

void loop() { 

        // Run the seven demo routines 
      while (!mySerial.available()); 
      value =  mySerial.read();
      if (value == 'C') {
       lcd.clear();}
      else
      { 
      lcd.print(value);
      
      if (value == 'F') {
      motor.run(FORWARD);
      } 
      if (value == 'B') {
      motor.run(BACKWARD);
      } 
      
      if (value == 'S') {
      motor.run(RELEASE);
      } 
      }
} 


