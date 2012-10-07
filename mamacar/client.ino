#include <SPI.h>
#include <Mirf.h>
#include <nRF24L01.h>
#include <MirfHardwareSpiDriver.h>

unsigned long rfdata;
String name = "";
boolean nameEntered = false; 

short int ENGINE_1 = 1;
short int ENGINE_2 = 2;
short int FORWARD = 1;
short int BACKWARD = 2;


void setup(){
  Serial.begin(9600);
  Mirf.spi = &MirfHardwareSpi;
  Mirf.init();
  Mirf.setRADDR((byte *)"clie1");
  Mirf.payload = sizeof(rfdata);
  Mirf.config();
  Serial.println("Beginning ... "); 
}

void loop(){ 
  // getting a value from the Serial
  while (Serial.available()) {
    char readChar = (char)Serial.read();
    // If the next character is a linefeed (enter)
    // the name is complete. Exit the while() loop.
    if (readChar == '\n') {
      nameEntered = true;
      continue;
    }
    // If the character wasn't enter, add it to the name string.
    name += readChar;
  }

  // if we got a value, send it through NRF
 if (name != "") {
  unsigned long time = millis();
 
  // going forward on engine 1 with 124 power
  rfdata = ENGINE_1 << 32 | FORWARD << 16 | name.toInt();
  
  Mirf.setTADDR((byte *)"serv1");
  
  Mirf.send((byte *)&rfdata);
  while(Mirf.isSending()){
  }
  delay(10);
  while(!Mirf.dataReady()){
    //Serial.println("Waiting");
    if ( ( millis() - time ) > 1000 ) {
      Serial.println("Timeout on response from server!");
      return;
    }
  }
  
  Mirf.getData((byte *) &rfdata);
  Serial.println(rfdata);
 }
 name = "";
  delay(1000);
} 
  
  
  
