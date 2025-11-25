#ifndef SWITCH_H
#define SWITCH_H

#include "NetworkDevice.h"
#include <map>

class Switch : public NetworkDevice {
protected:
    int numPorts;
    std::map<int, std::string> portStatus;
    std::string manufacturer;

    std::map<std::string, int> macAddressTable;

public:
    Switch();
    Switch(const std::string& name, const std::string& ip, const std::string& mac, bool isOnline, const std::string& location,
        int ports, const std::string& manufacturer);

    virtual void connectDevice(int port, const std::string& deviceName);
    virtual void disconnectDevice(int port);

    void displayPortStatus() const;

    virtual std::string getDeviceAtPort(int port) const;

    void displayInfo() const override;

    virtual void processPacket(const std::string& packetInfo) override;
};
#endif