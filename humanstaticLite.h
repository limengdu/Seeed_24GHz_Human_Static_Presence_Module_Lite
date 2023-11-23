#ifndef _HUMANSTATICLITE_H__
#define _HUMANSTATICLITE_H__

#define MESSAGE_HEAD1 0x53       //Data frame header1
#define MESSAGE_HEAD2 0x59       //Data frame header2

#define MESSAGE_END1  0x54       //End1 of data frame
#define MESSAGE_END2  0x43       //End2 of data frame

#define HUMANSTATUS   0x80       //Human Presence Information
#define HUMANEXIST    0x01       //Presence of the human body
#define HUMANMOVE     0x02       //Human movement information
#define HUMANSIGN     0x03       //Body Signs Parameters
#define HUMANDIRECT   0x0B       //Human movement trends

#define SOMEBODY      0x01       //Somebody move
#define NOBODY        0x00       //No one here

#define NONE          0x00
#define SOMEBODY_STOP 0x01       //Somebody stop
#define SOMEBODY_MOVE 0x02       //Somebody move

#define CA_CLOSE      0x01       //Someone approaches
#define CA_AWAY       0x02       //Some people stay away


#define DETAILSTATUS  0x08       //Underlying parameters of the human state
#define DETAILINFO    0x01       //Detailed data on the state of human movement
#define DETAILDIRECT  0x06       //Human movement trends
#define DETAILSIGN    0x07       //Body Signs Parameters

//Return status, Use in arduino
#define SOMEONE       0x01       //There are people
#define NOONE         0x02       //No one
#define NOTHING       0x03       //No message
#define SOMEONE_STOP  0x04       //Somebody stop
#define SOMEONE_MOVE  0x05       //Somebody move
#define HUMANPARA     0x06       //Body Signs Parameters
#define SOMEONE_CLOSE 0x07       //Someone approaches
#define SOMEONE_AWAY  0x08       //Some people stay away
#define DETAILMESSAGE 0x09       //Underlying parameters of the human state

#define reset_frame_len 10       //Reset data frame length

#define unit          0.5        //Calculate unit steps

//Reset data frame
const unsigned char reset_frame[10] = {0x53, 0x59, 0x01, 0x02, 0x00, 0x01, 0x0F, 0xBF, 0x54, 0x43};

class HumanStaticLite{
    private:
        Stream *stream;               // e.g. SoftwareSerial or Serial1
        boolean newData;
        byte dataLen;
        unsigned char Msg[20] = {0};  //Storage of the data frames returned by the radar up to a maximum length of 20.
        int count = 0;
        int checkdata_len = 2;        //Without cyclic sending, number of frames sent
        void data_printf(const unsigned char* buff, int len);
        float decodeVal_func(int val, bool decode = false);
    public:
        int radarStatus = 0, bodysign_val = 0, static_val = 0, dynamic_val = 0;
        float dis_static = 0.0, dis_move = 0.0, speed = 0.0;
        HumanStaticLite(Stream *s);
        void recvRadarBytes();
        unsigned char* showData();
        void HumanStatic_func(bool bodysign = false);
        unsigned char* checkSetMode_func(const unsigned char* buff, int len, bool cyclic = false);
        void reset_func();
};

#endif
