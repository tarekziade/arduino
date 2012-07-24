#include <SoftwareSerial.h>
#include <LiquidCrystal.h> 

LiquidCrystal lcd(7, 8, 9, 5, 6, 12);
SoftwareSerial mySerial(10, 11);

int col, row;
char value ;

void setup() { 
   mySerial.begin(9600);
    Serial.begin(9600);
lcd.begin(16, 2);
lcd.clear();
lcd.print("Ready or not...");
col = 0;
row = 0;
} 

void loop() {  

   while (!mySerial.available()); 
    
   
   value = mySerial.read();
   Serial.print(value);
   if (value == '*') {
       lcd.clear();
       col = 0;
       row = 0;
   }
   else {
 
    lcd.setCursor(col, row);
    lcd.print(value);
    
    if (col==15) {
      col = 0;
      if (row == 0) {
       row = 1;
      }
      else {
        row = 0;
      }
    }      
    else {
     col += 1;
    }
  } 
   
} 


