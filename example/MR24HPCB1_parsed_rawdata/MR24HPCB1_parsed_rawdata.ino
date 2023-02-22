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
}

void loop() {
  // put your main code here, to run repeatedly:
  radar.HumanStatic_func(false);    //Turn on printing of human movement sign parameters
  if(radar.radarStatus != 0x00){
    switch(radar.radarStatus){
      Serial.println(radar.radarStatus);
      case SOMEONE:
        Serial.println("Someone is here.");
        Serial.println("---------------------------------");
        break;
      case NOONE:
        Serial.println("Nobody here.");
        Serial.println("---------------------------------");
        break;
      case NOTHING:
        Serial.println("No human activity messages.");
        Serial.println("---------------------------------");
        break;
      case SOMEONE_STOP:
        Serial.println("Someone stop");
        Serial.println("---------------------------------");
        break;
      case SOMEONE_MOVE:
        Serial.println("Someone moving");
        Serial.println("---------------------------------");
        break;
      case HUMANPARA:
        Serial.print("The parameters of human body signs are: ");
        Serial.println(radar.bodysign_val, DEC);
        Serial.println("---------------------------------");
        break;
      case SOMEONE_CLOSE:
        Serial.println("Someone is closing");
        Serial.println("---------------------------------");
        break;
      case SOMEONE_AWAY:
        Serial.println("Someone is staying away");
        Serial.println("---------------------------------");
        break;
      case DETAILMESSAGE:
        Serial.print("Spatial static values: ");
        Serial.println(radar.static_val);

        Serial.print("Distance to stationary object: ");
        Serial.print(radar.dis_static);
        Serial.println(" m");

        Serial.print("Spatial dynamic values: ");
        Serial.println(radar.dynamic_val);
        
        Serial.print("Distance from the movement object: ");
        Serial.print(radar.dis_move);
        Serial.println(" m");

        Serial.print("Speed of moving object: ");
        Serial.print(radar.speed);
        Serial.println(" m/s");
        Serial.println("---------------------------------");
        break;
    }
  }
  delay(200);
}
