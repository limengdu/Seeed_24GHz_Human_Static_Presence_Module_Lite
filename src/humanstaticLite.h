#ifndef _HUMANSTATICLITE_H__
#define _HUMANSTATICLITE_H__

#define MESSAGE_HEAD1 0x53       //Data frame header1
#define MESSAGE_HEAD2 0x59       //Data frame header2

#define MESSAGE_END1  0x54
#define MESSAGE_END2  0x43

#define HUMANSTATUS   0x80
#define HUMANEXIST    0x01
#define HUMANMOVE     0x02
#define HUMANSIGN     0x03
#define HUMANDIRECT   0x0B

#define SOMEBODY      0x01       //Somebody move
#define NOBODY        0x00       //No one here

#define NONE          0x00
#define SOMEBODY_STOP 0x01       //Somebody stop
#define SOMEBODY_MOVE 0x02       //Somebody move

#define CA_CLOSE      0x01       //Someone approaches
#define CA_AWAY       0x02       //Some people stay away


#define DETAILSTATUS  0x08       //
#define DETAILINFO    0x01
#define DETAILDIRECT  0x06
#define DETAILSIGN    0x07

#define SOMEONE       0x01
#define NOONE         0x02
#define NOTHING       0x03
#define SOMEONE_STOP  0x04
#define SOMEONE_MOVE  0x05
#define HUMANSIGN     0x06
#define SOMEONE_CLOSE 0x07
#define SOMEONE_AWAY  0x08
#define DETAILMESSAGE 0x09

#define reset_frame_len 10

const unsigned char reset_frame[10] = {0x53, 0x59, 0x01, 0x02, 0x00, 0x01, 0x0F, 0xBF, 0x54, 0x43};

class HumanStaticLite{
    private:
        Stream *stream;   // e.g. SoftwareSerial or Serial1
        boolean newData;
        byte dataLen;
        unsigned char Msg[20] = {0};
        int count = 0;
        int checkdata_len = 2;
        void data_printf(const unsigned char* buff, int len);
    public:
        int radarStatus = 0, bodysign_val = 0, static_val = 0, dynamic_val = 0, dis_static = 0, dis_move = 0, speed = 0;
        HumanStaticLite(Stream *s);
        void recvRadarBytes();
        void showData();
        void HumanStatic_func(bool bodysign = false);
        void checkSetMode_func(const unsigned char* buff, int len, bool cyclic = false);
        void reset_func();
};

#endif
