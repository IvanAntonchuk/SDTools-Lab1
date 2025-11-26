#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <string>
#include <iostream>

/**
 * @brief Інтерфейс мережевого протоколу.
 * Визначає контракт для відправки повідомлень.
 */
class Protocol {
public:
    /**
     * @brief Відправляє повідомлення згідно з протоколом.
     * @param message Текст повідомлення.
     * @return Рядок, що підтверджує відправку (для тестів).
     */
    virtual std::string send(const std::string& message) = 0;
    virtual ~Protocol() {}
};

/**
 * @brief Реалізація протоколу TCP (Transmission Control Protocol).
 * Гарантує доставку даних (симуляція).
 */
class TCP : public Protocol {
public:
    std::string send(const std::string& message) override;
};

/**
 * @brief Реалізація протоколу UDP (User Datagram Protocol).
 * Відправка датаграм без гарантії доставки (симуляція).
 */
class UDP : public Protocol {
public:
    std::string send(const std::string& message) override;
};
#endif