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

const unsigned char close_buff[10] = {0x53, 0x59, 0x08, 0x00, 0x00, 0x01, 0x00, 0xB5, 0x54, 0x43};  //switch off Open Underlying Message
const unsigned char open_buff[10] = {0x53, 0x59, 0x08, 0x00, 0x00, 0x01, 0x01, 0xB6, 0x54, 0x43};   //switch on Open Underlying Message

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial1.begin(115200);

  //  mySerial.begin(115200);

  while(!Serial);   //When the serial port is opened, the program starts to execute.

  Serial.println("Ready");
}

void loop() {
  // put your main code here, to run repeatedly:
  radar.checkSetMode_func(open_buff, 10, false);
  delay(50);   //Do not set the delay time too long, as this may affect the reception of the data frames returned by the radar.
}
