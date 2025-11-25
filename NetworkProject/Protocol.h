#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <string>
#include <iostream>

class Protocol {
public:
    virtual std::string send(const std::string& message) = 0;
    virtual ~Protocol() {}
};

class TCP : public Protocol {
public:
    std::string send(const std::string& message) override;
};

class UDP : public Protocol {
public:
    std::string send(const std::string& message) override;
};
#endif