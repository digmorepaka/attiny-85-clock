//include libraries, TinyWireM and TinyRTClib is used thanks to their small size
//recommended to flash this directly via ISP, digispark bootloader is slow, takes around 15 seconds to boot due to programming wait time
//expect slight drift of ds1307, it is not perfect
//ds1307 needs to be modded to not destroy non-rechargable batteries

#include <TM1637.h>
#include <TinyWireM.h>
#include "TinyRTClib.h"
//init RTC
RTC_DS1307 RTC;
//variables
int hh,mm;
//display pins
#define CLK 4
#define DIO 3

//init display
TM1637 Display(CLK, DIO);

void setup() {
   //init i2c and rtc clock
   TinyWireM.begin();
   RTC.begin();
   //init display set low brightness
   Display.init();
   Display.set(1); 

}


void loop() {
  //current time
  DateTime now = RTC.now();
  //current minutes and hour
  hh = now.hour(), DEC;
  mm = now.minute(), DEC;
  //enable double dot
  Display.point(POINT_ON);
  //divide parts of integer for each digit.. eg: 04:20, digit 0 = 0, digit 1 = 4, digit 2 = 2, digit 3 = 0
  Display.display(0,hh/10);
  Display.display(1,hh%10);
  Display.display(2,mm/10); 
  Display.display(3,mm%10);
  //wait 10 seconds
  delay(10000);
}
