#ifndef NETWORKDEVICE_H
#define NETWORKDEVICE_H

#include <string>
#include <vector>
#include <iostream>
#include "Packet.h"

/**
 * @brief Абстрактний базовий клас для всіх мережевих пристроїв.
 *
 * Цей клас визначає спільні властивості (IP, MAC, статус) та інтерфейс
 * для всіх пристроїв у мережі (роутери, комутатори тощо).
 */
class NetworkDevice {
protected:
    std::string name;       ///< Назва пристрою (hostname)
    std::string ip;         ///< IP-адреса пристрою
    std::string mac;        ///< MAC-адреса пристрою
    bool isOnline;          ///< Статус підключення (true - онлайн)
    std::string location;   ///< Фізичне розташування пристрою

public:
    /**
     * @brief Конструктор за замовчуванням.
     * Ініціалізує пристрій з пустими параметрами.
     */
    NetworkDevice();

    /**
     * @brief Параметризований конструктор.
     *
     * @param name Назва пристрою.
     * @param ip IP-адреса.
     * @param mac MAC-адреса.
     * @param isOnline Початковий статус (онлайн/офлайн).
     * @param location Місцезнаходження.
     */
    NetworkDevice(const std::string& name, const std::string& ip, const std::string& mac, bool isOnline, const std::string& location);

    /**
     * @brief Виводить інформацію про пристрій у консоль.
     * @see displayInfo() у спадкоємцях.
     */
    virtual void displayInfo() const;

    /**
     * @brief Симуляція Ping-тесту.
     * Виводить повідомлення про успішний пінг до цього пристрою.
     */
    virtual void pingTest() const;

    /**
     * @brief Обробка вхідного пакету.
     * Чисто віртуальний метод, який має бути реалізований у спадкоємцях.
     *
     * @param packetInfo Рядок з інформацією про пакет.
     */
    virtual void processPacket(const std::string& packetInfo) = 0;

    /**
     * @brief Отримати IP-адресу.
     * @return Рядок з IP-адресою.
     */
    std::string getIp() const { return ip; }

    /**
     * @brief Отримати назву пристрою.
     * @return Рядок з іменем (hostname).
     */
    std::string getName() const { return name; }
};

#endif