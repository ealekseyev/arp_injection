//#define _PRINT // comment to enable prints
//TODO: cleanup, redelegate, and delete this file
void getIfaceMAC_old(uint8* retval, int sockfd, char* name);
void printMAC(uint8* mac);

void getIfaceMAC_old(uint8* retval, int sockfd, char* name) {
    struct ifreq if_mac;

    memset(&if_mac, 0, sizeof(if_mac));
    strncpy(if_mac.ifr_name, name, IF_NAMESIZE-1);
    if (ioctl(sockfd, SIOCGIFHWADDR, &if_mac) < 0)
        perror("SIOCGIFHWADDR");
    for(int i = 0; i < 6; i++) {
        retval[i] = (unsigned char) if_mac.ifr_hwaddr.sa_data[i] ;
    }
}

void printMAC(uint8* mac) {
    printf("%0.2x:%0.2x:%0.2x:%0.2x:%0.2x:%0.2x\n", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
}