#include "Router.h"
#include "Switch.h"
#include "Protocol.h"
#include "Graph.h"
#include "ManagedSwitch.h"
#include "Packet.h"
#include <algorithm>
#include <limits>


void testDynamicPolymorphism(NetworkDevice& device) {
    std::cout << "\n--- Testing device: " << device.getName() << " ---\n";
    Packet<std::string> testPacket(device.getIp(), "10.0.0.1", "Test_Data");


    device.processPacket(testPacket.getPacketInfo());
}

void clearInputBuffer() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int main() {
    Router r("R1", "192.168.1.1", "AA:BB:CC:DD:EE:FF", true, "ServerRoom", 4, "RTX1000", "v2.1");
    Switch s("S1", "192.168.1.2", "11:22:33:44:55:66", true, "Lab", 8, "NetMaker");
    ManagedSwitch ms("MS1", "192.168.1.3", "77:88:99:AA:BB:CC", true, "Core", 24, "Cisco", "192.168.1.4");

    TCP tcp;
    UDP udp;
    AdjacencyListGraph graph;

    int choice;
    do {
        std::cout << "\nMenu:\n"
            << "1. Show Router Info\n"
            << "2. Add Route\n"
            << "3. Show Switch Info\n"
            << "4. Connect Device to Switch\n"
            << "5. Send TCP\n"
            << "6. Send UDP\n"
            << "7. Graph Add Edge\n"
            << "8. Graph Display\n"
            << "--- (NEW FEATURES) ---\n"
            << " 9. Show Managed Switch Info\n"
            << "10. Configure VLAN on Managed Switch\n"
            << "11. Demo: Static Polymorphism (Packet<T>)\n"
            << "12. Demo: Dynamic Polymorphism (processPacket)\n"
            << "0. Exit\n"
            << "Choice: ";

        while (!(std::cin >> choice)) {
            std::cout << "Error: Please enter a number.\n";
            std::cin.clear();
            clearInputBuffer();
            std::cout << "Choice: ";
        }
        clearInputBuffer();

        switch (choice) {
        case 1:
            r.displayInfo();
            break;

        case 2: {
            std::string dest, gw;
            std::cout << "Destination: "; std::cin >> dest;
            std::cout << "Gateway: "; std::cin >> gw;
            r.addRoute(dest, gw);
            std::cout << "Route added.\n";
            break;
        }

        case 3:
            s.displayInfo();
            break;

        case 4: {
            int port;
            std::string dev;
            std::cout << "Port: "; std::cin >> port;
            clearInputBuffer();
            std::cout << "Device Name: "; std::getline(std::cin, dev);
            s.connectDevice(port, dev);
            std::cout << "Device connected.\n";
            break;
        }

        case 5: {
            std::string msg;
            std::cout << "Message: "; std::getline(std::cin, msg);
            tcp.send(msg);
            break;
        }

        case 6: {
            std::string msg;
            std::cout << "Message: "; std::getline(std::cin, msg);
            udp.send(msg);
            break;
        }

        case 7: {
            int from, to;
            std::cout << "From: "; std::cin >> from;
            std::cout << "To: "; std::cin >> to;
            clearInputBuffer();

            graph.addNode(std::max(from, to));

            graph.addEdge(from, to);
            std::cout << "Edge added from " << from << " to " << to << "\n";
            break;
        }

        case 8:
            std::cout << "Graph:\n";
            graph.displayGraph();
            break;

        case 9:
            ms.displayInfo();
            break;

        case 10: {
            int port, vlan;
            std::cout << "Port: "; std::cin >> port;
            std::cout << "VLAN ID: "; std::cin >> vlan;
            clearInputBuffer();
            ms.configureVlan(port, vlan);
            break;
        }

        case 11: {
            std::cout << "--- Demo: Static Polymorphism (Packet<T>) ---\n";
            Packet<std::string> strPacket("1.1.1.1", "2.2.2.2", "Hello World");
            std::cout << strPacket.getPacketInfo() << "\n";
            Packet<int> intPacket("1.1.1.1", "2.2.2.2", 404);
            std::cout << intPacket.getPacketInfo() << "\n";
            break;
        }

        case 12: {
            std::cout << "--- Demo: Dynamic Polymorphism (processPacket) ---\n";
            std::cout << "Calling the same helper function for 3 different object types:\n";
            testDynamicPolymorphism(r);
            testDynamicPolymorphism(s);
            testDynamicPolymorphism(ms);
            std::cout << "\nNote: Each object called its own version of .processPacket()\n";
            break;
        }

        case 0:
            std::cout << "Exiting...\n";
            break;

        default:
            std::cout << "Invalid choice! Try again.\n";
        }
    } while (choice != 0);

    return 0;
}