#include "ManagedSwitch.h"
#include <iostream> 

ManagedSwitch::ManagedSwitch(const std::string& n, const std::string& i, const std::string& m, bool online, const std::string& loc,
    int ports, const std::string& manuf, const std::string& mgmtIp)
    : Switch(n, i, m, online, loc, ports, manuf), managementIp(mgmtIp) {
}

void ManagedSwitch::configureVlan(int port, int vlanId) {
    if (port > 0 && port <= numPorts) {
        vlanDatabase[port] = vlanId;
        std::cout << "[M-Switch " << name << "] Port " << port << " configured for VLAN " << vlanId << "\n";
    }
    else {
        std::cout << "[M-Switch " << name << "] Invalid port number.\n";
    }
}

void ManagedSwitch::removeVlan(int port) {
    vlanDatabase.erase(port);
    std::cout << "[M-Switch " << name << "] VLAN configuration removed from port " << port << "\n";
}

void ManagedSwitch::displayInfo() const {
    Switch::displayInfo();
    std::cout << "--- Management Features ---\n";
    std::cout << "  Management IP: " << managementIp << "\n";
    std::cout << "  VLANs Configured:\n";
    if (vlanDatabase.empty()) {
        std::cout << "    None\n";
    }
    for (const auto& vlan : vlanDatabase) {
        std::cout << "    Port " << vlan.first << " -> VLAN " << vlan.second << "\n";
    }
}

void ManagedSwitch::processPacket(const std::string& packetInfo) {
    if (!isOnline) {
        std::cout << "[M-Switch " << name << "] Cannot process packet, device is offline.\n";
        return;
    }
    std::cout << "[M-Switch " << name << "] Applying VLAN/QoS rules and forwarding... " << packetInfo << "\n";
}