#pragma once

#include "names.h"
#include "ethernet.h"
#include "InetProto.h"

struct __attribute__((__packed__)) arp_payload {
    uint16 htype;
    uint16 ptype;
    uint8 hlen;
    uint8 plen;
    uint16 oper;
    uint8 src_ha[6];
    uint8 src_ip[4];
    uint8 dst_ha[6];
    uint8 dst_ip[4];
}; typedef struct arp_payload ARPPayload;

class ARPWrapper {
private:
    int sock;
    char iface[IFNAMSIZ];
    struct sockaddr_ll sock_addr;
    EthHeader ethHeader;
    ARPPayload arpPayload;
public:
    ARPWrapper(int sock, char* iface) {
        this->sock = sock;
        strcpy(this->iface, iface);
    }
    ARPWrapper(int sock) {
        this->sock = sock;
        ethernet::getIfaceBoundToSocket(this->iface, sock);
    }
    /// note there is a separate protocol for mapping MAC's to IP's
    bool set(uint8* sender_ha, uint8* sender_pa, uint8* target_ha, uint8* target_pa) {
        /// note it should be safe to set the argument pointers; the destination is in this class anyway
        // check for dst ha and pa. Sender addresses are unimportant
        // since they can be automatically determined
        /// set target ip and mac addrs:
        if(target_ha == nullptr && target_pa == nullptr) { // error
            return false;
        } else if(target_ha == nullptr) {              // arp request for hardware addr
            //uint8 broadcast[6] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
            memset(ethHeader.dst_addr, 0xFF, 6);        // remember to set this as a broadcast (unknown MAC)
            memset(arpPayload.dst_ha, 0, 6);           // set dst mac to zeroes (this means request)
            memcpy(arpPayload.dst_ip, target_pa, 4);   // auto fill dst IP
        } else if(target_pa == nullptr) {              // arp request for proto addr
            memcpy(ethHeader.dst_addr, target_ha, 6);
            memcpy(arpPayload.dst_ha, target_ha, 6);
            memset(arpPayload.dst_ip, 0, 4);
        }

        /// self MAC
        if(sender_ha == nullptr) {                              // auto fill sender MAC
            ethernet::getIfaceMAC(ethHeader.src_addr, iface);   // eth src addr
            ethernet::getIfaceMAC(arpPayload.src_ha, iface);    // arp src ha (MAC)
        } else {
            memcpy(ethHeader.src_addr, sender_ha, 6);            // copy given MAC into ethHeader
            memcpy(arpPayload.src_ha, sender_ha, 6);             // copy given MAC into arpPayload
        }
        /// self IP
        if(sender_pa == nullptr) {                              // auto fill sender IP
            ethernet::getIPFromIface(arpPayload.src_ip, iface);
        } else {
            memcpy(arpPayload.src_ip, sender_pa, 6);             // copy given IP into arpPayload
        }
        /// set header vars:
        ethHeader.ethertype = 0x0608; // ARP ethertype is 0x0806 but must be in little endian
        arpPayload.htype = 0x0100; // Ethernet is 0x0001, but must use LE
        arpPayload.ptype = 0x0008; // Internet protocol is 0x0800
        arpPayload.hlen = 6;
        arpPayload.plen = 4;
        arpPayload.oper = 0x0100; // opcode 1
        return true;
    }
    // more on-the-fly friendly
    bool set(char* sender_ha, char* sender_pa, char* target_ha, char* target_pa) {
        uint8 sender_ha_int[6];
        uint8 sender_pa_int[4];
        uint8 target_ha_int[6];
        uint8 target_pa_int[4];

        // necessary in order to pass through the nullptr's
        // TODO: no idea why this didn't throw an error
        // pointer to an array of uint8's
        uint8 (*sender_ha_int_pointer)[6];
        uint8 (*sender_pa_int_pointer)[4];
        uint8 (*target_ha_int_pointer)[6];
        uint8 (*target_pa_int_pointer)[4];
        // set nullptr vars
        if(sender_ha == nullptr) {
            sender_ha_int_pointer = nullptr;
        } else {
            sscanf(sender_ha, "%hhx:%hhx:%hhx:%hhx:%hhx:%hhx", 
                   &sender_ha_int[0], &sender_ha_int[1], &sender_ha_int[2], 
                   &sender_ha_int[3], &sender_ha_int[4], &sender_ha_int[5]);
            sender_ha_int_pointer = &sender_ha_int;
        }
        if(sender_pa == nullptr) {
            sender_pa_int_pointer = nullptr;
        } else {
            sscanf(sender_pa, "%d.%d.%d.%d", 
                   &sender_pa_int[0], &sender_pa_int[1], &sender_pa_int[2], &sender_pa_int[3]);
            sender_pa_int_pointer = &sender_pa_int;

        }

        if(target_ha == nullptr) {
            target_ha_int_pointer = nullptr;
        } else {
            sscanf(target_ha, "%hhx:%hhx:%hhx:%hhx:%hhx:%hhx",
                   &target_ha_int[0], &target_ha_int[1], &target_ha_int[2],
                   &target_ha_int[3], &target_ha_int[4], &target_ha_int[5]);
            target_ha_int_pointer = &target_ha_int;
        }

        if(target_pa == nullptr) {
            target_pa_int_pointer = nullptr;
        } else {
            sscanf(target_pa, "%d.%d.%d.%d", 
                   &target_pa_int[0], &target_pa_int[1], &target_pa_int[2], &target_pa_int[3]);
            target_pa_int_pointer = &target_pa_int;
        }

        return set(*sender_ha_int_pointer, *sender_pa_int_pointer, *target_ha_int_pointer, *target_pa_int_pointer);
    }

    bool request() {
        /// prep the packet
        uint8 buffer[64]; // arp frames do not exceed 60 bytes
        // convert structs to arrays and stitch them together
        memset(buffer, 0, 64);
        memcpy(buffer, (uint8*)&ethHeader, sizeof(EthHeader));
        memcpy((buffer+sizeof(EthHeader)), (uint8*)&arpPayload, sizeof(ARPPayload));
        // print constructed packet
        for(int i = 0; i < 8; i++) {
            for(int j = 0; j < 8; j++) {
                printf("%0.2x ", buffer[(i*8)+j]);
            }
            printf("\n");
        }
        /// write out the packet
        return ethernet::write_packet(sock, buffer, 60);

        //TODO:receive
        // currently handled by user
    }

    ARPPayload* convertBufferToStruct(uint8* buf, size_t buflen) {
        int index = 14;
        arpPayload.htype = (buf[index] << 8) + buf[index+1]; index+=2; // TODO: check for correct endian order
        arpPayload.ptype = (buf[index] << 8) + buf[index+1]; index+=2;
        arpPayload.hlen = buf[index]; index++;
        arpPayload.plen = buf[index]; index++;
        arpPayload.ptype = (buf[index] << 8) + buf[index+1]; index+=2;
        memcpy(arpPayload.dst_ha, buf+index, 6); index+=6;
        memcpy(arpPayload.dst_ip, buf+index, 4); index+=4;
        memcpy(arpPayload.src_ha, buf+index, 6); index+=6;
        memcpy(arpPayload.src_ip, buf+index, 4); index+=4; // remember, src and dst are switched in the return packet
        return &arpPayload; // can return pointer because arpPayload exists outside of this function.
    }
};
