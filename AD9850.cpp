//This code was created on 03JUL2015
//The purpose of this code is to set up the AD9850 DDS Signal Generator,
//And to set the output frequency of the AD9850 chip 
//This code was created with this reference - http://www.electrodragon.com/w/AD9850_Module_DDS_Signal_Generator_V2

#include "AD9850.h"

#define DEBUG

DDS::DDS(){

  // Set pins for DDS output. These pins can be customized to whatever is needed, 
  // but all pins need to be DI/O pins
  
  W_CLK = 30;
  FU_UD = 31;
  DATA = 32;
  RESET = 33;

  //Sine Wave output is on ZOUT1 and ZOUT2
  //Square Wave output is on QOUT1 and QOUT2
  // OUT1 and OUT2 are inverse waves of eachother

  //OUT1
  //            / /                     / /
  //          /     /                 /      /
  //        /         /              /          /
  //      /             /           /              /
  //    /                /        /                  /
  //  /                   /     /                      /
  ///                       / /                          /
  ////////////////////////////////////////////////////////////////////////

  //OUT2
  ///                         / /
  //  /                     /    /
  //   /                 /        /
  //    /             /            /
  //     /         /                /
  //       /     /                    /
  //         / /                        / /
  ////////////////////////////////////////////////////////////////////////

  //Set pins to output mode
  pinMode(W_CLK, OUTPUT);
  pinMode(FU_UD, OUTPUT);
  pinMode(DATA, OUTPUT);
  pinMode(RESET, OUTPUT);

  //set pins to serial mode
  pulseHigh(RESET);
  pulseHigh(W_CLK);
  pulseHigh(FU_UD);

  #ifdef DEBUG
    Serial.println("DDS Initialized");
  #endif
  
}

void DDS::setFreq(double frequency){

  //enter frequency as Hz
  if(frequency > 40000000){
      Serial.println("Frequency is set Higher than board can output");
      Serial.println("Setting to Maximum Freq ");
      frequency = 40000000;
  }
  
  #ifdef DEBUG
    Serial.print("Freq: ");
    Serial.print(frequency);
    Serial.println(" Hz");    
  #endif
  
  int32_t freq = frequency * 4294967295 / 125000000;  // note 125 MHz clock on 9850
  for (int b = 0; b < 4; b++, freq>>=8) {
    writeByte(freq & 0xFF);
  }
  writeByte(0x000);   // Final control byte
  pulseHigh(FU_UD);  // Done!  Should see output
  
}

void DDS::writeByte(byte data){
  for (int i=0; i<8; i++, data>>=1) {
    digitalWrite(DATA, data & 0x01);
    pulseHigh(W_CLK);   //after each bit sent, CLK is pulsed high
  }  
}


void DDS::pulseHigh(int pin){
  
  digitalWrite(pin, HIGH); 
  digitalWrite(pin, LOW); 
  
}

