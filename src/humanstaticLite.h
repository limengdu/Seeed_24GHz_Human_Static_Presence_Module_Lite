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



class HumanStaticLite{
    private:
        Stream *stream;   // e.g. SoftwareSerial or Serial1
        int radarStatus;
        byte dataLen;
        boolean newData = false;
        unsigned char Msg[20] = {0};
        int count = 0;
        int checkdata_len = 2;
        void data_printf(const unsigned char* buff, int len);
    public:
        HumanStaticLite(Stream *s);
        const char* str;
        void recvRadarBytes();
        void showData();
        void HumanStatic_func(bool bodysign = false);
        void checkSetMode_func(const unsigned char* buff, int len, bool cyclic = false);
};

#endif