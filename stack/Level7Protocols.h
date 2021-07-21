#pragma once

#include "ethernet.h"
#include "InetProto.h"
#include "dhcp.h"
#include "arp.h"
#include "udp.h"

struct __attribute__((__packed__)) _udp_packet_full {
    EthHeader eth;
    IPHeader ip;
    UDPHeader udp;
}; typedef struct _udp_packet_full UDPPacket;

struct __attribute__((__packed__)) _dhcp_packet_full {
    EthHeader eth;
    IPHeader ip;
    UDPHeader udp;
    DHCPPayload dhcp;
}; typedef struct _dhcp_packet_full DHCPPacket;

struct __attribute__((__packed__)) _arp_packet_full {
    EthHeader eth;
    ARPPayload arp;
}; typedef struct _arp_packet_full ARPPacket;

struct __attribute__((__packed__)) _dns_packet_full {
    EthHeader eth;
    IPHeader ip;
    UDPHeader udp;
     // (this will be the dns payload)
}; typedef struct _dns_packet_full DNSPacket;

