#pragma once

#include <stdio.h>
#include "../stack/names.h"
#include "../stack/ethernet.h"
#include "../stack/dhcp.h"
#include "../stack/Level7Protocols.h"
#include <errno.h>
extern int errno;

int main(int argc, char** argv) {
    int sockfd = 0;
    if ((sockfd = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL))) < 0) {
        printf("Error creating socket\n");
        return 1;
    }
    /// bind to ens9
    strcpy(ethernet::global_iface, argv[1]);
    ethernet::bindToIface(sockfd, argv[1]);

    ethernet::printIfaceDetails();
    /*ARPWrapper arp(sockfd);

    // request mac of device with following ip:
    uint8 target_pa[4] = {192, 168, 1, 1};
    uint8 src_pa[4] = {192, 168, 1, 119};
    if (arp.set(nullptr, nullptr, nullptr, target_pa)) {
        if(arp.request()) {
            printf("arp request has been sent\n");
        } else {
            fprintf(stderr, "arp request send error\n");
        }
    } else {
        fprintf(stderr, "err arp set\n");
    }
    uint8 self_mac[6];
    ethernet::getIfaceMAC(self_mac, "ens9");
    uint8 buffer[1000];
    int len = ethernet::listenForExclusiveBytes(sockfd, buffer, self_mac);
    ARPPayload *payload = arp.convertBufferToStruct(buffer, len); // store packet as ARPPayload
    ethernet::printPacket(buffer, len);
    printf("Requested MAC: ");
    ethernet::printMAC(payload->dst_ha);
    printf("\n");
    return 0;*/
}