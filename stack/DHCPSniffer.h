//
// Created by root on 7/11/21.
//

#include "ethernet.h"
#include "InetProto.h"
#include "udp.h"
#include "dhcp.h"
#ifndef ARP_INJECTION_DHCPSNIFFER_H
#define ARP_INJECTION_DHCPSNIFFER_H

class DHCPSniffer {
public:
    EthHeader ethHeader;
    IPHeader ipHeader;
    UDPHeader udpHeader;
    DHCPPayload dhcpPayload;
    BootPOptions bootpOpts;
    uint8 payload[200];

    void sniff() {

    }
};

#endif //ARP_INJECTION_DHCPSNIFFER_H
