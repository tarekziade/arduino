#include <SoftwareSerial.h>
#include <AFMotor.h>

SoftwareSerial mySerial(14, 15);

AF_DCMotor motor(4, MOTOR12_64KHZ); // create motor #2, 64KHz pwm
AF_DCMotor motor2(2, MOTOR12_64KHZ); // create motor #2, 64KHz pwm

void setup() { 
  Serial.begin(9600);           // set up Serial library at 9600 bps
  mySerial.begin(9600); 
  motor.setSpeed(255);     
  motor2.setSpeed(255);   
} 

char value ;

void loop() { 
    
      // Run the seven demo routines 
      while (!mySerial.available()); 
 
      value =  mySerial.read();
      Serial.print(value);
      
      
      if (value == 'F') {
       motor.run(FORWARD);
       
      } 
      if (value == 'B') {
      motor.run(BACKWARD);
      
       
      } 
      
      if (value == 'S') {
      motor.run(RELEASE);
       motor2.run(RELEASE);
     
    } 
          
      if (value == 'L') {
       motor2.run(FORWARD);
      
      } 
      if (value == 'R') {
      motor2.run(BACKWARD);
      
      } 
 

} 


