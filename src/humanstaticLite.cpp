#include "Arduino.h"
#include "humanstaticLite.h"

HumanStaticLite::HumanStaticLite(Stream *s)
    : stream(s){
  radarStatus = 0;
}
   
// Receive data and process
void HumanStaticLite::recvRadarBytes(){
  while (stream->available()) {
    if(stream->read() == MESSAGE_HEAD1){           //收到头帧1
      if(stream->read() == MESSAGE_HEAD2){         //收到头帧2
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
void HumanStaticLite::ShowData(){
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
    delay(200);
  }
}

// void HumanStatic_func(){
//   switch (Msg[0])
//   {
//     case HUMANSTATUS:
//       switch (Msg[1])
//       {
//         case HUMANEXIST:
//           switch (Msg[3])
//           {
//             case SOMEBODY:
//               Serial1.println("someone here");
//               Serial1.println("------------------------------");
//               break;
//             case NOBODY:
//               Serial1.println("nobody here");
//               Serial1.println("------------------------------");
//               break;
//           }
//           break;
//         case HUMANMOVE:
//           break;
//         case HUMANSIGN:
//           break;
//         case HUMANDIRECT:
//           break;
//       }
//       break;
//   }
// }

//Respiratory sleep data frame decoding
// int HumanStaticLite::Sleep_inf(byte inf[]){
//   switch(inf[3]){
//     case SLEEP_INF:
//       switch(inf[4]){
//         case BREATH:
//           switch(inf[5]){
//             case CHECK_SIGN:
//               switch(inf[6]){
//                 case BREATH_HOLD:
//                   ShowData(inf);
//                   Serial.println("Abnormal breath-holding detected.");
//                   Serial.println("----------------------------");
//                   return 1;
//                   break;
//                 case BREATH_NULL:
//                   ShowData(inf);
//                   Serial.println("No detection signal at the moment.");
//                   Serial.println("----------------------------");
//                   return 2;
//                   break;
//                 case BREATH_NORMAL:
//                   ShowData(inf);
//                   Serial.println("Normal breathing was detected.");
//                   Serial.println("----------------------------");
//                   return 3;
//                   break;
//                 case BREATH_MOVE:
//                   ShowData(inf);
//                   Serial.println("Abnormal motion is detected.");
//                   Serial.println("----------------------------");
//                   return 4;
//                   break;
//                 case BREATH_RAPID:
//                   ShowData(inf);
//                   Serial.println("Abnormal shortness of breath was detected.");
//                   Serial.println("----------------------------");
//                   return 5;
//                   break;
//               }
//               break;
//           }
//           break;
//         case SCENARIO:
//           switch(inf[5]){
//             case CLOSE_AWAY_BED:
//               switch(inf[6]){
//                 case AWAY_BED:
//                   ShowData(inf);
//                   Serial.println("Detects someone leaving the bed.");
//                   Serial.println("----------------------------");
//                   return 6;
//                   break;
//                 case CLOSE_BED:
//                   ShowData(inf);
//                   Serial.println("Detects someone in bed.");
//                   Serial.println("----------------------------");
//                   return 7;
//                   break;
//               }
//               break;
//             case SLEEP_STATE:
//               switch(inf[6]){
//                 case AWAKE:
//                   ShowData(inf);
//                   Serial.println("Current user status detected: Awake.");
//                   Serial.println("----------------------------");
//                   return 8;
//                   break;
//                 case LIGHT_SLEEP:
//                   ShowData(inf);
//                   Serial.println("Current user status detected: Light sleep.");
//                   Serial.println("----------------------------");
//                   return 9;
//                   break;
//                 case DEEP_SLEEP:
//                   ShowData(inf);
//                   Serial.println("Current user status detected: Deep sleep.");
//                   Serial.println("----------------------------");
//                   return 10;
//                   break;
//                 case SLEEP_NULL:
//                   ShowData(inf);
//                   Serial.println("Current user status detected: NULL.");
//                   Serial.println("----------------------------");
//                   return 11;
//                   break;
//               }
//               break;
//           }
//           break;
//       }
//       break;
//   }
//   return 0;
// }



void HumanStaticLite::OutputAssignment(int data){
  switch(data){
    case 1:
      str = "Breath-holding";
      break;
    case 2:
      str = "No detection";
      break;
    case 3:
      str = "Normal breathing";
      break;
    case 4:
      str = "Abnormal motion";
      break;
    case 5:
      str = "Shortness of breath";
      break;
    case 6:
      str = "leaving the bed";
      break;
    case 7:
      str = "in bed";
      break;
    case 8:
      str = "Awake";
      break;
    case 9:
      str = "Light sleep";
      break;
    case 10:
      str = "Deep sleep";
      break;
    case 11:
      str = "NULL";
      break;
  }

}
