#ifndef PACKET_H
#define PACKET_H

#include <string>
#include <iostream>
#include <sstream> 

template<typename T>
class Packet {
private:
    std::string sourceIp;
    std::string destIp;
    T payload;

public:
    Packet(const std::string& src, const std::string& dest, const T& data)
        : sourceIp(src), destIp(dest), payload(data) {
    }

    std::string getPacketInfo() const {
        std::stringstream ss;
        ss << "Packet from " << sourceIp << " to " << destIp
            << " | Payload: " << payload;
        return ss.str();
    }

    const std::string& getSourceIp() const { return sourceIp; }
    const std::string& getDestIp() const { return destIp; }
};

template<>
inline std::string Packet<std::string>::getPacketInfo() const {
    std::stringstream ss;
    ss << "Packet from " << sourceIp << " to " << destIp
        << " | Payload: \"" << payload << "\"";
    return ss.str();
}

#endif