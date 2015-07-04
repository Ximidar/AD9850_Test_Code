#include "AD9850.h"
#include <Arduino.h>

//This code uses a potentiometer to control the output frequency.
//you can put any number you want for freq in Hz
// AD9850 supports 1 - 40000000 Hz
DDS frq;
double freq = 1;
#define potPin A3

void setup(){

  Serial.begin(9600);
  DDS();
  
  
  
}

void loop(){

  
  freq = analogRead(potPin);
  //Serial.println(freq);
  freq = freq / 875;
  freq = freq * 10000;
  
  frq.setFreq(freq);
    
    
  
    
  
  
}
 
 

