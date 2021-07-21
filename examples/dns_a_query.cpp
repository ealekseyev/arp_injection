#include <stdio.h>
#include "../stack/ethernet.h"
#include "../stack/udp.h"
#include "../stack/InetProto.h"
#include "../stack/dns.h"

EthHeader ethHeader;
IPHeader ipHeader;
UDPHeader udpHeader;
DNSPayload dnsPayload;

uint8 self_mac[6];

int main(int argc, char** argv) {
    ethernet::getIfaceMAC(self_mac, argv[1]);
}