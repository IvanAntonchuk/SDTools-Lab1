#include "NetworkDevice.h"

NetworkDevice::NetworkDevice() : name("Unknown"), ip("0.0.0.0"), mac("00:00:00:00:00:00"), isOnline(false), location("Unknown") {}

NetworkDevice::NetworkDevice(const std::string& n, const std::string& i, const std::string& m, bool online, const std::string& loc)
    : name(n), ip(i), mac(m), isOnline(online), location(loc) {
}

void NetworkDevice::displayInfo() const {
    std::cout << "Device: " << name << "\nIP: " << ip << "\nMAC: " << mac << "\nOnline: " << (isOnline ? "Yes" : "No") << "\nLocation: " << location << "\n";
}

void NetworkDevice::pingTest() const {
    std::cout << "Pinging " << ip << " ... Success!\n";
}