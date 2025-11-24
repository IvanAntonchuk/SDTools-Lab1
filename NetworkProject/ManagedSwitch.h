#ifndef MANAGEDSWITCH_H
#define MANAGEDSWITCH_H

#include "Switch.h"
#include <vector>

class ManagedSwitch : public Switch {
private:
    std::map<int, int> vlanDatabase;
    std::string managementIp;

public:
    ManagedSwitch(const std::string& name, const std::string& ip, const std::string& mac, bool isOnline, const std::string& location,
        int ports, const std::string& manufacturer, const std::string& managementIp);

    void configureVlan(int port, int vlanId);
    void removeVlan(int port);

    void displayInfo() const override;
    void processPacket(const std::string& packetInfo) override;
};

#endif