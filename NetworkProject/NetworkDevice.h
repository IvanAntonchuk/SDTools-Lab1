#ifndef NETWORKDEVICE_H
#define NETWORKDEVICE_H

#include <string>
#include <vector>
#include <iostream>
#include "Packet.h" 

class NetworkDevice {
protected:
    std::string name;
    std::string ip;
    std::string mac;
    bool isOnline;
    std::string location;
public:
    NetworkDevice();
    NetworkDevice(const std::string& name, const std::string& ip, const std::string& mac, bool isOnline, const std::string& location);

    virtual void displayInfo() const;
    virtual void pingTest() const;
    virtual void processPacket(const std::string& packetInfo) = 0;

    std::string getIp() const { return ip; }
    std::string getName() const { return name; }
};

#endif