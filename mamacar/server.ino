/**
 * An Mirf example which copies back the data it recives.
 *
 * Pins:
 * Hardware SPI:
 * MISO -> 12
 * MOSI -> 11
 * SCK -> 13
 *
 * Configurable:
 * CE -> 8
 * CSN -> 7
 *
 */

#include <SPI.h>
#include <Mirf.h>
#include <nRF24L01.h>
#include <MirfHardwareSpiDriver.h>



int IN1 = 4;
int IN2 = 5;
int IN3 = 6;
int IN4 = 9;
int ENA = 3;
int ENB = 1;

unsigned long rfdata;


// qty 0-255
void engine1(boolean forward, int speed) {
  if (forward) {
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
  }
  else {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
  }
  analogWrite(ENA, speed);
}

void engine2(boolean forward, int speed) {
  if (forward) {
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
  }
  else {
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
  }
  analogWrite(ENB, speed);
}


void setup(){
  Serial.begin(9600);
  
    // motorshield pins
  pinMode(ENB, OUTPUT);   // sets the pin as output
  pinMode(IN3, OUTPUT);   // sets the pin as output
  pinMode(IN4, OUTPUT);   // sets the pin as output
  pinMode(IN1, OUTPUT);   // sets the pin as output
  pinMode(IN2, OUTPUT);   // sets the pin as output
  pinMode(ENA, OUTPUT);   // sets the pin as output
  
  /*
   * Set the SPI Driver.
   */

  Mirf.spi = &MirfHardwareSpi;
  
  /*
   * Setup pins / SPI.
   */
   
  Mirf.init();
  
  /*
   * Configure reciving address.
   */
   
  Mirf.setRADDR((byte *)"serv1");
  
  /*
   * Set the payload length to sizeof(unsigned long) the
   * return type of millis().
   *
   * NB: payload on client and server must be the same.
   */
   
  Mirf.payload = sizeof(rfdata);
  
  /*
   * Write channel and payload config then power up reciver.
   */
   
  Mirf.config();
  
  Serial.println("Listening..."); 
}

void loop(){
  /*
   * A buffer to store the data.
   */
   
  byte data[Mirf.payload];
  
  /*
   * If a packet has been recived.
   *
   * isSending also restores listening mode when it 
   * transitions from true to false.
   */
   
  if(!Mirf.isSending() && Mirf.dataReady()){
    Serial.println("Got packet");
    
    /*
     * Get load the packet into the buffer.
     */
     
    Mirf.getData(data);
    
    rfdata = data[0];
    short int engine = rfdata >> 32;
    short int direction = rfdata >> 16 & 0xFFFFF;
    short int speed = rfdata & 0xFFFFF;
    boolean forward = direction == 1;
     
  
    if (engine == 1) { 
        engine1(forward, speed);
    }
    else {
        engine2(forward, speed);
   
    }
    
    /*
     * Set the send address.
     */
     
     
    Mirf.setTADDR((byte *)"clie1");
    
    /*
     * Send the data back to the client
     */
     
    Mirf.send(data);
    
    /*
     * Wait untill sending has finished
     *
     * NB: isSending returns the chip to receving after returning true.
     */
      
    Serial.println("Reply sent.");
  }
}
