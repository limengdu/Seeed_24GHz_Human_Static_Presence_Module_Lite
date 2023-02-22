#include "Arduino.h"
#include <humanstaticLite.h>

//#include <SoftwareSerial.h>
// Choose any two pins that can be used with SoftwareSerial to RX & TX
//#define RX_Pin A2
//#define TX_Pin A3

//SoftwareSerial mySerial = SoftwareSerial(RX_Pin, TX_Pin);

// we'll be using software serial
//HumanStaticLite radar = HumanStaticLite(&mySerial);

// can also try hardware serial with
HumanStaticLite radar = HumanStaticLite(&Serial1);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial1.begin(115200);

  //  mySerial.begin(115200);

  while(!Serial);   //When the serial port is opened, the program starts to execute.

  Serial.println("Ready");

  radar.reset_func();
}

void loop() {
  // put your main code here, to run repeatedly:

}
