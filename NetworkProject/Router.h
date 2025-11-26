#ifndef ROUTER_H
#define ROUTER_H

#include "NetworkDevice.h"
#include <map>

/**
 * @brief Клас, що моделює роботу маршрутизатора.
 *
 * Роутер зберігає таблицю маршрутизації та вміє знаходити шлюз
 * для заданої IP-адреси призначення.
 */
class Router : public NetworkDevice {
private:
    int numPorts;                                   ///< Кількість фізичних портів
    std::map<std::string, std::string> routingTable;///< Таблиця маршрутизації (Dest -> Gateway)
    std::string model;                              ///< Модель роутера
    std::string firmwareVersion;                    ///< Версія прошивки

public:
    /**
     * @brief Конструктор за замовчуванням.
     */
    Router();

    /**
     * @brief Параметризований конструктор.
     * @param name Назва.
     * @param ip IP.
     * @param mac MAC.
     * @param isOnline Статус.
     * @param location Розташування.
     * @param numPorts Кількість портів.
     * @param model Модель.
     * @param firmwareVersion Прошивка.
     */
    Router(const std::string& name, const std::string& ip, const std::string& mac, bool isOnline, const std::string& location,
        int numPorts, const std::string& model, const std::string& firmwareVersion);

    /**
     * @brief Додає новий маршрут у таблицю.
     *
     * @param dest IP-адреса призначення.
     * @param gateway IP-адреса шлюзу.
     */
    void addRoute(const std::string& dest, const std::string& gateway);

    /**
     * @brief Видаляє маршрут з таблиці.
     * @param dest IP-адреса призначення для видалення.
     */
    void removeRoute(const std::string& dest);

    /**
     * @brief Оновлює шлюз для існуючого маршруту.
     * @param dest IP-адреса призначення.
     * @param newGateway Новий шлюз.
     */
    void updateRoute(const std::string& dest, const std::string& newGateway);

    /**
     * @brief Шукає маршрут до вказаної адреси.
     *
     * @param dest IP-адреса призначення.
     * @return IP-адреса шлюзу або повідомлення про помилку, якщо маршрут не знайдено.
     */
    std::string findRoute(const std::string& dest) const;

    /**
     * @brief Виводить інформацію про роутер та таблицю маршрутизації.
     */
    void displayInfo() const override;

    /**
     * @brief Обробляє пакет (логіка маршрутизації).
     * @param packetInfo Інформація про пакет.
     */
    void processPacket(const std::string& packetInfo) override;
};
#endif