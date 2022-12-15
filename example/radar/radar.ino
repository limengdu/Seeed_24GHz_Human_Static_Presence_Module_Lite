#include "Arduino.h"
#include <humanstaticLite.h>

//#include <SoftwareSerial.h>
//// Choose any two pins that can be used with SoftwareSerial to RX & TX
//#define RX_Pin A2
//#define TX_Pin A3

//SoftwareSerial mySerial = SoftwareSerial(RX_Pin, TX_Pin);

//// we'll be using software serial
//HumanStaticLite radar = HumanStaticLite(&mySerial);

// can also try hardware serial with
HumanStaticLite radar = HumanStaticLite(&Serial1);

const unsigned char buff_1[10] = {0x53, 0x59, 0x08, 0x00, 0x00, 0x01, 0x00, 0xB5, 0x54, 0x43};   //开启0x80
const unsigned char buff_2[10] = {0x53, 0x59, 0x08, 0x00, 0x00, 0x01, 0x01, 0xB6, 0x54, 0x43};   //开启0x08  
const unsigned char buff_3[10] = {0x53, 0x59, 0x02, 0xA1, 0x00, 0x01, 0x0F, 0x5F, 0x54, 0x43};   //产品型号查询
const unsigned char buff_4[10] = {0x53, 0x59, 0x01, 0x02, 0x00, 0x01, 0x0F, 0xBF, 0x54, 0x43};   //雷达复位


//unsign char send_buf[19];

void setup()
{
  Serial.begin(115200);
  Serial1.begin(115200);
  
//  mySerial.begin(115200);

  while(!Serial);

//  radar.reset_func();
  
  Serial.println("Readly");
}

void loop()
{
//  radar.recvRadarBytes();           //Receive radar data and start processing
//  radar.showData();                 //Serial port prints a set of received data frames

//   radar.HumanStatic_func(true);
//   if(radar.radarStatus != 0x00){
//    switch(radar.radarStatus){
//      Serial.println("begin");
//      case SOMEONE:
//        Serial.println("Someone is here.");
//        Serial.println("---------------------------------");
//        break;
//      case NOONE:
//        Serial.println("Nobody here.");
//        Serial.println("---------------------------------");
//        break;
//      case NOTHING:
//        Serial.println("No human activity messages.");
//        Serial.println("---------------------------------");
//        break;
//      case SOMEONE_STOP:
//        Serial.println("Someone stop");
//        Serial.println("---------------------------------");
//        break;
//      case SOMEONE_MOVE:
//        Serial.println("Someone moving");
//        Serial.println("---------------------------------");
//        break;
//      case HUMANSIGN:
//        Serial.print("The parameters of human body signs are: ");
//        Serial.println(radar.bodysign_val, DEC);
//        Serial.println("---------------------------------");
//        break;
//      case SOMEONE_CLOSE:
//        Serial.println("Someone is closing");
//        Serial.println("---------------------------------");
//        break;
//      case SOMEONE_AWAY:
//        Serial.println("Someone is staying away");
//        Serial.println("---------------------------------");
//        break;
//      case DETAILMESSAGE:
//        Serial.print("Spatial static values: ");
//        Serial.println(radar.static_val, DEC);
//        Serial.print("Distance to stationary object: ");
//        Serial.println(radar.dynamic_val, DEC);
//        Serial.print("Spatial dynamic values: ");
//        Serial.println(radar.dis_static, DEC);
//        Serial.print("Distance from the movement object: ");
//        Serial.println(radar.dis_move, DEC);
//        Serial.print("Speed of moving object: ");
//        Serial.println(radar.speed, DEC);
//        Serial.println("---------------------------------");
//        break;
//      default:
//        Serial.println("No radar message received, please wait...");
//        Serial.println("---------------------------------");
//        break;
//    }
//   }

  radar.checkSetMode_func(buff_2, 10, false);

//  radar.recvRadarBytes();
//  radar.showData();
  

  delay(50);
}
