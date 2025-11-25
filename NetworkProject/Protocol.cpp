#include "Protocol.h"

std::string TCP::send(const std::string& message) {
    std::string output = "TCP sending: " + message;
    std::cout << output << "\n";
    return output;
}

std::string UDP::send(const std::string& message) {
    std::string output = "UDP sending: " + message;
    std::cout << output << "\n";
    return output;
}