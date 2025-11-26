#ifndef MANAGEDSWITCH_H
#define MANAGEDSWITCH_H

#include "Switch.h"
#include <vector>

/**
 * @brief Керований комутатор з підтримкою VLAN.
 *
 * Розширює функціональність звичайного комутатора, додаючи можливість
 * налаштування віртуальних локальних мереж (VLAN) на окремих портах.
 */
class ManagedSwitch : public Switch {
private:
    std::map<int, int> vlanDatabase; ///< База даних VLAN (Порт -> VLAN ID)
    std::string managementIp;        ///< IP-адреса для керування комутатором

public:
    /**
     * @brief Конструктор керованого комутатора.
     *
     * @param name Назва.
     * @param ip IP-адреса.
     * @param mac MAC-адреса.
     * @param isOnline Статус.
     * @param location Розташування.
     * @param ports Кількість портів.
     * @param manufacturer Виробник.
     * @param managementIp IP-адреса інтерфейсу керування.
     */
    ManagedSwitch(const std::string& name, const std::string& ip, const std::string& mac, bool isOnline, const std::string& location,
        int ports, const std::string& manufacturer, const std::string& managementIp);

    /**
     * @brief Призначає VLAN ID конкретному порту.
     *
     * @param port Номер порту.
     * @param vlanId Ідентифікатор VLAN (наприклад, 10, 20, 100).
     */
    void configureVlan(int port, int vlanId);

    /**
     * @brief Видаляє налаштування VLAN з порту.
     * @param port Номер порту.
     */
    void removeVlan(int port);

    /**
     * @brief Отримати VLAN ID на порту.
     * @param port Номер порту.
     * @return VLAN ID або -1, якщо VLAN не налаштовано.
     */
    int getVlanAtPort(int port) const;

    /**
     * @brief Виводить детальну інформацію, включаючи таблицю VLAN.
     */
    void displayInfo() const override;

    /**
     * @brief Обробляє пакет з урахуванням правил VLAN.
     * @param packetInfo Інформація про пакет.
     */
    void processPacket(const std::string& packetInfo) override;
};

#endif