#include "Arduino.h"
#include "humanstaticLite.h"

HumanStaticLite::HumanStaticLite(Stream *s)
    : stream(s){
  this->newData = false;
}

// Receive data and process
void HumanStaticLite::recvRadarBytes(){
  while (stream->available()) {
    if(stream->read() == MESSAGE_HEAD1){           //Receive header frame 1
      if(stream->read() == MESSAGE_HEAD2){         //Receive header frame 2
        dataLen = stream->readBytesUntil(MESSAGE_END2, Msg, 20);
        if (dataLen > 0 && dataLen < 20){
          Msg[dataLen] = MESSAGE_END2;
          this->newData = true;
        }
      }
    }
  }
}

//Radar transmits data frames for display via serial port
void HumanStaticLite::showData(){
  if(this->newData){
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
    this->newData = false;
    Msg[dataLen] = {0};
    // delay(200);
  }
}

//Parsing data frames
void HumanStaticLite::HumanStatic_func(bool bodysign /*=false*/){
  recvRadarBytes();
  radarStatus = 0x00;
  bodysign_val = 0x00;
  static_val = 0x00;
  dynamic_val = 0x00;
  dis_static = 0x00;
  dis_move = 0x00;
  speed = 0x00;
  if(this->newData){
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
                radarStatus = SOMEONE;
                break;
              case NOBODY:
                showData();
                radarStatus = NOONE;
                break;
            }
            break;
          case HUMANMOVE:
            switch (Msg[4])
            {
              case NONE:
                showData();
                radarStatus = NOTHING;
                break;
              case SOMEBODY_STOP:
                showData();
                radarStatus = SOMEONE_STOP;
                break;
              case SOMEBODY_MOVE:
                showData();
                radarStatus = SOMEONE_MOVE;
                break;
            }
            break;
          case HUMANSIGN:
            if(bodysign){
              showData();
              radarStatus = HUMANSIGN;
              bodysign_val = Msg[4];
            }
            break;
          case HUMANDIRECT:
            switch (Msg[4])
            {
              case NONE:
                showData();
                radarStatus = NOTHING;
                break;
              case CA_CLOSE:
                showData();
                radarStatus = SOMEONE_CLOSE;
                break;
              case CA_AWAY:
                showData();
                radarStatus = SOMEONE_AWAY;
                break;
            }
            break;
        }
        break;
      case DETAILSTATUS:
        switch(Msg[1]){
          case DETAILINFO:
            showData();
            radarStatus = DETAILMESSAGE;
            static_val = Msg[4];
            dynamic_val = Msg[5];
            dis_static = Msg[6];
            dis_move = Msg[7];
            speed = Msg[8];
            break;
          case DETAILDIRECT:
            switch(Msg[4]){
              case NONE:
                showData();
                radarStatus = NOTHING;
                break;
              case CA_CLOSE:
                showData();
                radarStatus = SOMEONE_CLOSE;
                break;
              case CA_AWAY:
                showData();
                radarStatus = SOMEONE_AWAY;
                break;
            }
            break;
          case DETAILSIGN:
            if(bodysign){
              showData();
              radarStatus = HUMANSIGN;
              bodysign_val = Msg[4];
            }
            break;
        }
        break;
    }
  }
  this->newData = false;
}

//Send data frame
void HumanStaticLite::checkSetMode_func(const unsigned char* buff, int len, bool cyclic /*=false*/){
  if(cyclic || count < checkdata_len){
    if(cyclic || count < 1){
      stream->write(buff, len);
      stream->flush();
    }
    do{
      recvRadarBytes();
      delay(20);
    }while(!(this->newData));
    if(cyclic || count < 1){
      Serial.print(F("  Sent  ---> "));
      data_printf(buff, len);
    }
    if(count%2 == 1){
      Serial.print(F("Receive <--- "));
      showData();
    }
    this->newData = false;
  }
  count++;
}

//Reset radar
void HumanStaticLite::reset_func(){
  stream->write(reset_frame, reset_frame_len);
  stream->flush();
  Serial.println(F("Radar reset!"));
}

//print redirect
void HumanStaticLite::data_printf(const unsigned char* buff, int len){
  char charVal[4];
  for(int i=0; i<len; i++){
    sprintf(charVal, "%02X", buff[i]);
    Serial.print(F(charVal));
    Serial.print(' ');
  }
  Serial.println();
}






