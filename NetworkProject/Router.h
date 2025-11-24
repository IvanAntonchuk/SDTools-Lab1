#ifndef ROUTER_H
#define ROUTER_H

#include "NetworkDevice.h"
#include <map>

class Router : public NetworkDevice {
private:
    int numPorts;
    std::map<std::string, std::string> routingTable;
    std::string model;
    std::string firmwareVersion;
public:
    Router();
    Router(const std::string& name, const std::string& ip, const std::string& mac, bool isOnline, const std::string& location,
        int numPorts, const std::string& model, const std::string& firmwareVersion);

    void addRoute(const std::string& dest, const std::string& gateway);
    void removeRoute(const std::string& dest);
    void updateRoute(const std::string& dest, const std::string& newGateway);
    std::string findRoute(const std::string& dest) const;

    void displayInfo() const override;

    void processPacket(const std::string& packetInfo) override;
};
#endif