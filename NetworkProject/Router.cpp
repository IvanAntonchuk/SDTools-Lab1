#include "Router.h"

Router::Router() : NetworkDevice(), numPorts(0), model("Unknown"), firmwareVersion("1.0") {}

Router::Router(const std::string& n, const std::string& i, const std::string& m, bool online, const std::string& loc,
    int ports, const std::string& mod, const std::string& fw)
    : NetworkDevice(n, i, m, online, loc), numPorts(ports), model(mod), firmwareVersion(fw) {
}

void Router::addRoute(const std::string& dest, const std::string& gateway) {
    routingTable[dest] = gateway;
}

void Router::removeRoute(const std::string& dest) {
    routingTable.erase(dest);
}

void Router::updateRoute(const std::string& dest, const std::string& newGateway) {
    routingTable[dest] = newGateway;
}

std::string Router::findRoute(const std::string& dest) const {
    auto it = routingTable.find(dest);
    if (it != routingTable.end()) return it->second;
    return "Route not found";
}

void Router::displayInfo() const {
    NetworkDevice::displayInfo();
    std::cout << "Model: " << model << "\nFirmware: " << firmwareVersion << "\nPorts: " << numPorts << "\nRoutes:\n";
    for (const auto& r : routingTable)
        std::cout << r.first << " -> " << r.second << "\n";
}

void Router::processPacket(const std::string& packetInfo) {
    if (!isOnline) {
        std::cout << "[Router " << name << "] Cannot process packet, device is offline.\n";
        return;
    }
    std::cout << "[Router " << name << "] Processing packet... " << packetInfo << "\n";
}