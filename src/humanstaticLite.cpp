#include "Arduino.h"
#include "humanstaticLite.h"

HumanStaticLite::HumanStaticLite(Stream *s)
    : stream(s){
  radarStatus = 0;
}

// Receive data and process
void HumanStaticLite::recvRadarBytes(){
  while (stream->available()) {
    if(stream->read() == MESSAGE_HEAD1){           //Receive header frame 1
      if(stream->read() == MESSAGE_HEAD2){         //Receive header frame 2
        dataLen = stream->readBytesUntil(MESSAGE_END2, Msg, 20);
        if (dataLen > 0 && dataLen < 20){
          Msg[dataLen] = MESSAGE_END2;
          newData = true;
        }
      }
    }
  }
}

//Radar transmits data frames for display via serial port
void HumanStaticLite::showData(){
  if(newData == true){
    Serial.print(MESSAGE_HEAD1, HEX);
    Serial.print(' ');
    Serial.print(MESSAGE_HEAD2, HEX);
    Serial.print(' ');
    char charVal[4];
    for (byte n = 0; n < dataLen+1; n++) {
      sprintf(charVal, "%02X", Msg[n]);
      Serial.print(F(charVal));
      Serial.print(' ');
    }
    Serial.println();
    newData = false;
    Msg[dataLen] = {0};
    // delay(200);
  }
}

void HumanStaticLite::HumanStatic_func(bool bodysign /*=false*/){
  if(newData == true){
    switch (Msg[0])
    {
      case HUMANSTATUS:
        switch (Msg[1])
        {
          case HUMANEXIST:
            switch (Msg[4])
            {
              case SOMEBODY:
                showData();
                Serial.println(F("Someone here"));
                Serial.println(F("---------------------------------"));
                break;
              case NOBODY:
                showData();
                Serial.println(F("Nobody here."));
                Serial.println(F("---------------------------------"));
                break;
            }
            break;
          case HUMANMOVE:
            switch (Msg[4])
            {
              case NONE:
                showData();
                Serial.println(F("No human activity messages."));
                Serial.println(F("---------------------------------"));
                break;
              case SOMEBODY_STOP:
                showData();
                Serial.println(F("Someone stop"));
                Serial.println(F("---------------------------------"));
                break;
              case SOMEBODY_MOVE:
                showData();
                Serial.println(F("Someone moving"));
                Serial.println(F("---------------------------------"));
                break;
            }
            break;
          case HUMANSIGN:
            if(bodysign == true){
              showData();
              Serial.print(F("The motor signs parameters are: "));
              Serial.println(Msg[4], DEC);
              Serial.println(F("---------------------------------"));
            }
            break;
          case HUMANDIRECT:
            switch (Msg[4])
            {
              case NONE:
                showData();
                Serial.println(F("No human activity messages."));
                Serial.println(F("---------------------------------"));
                break;
              case CA_CLOSE:
                showData();
                Serial.println(F("Someone is closing"));
                Serial.println(F("---------------------------------"));
                break;
              case CA_AWAY:
                showData();
                Serial.println(F("Someone is staying away"));
                Serial.println(F("---------------------------------"));
                break;
            }
            break;
        }
        break;
      case DETAILSTATUS:
        switch(Msg[1]){
          case DETAILINFO:
            showData();
            Serial.print(F("Spatial static values: "));
            Serial.println(Msg[4], DEC);
            Serial.print(F("Distance to stationary object: "));
            Serial.println(Msg[5], DEC);
            Serial.print(F("Spatial dynamic values: "));
            Serial.println(Msg[6], DEC);
            Serial.print(F("Distance from the movement object: "));
            Serial.println(Msg[7], DEC);
            Serial.print(F("Speed of moving object: "));
            Serial.println(Msg[8], DEC);
            Serial.println(F("---------------------------------"));
            break;
          case DETAILDIRECT:
            switch(Msg[4]){
              case NONE:
                showData();
                Serial.println(F("No human activity messages."));
                Serial.println(F("---------------------------------"));
                break;
              case CA_CLOSE:
                showData();
                Serial.println(F("Someone is closing"));
                Serial.println(F("---------------------------------"));
                break;
              case CA_AWAY:
                showData();
                Serial.println(F("Someone is staying away"));
                Serial.println(F("---------------------------------"));
                break;
            }
            break;
          case DETAILSIGN:
            if(bodysign == true){
              showData();
              Serial.print(F("The motor signs parameters are: "));
              Serial.println(Msg[4], DEC);
              Serial.println(F("---------------------------------"));
            }
            break;
        }
        break;
    }
  }
}

void HumanStaticLite::setMode_func(const unsigned char* buff, int len, bool cyclic /*=false*/){
  if(cyclic || count < checkdata_len){
    stream->write(buff, len);
    stream->flush();
    Serial.println(F("Setup message sent! Please check..."));
    recvRadarBytes();
    showData();
    count++;
  }
}



