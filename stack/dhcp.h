#pragma once

#include "names.h"
#include "ethernet.h"
#include "InetProto.h"
#include "udp.h"

// these are usually all zeroes
struct __attribute__((__packed__)) _bootp_options {
    uint8 sname[64];
    uint8 file[128];
}; typedef struct _bootp_options BootPOptions;
// ethernet, ipv4, udp, dhcp, bootp
// D O R vA
struct __attribute__((__packed__)) _dhcp_payload {
    uint8 op;           // message type
    uint8 htype;        // hardware type (usually ethernet)
    uint8 hlen;         // hardware addr len
    uint8 hops;         // machine hops
    uint32 xid;         // transaction id - randomly generated
    uint16 secs;        // seconds elapsed
    uint16 bpflags;     // bootp flags; set to zero
    /// next comes the traditional bootp sector:
    // the next four are all zeroes if it is a type D request
    uint8 ciaddr[4];    // client ip address
    uint8 yiaddr[4];    // your ip addr
    uint8 siaddr[4];    // dhcp server ip addr
    uint8 giaddr[4];    // gateway ip addr
    uint8 chaddr[16];   // client hardware address (MAC) all the rest are zeroes
    BootPOptions bootp_opts;
    uint32 magic_cookie;// default 0x63825363 (signifies dhcp)
    uint8 opts[128]; // traditionally 64 in bootp but variable in dhcp
}; typedef struct _dhcp_payload DHCPPayload;