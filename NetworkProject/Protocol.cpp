#include "Protocol.h"

void TCP::send(const std::string& message) {
    std::cout << "TCP sending: " << message << "\n";
}

void UDP::send(const std::string& message) {
    std::cout << "UDP sending: " << message << "\n";
}   