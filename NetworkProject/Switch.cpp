#include "Switch.h"

Switch::Switch() : NetworkDevice(), numPorts(0), manufacturer("Unknown") {}

Switch::Switch(const std::string& n, const std::string& i, const std::string& m, bool online, const std::string& loc,
    int ports, const std::string& manuf)
    : NetworkDevice(n, i, m, online, loc), numPorts(ports), manufacturer(manuf) {
}

void Switch::connectDevice(int port, const std::string& deviceName) {
    if (port < 1 || port > numPorts) {
        std::cout << "[Switch " << name << "] Error: Port " << port << " does not exist!\n";
        return;
    }

    portStatus[port] = deviceName;
    std::string fakeMac = "FA:KE:MA:C:FF:" + std::to_string(port);
    macAddressTable[fakeMac] = port;
    std::cout << "[Switch " << name << "] Learned fake MAC " << fakeMac << " on port " << port << "\n";
}

void Switch::disconnectDevice(int port) {
    portStatus.erase(port);
}

void Switch::displayPortStatus() const {
    for (const auto& p : portStatus)
        std::cout << "Port " << p.first << " -> " << p.second << "\n";
}

void Switch::displayInfo() const {
    NetworkDevice::displayInfo();
    std::cout << "Manufacturer: " << manufacturer << "\nPorts: " << numPorts << "\n";

    std::cout << "MAC Address Table:\n";
    if (macAddressTable.empty()) {
        std::cout << "  (Empty)\n";
    }
    for (const auto& entry : macAddressTable) {
        std::cout << "  " << entry.first << " -> Port " << entry.second << "\n";
    }

    displayPortStatus();
}

void Switch::processPacket(const std::string& packetInfo) {
    if (!isOnline) {
        std::cout << "[Switch " << name << "] Cannot process packet, device is offline.\n";
        return;
    }
    std::cout << "[Switch " << name << "] Forwarding packet... " << packetInfo << "\n";
}

std::string Switch::getDeviceAtPort(int port) const {
    auto it = portStatus.find(port);
    if (it != portStatus.end()) {
        return it->second;
    }
    return "Empty";
}