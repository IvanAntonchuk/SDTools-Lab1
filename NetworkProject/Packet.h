#ifndef PACKET_H
#define PACKET_H

#include <string>
#include <iostream>
#include <sstream>

/**
 * @brief Шаблонний клас для представлення мережевого пакету.
 *
 * Дозволяє створювати пакети з різним типом корисного навантаження (Payload).
 * @tparam T Тип даних, що передаються (наприклад, string, int).
 */
template<typename T>
class Packet {
private:
    std::string sourceIp;   ///< IP-адреса відправника
    std::string destIp;     ///< IP-адреса отримувача
    T payload;              ///< Корисне навантаження

public:
    /**
     * @brief Створює новий пакет.
     * @param src IP відправника.
     * @param dest IP отримувача.
     * @param data Дані пакету.
     */
    Packet(const std::string& src, const std::string& dest, const T& data)
        : sourceIp(src), destIp(dest), payload(data) {
    }

    /**
     * @brief Формує рядкове представлення пакету.
     * @return Рядок з заголовками та даними.
     */
    std::string getPacketInfo() const {
        std::stringstream ss;
        ss << "Packet from " << sourceIp << " to " << destIp
            << " | Payload: " << payload;
        return ss.str();
    }

    /**
     * @brief Отримати IP відправника.
     */
    const std::string& getSourceIp() const { return sourceIp; }

    /**
     * @brief Отримати IP отримувача.
     */
    const std::string& getDestIp() const { return destIp; }
};

/**
 * @brief Спеціалізація шаблону Packet для типу std::string.
 * Додає лапки навколо текстових даних.
 */
template<>
inline std::string Packet<std::string>::getPacketInfo() const {
    std::stringstream ss;
    ss << "Packet from " << sourceIp << " to " << destIp
        << " | Payload: \"" << payload << "\"";
    return ss.str();
}

#endif