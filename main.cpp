#include <stdio.h>

//prototypes
using namespace std;
typedef unsigned char uint8;
typedef unsigned short uint16;
void getIfaceMAC(uint8* retval, int sockfd, char* name);
void printMAC(uint8* mac);

struct __attribute__((__packed__)) arp_pack {
    uint16 htype;
    uint16 ptype;
    uint8 hlen;
    uint8 plen;
    uint16 oper;
    uint8 src_ha[6];
    uint8 src_ip[4];
    uint8 dst_ha[6];
    uint8 dst_ip[4];
};

int main(int argc, char** argv) {
    // create the socket
    int sockfd = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL)); //IPPROTO_RAW);

    // bind to interface at argv[1]
    struct ifreq ifr;
    memset(&ifr, 0, sizeof(ifr)); // set memory to all zeroes
    snprintf(ifr.ifr_name, sizeof(ifr.ifr_name), argv[1]); // denote which interface to use
    if (setsockopt(sockfd, SOL_SOCKET, SO_BINDTODEVICE, (void *)&ifr, sizeof(ifr)) < 0) {
        fprintf(stderr, "Error binding socket to device %s", argv[1]);
    }
    // print mac of interface
    uint8 selfMAC[6]; getIfaceMAC(selfMAC, sockfd, argv[1]); printMAC(selfMAC);

}

void getIfaceMAC(uint8* retval, int sockfd, char* name) {
    struct ifreq if_mac;

    memset(&if_mac, 0, sizeof(struct ifreq));
    strncpy(if_mac.ifr_name, name, IFNAMSIZ-1);
    if (ioctl(sockfd, SIOCGIFHWADDR, &if_mac) < 0)
        perror("SIOCGIFHWADDR");
    for(int i = 0; i < 6; i++) {
        retval[i] = (unsigned char) if_mac.ifr_hwaddr.sa_data[i] ;
    }
}

void printMAC(uint8* mac) {
    printf("%0.2x:%0.2x:%0.2x:%0.2x:%0.2x:%0.2x\n", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
}

void write_packet(int sock, uint8* packet, int len) {
    const struct sockaddr_in dst_addr;
    dst_addr.sin_family = AFu
    if(sendto(sock, (void*) packet, len, nullptr, &dst_addr, sizeof(destaddr))) {

    }
}