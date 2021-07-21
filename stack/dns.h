#include "names.h"
#include <string>
#include <vector>

// no need to pack since it will have to be manually converted to an array anyways
class DNSPayload {
private:
    char buf[500];
public:
    uint16 xid;
    union _hflags {
        struct __attribute__((__packed__)) {
            int qr: 1;
            int opcode: 4;
            int aa: 1;
            int tc: 1;
            int rd: 1;
            int ra: 1;
            int z: 3; // 3 zero bits
            int rcode: 4;
        } hflags_struct; // 16 bit
        uint16 hflags_uint16;
    } hflags;
    uint16 qdcount = 1;
    uint16 ancount = 0;
    uint16 nscount = 0;
    uint16 arcount = 0;
    //char qname[48];
    std::string qname;
    uint16 qtype;
    uint16 qclass;
    //char rrname[64]; // variable length
    std::string rrname;
    uint16 rrtype;
    uint16 classc;
    uint32 ttl;
    uint16 rdlength;
    std::vector<uint8> rdata; // extra rr-specific data
    int rdata_len;

    operator uint8*() {
        int offset = 0;
        //memcpy(buf, &xid, 2); offset+=2;
        //memcpy(buf+offset, &hflags, sizeof(hflags)); offset+=sizeof(hflags);
        return nullptr;
        //memcpy(buf+offset, rrname, strlen(rrname)) offset+=strlen(rrname); /// idk
        //memcpy(buf+offset, )
    }
};

namespace dns {
    const int A = 1;
    const int AAAA = 28;
    const int CNAME = 5;
    const int PTR = 12;
    const int KEY = 25;
    const int MX = 15;
    const int NAPTR = 35;
    const int NS = 2;
    const int SOA = 6;
    const int SRV = 33;
    const int TXT = 16;
    const int URI = 256;
    const int HTTPS = 65;
};