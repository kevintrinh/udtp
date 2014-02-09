/*******************************************
*UDTPData takes objects as arguments in its
*constructors, it then converts that object to a
*serialized and networkable form. UDTPData
*can also be used to create objects.
*******************************************/
#ifndef __UDTP_DATA
#define __UDTP_DATA
#include <iostream>
#include "UDTPPacket.h"
#include <cstring>
class UDTPPath;
class UDTPHeader;
class UDTPChunk;
class UDTPWhine;
class UDTPHandshake;

class UDTPData : public UDTPPacket {
    public:
        /*Raw data constructors. Char buffers (Deduction) coming in from recv()*/
        UDTPData(char deducePacket[3]);
        /*Serialization constructors. Objects that want to be send()'t*/
        UDTPData(UDTPPath& path);
        UDTPData(UDTPHeader& header);
        UDTPData(UDTPChunk& chunk);
        UDTPData(UDTPWhine &whine);
        UDTPData(UDTPHandshake& handshake);

        bool set_raw_buffer(char* raw){ _raw = raw; };
        char& write_to_buffer() {return  *_raw;};
        char* get_raw_buffer(); /*Retrieves transferable character buffer*/

        unsigned int get_from_socket() { return _fromSocket;};
        bool set_from_socket(unsigned int fromSocket) { _fromSocket = fromSocket;};

        unsigned short get_packet_size() { return _packetSize;};
    private:
        unsigned int _fromSocket; /*Optional holder*/
        unsigned short _packetSize;
        char* _raw; /*This is the holder for raw data*/
    };


#endif
