#ifndef AD9850_h
#define AD9850_h

#include <Arduino.h>

class DDS {
  public:

    int W_CLK;
    int FU_UD;
    int DATA;
    int RESET;
    
    

    DDS();    
    void setFreq(double Freq);
    
  private:

    void writeByte(byte data);
    void pulseHigh(int pin); 

};

#endif
