#ifndef SWITCH_H
#define SWITCH_H

#include "NetworkDevice.h"
#include <map>

/**
 * @brief Клас, що моделює роботу мережевого комутатора (світча).
 *
 * Зберігає таблицю MAC-адрес та стан портів. Дозволяє підключати пристрої до портів.
 */
class Switch : public NetworkDevice {
protected:
    int numPorts;                               ///< Загальна кількість портів
    std::map<int, std::string> portStatus;      ///< Стан портів (Номер порту -> Назва пристрою)
    std::string manufacturer;                   ///< Виробник

    std::map<std::string, int> macAddressTable; ///< Таблиця MAC-адрес (MAC -> Порт)

public:
    /**
     * @brief Конструктор за замовчуванням.
     */
    Switch();

    /**
     * @brief Параметризований конструктор.
     * Детальний опис параметрів див. у NetworkDevice.
     * @param ports Кількість портів.
     * @param manufacturer Виробник.
     */
    Switch(const std::string& name, const std::string& ip, const std::string& mac, bool isOnline, const std::string& location,
        int ports, const std::string& manufacturer);

    /**
     * @brief Підключає пристрій до вказаного порту.
     *
     * Метод емулює навчання комутатора (MAC learning).
     * @param port Номер порту (1..numPorts).
     * @param deviceName Назва підключеного пристрою.
     */
    virtual void connectDevice(int port, const std::string& deviceName);

    /**
     * @brief Відключає пристрій від порту.
     * @param port Номер порту.
     */
    virtual void disconnectDevice(int port);

    /**
     * @brief Повертає назву пристрою на порту.
     * @param port Номер порту.
     * @return Назва пристрою або "Empty", якщо порт вільний.
     */
    virtual std::string getDeviceAtPort(int port) const;

    /**
     * @brief Виводить статус усіх портів.
     */
    void displayPortStatus() const;

    /**
     * @brief Виводить повну інформацію про комутатор.
     */
    void displayInfo() const override;

    /**
     * @brief Обробляє пакет (комутація кадрів).
     */
    virtual void processPacket(const std::string& packetInfo) override;
};
#endif