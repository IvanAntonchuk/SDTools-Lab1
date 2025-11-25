#include "pch.h"
#include "gtest/gtest.h"
#include "../NetworkProject/Router.h"
#include "../NetworkProject/Packet.h"
#include "../NetworkProject/Switch.h"
#include "../NetworkProject/ManagedSwitch.h"
#include "../NetworkProject/Graph.h"
#include "../NetworkProject/Protocol.h"

TEST(RouterTests, ConstructorSetsValuesCorrectly) {
    Router r("R1", "192.168.0.1", "MAC", true, "Lab", 4, "Cisco", "v1.0");
    EXPECT_EQ(r.getName(), "R1");
    EXPECT_EQ(r.getIp(), "192.168.0.1");
}

TEST(RouterTests, AddAndFindRoute) {
    Router r;
    std::string dest = "10.0.0.5";
    std::string gw = "192.168.1.1";

    r.addRoute(dest, gw);
    std::string result = r.findRoute(dest);

    EXPECT_EQ(result, gw);
}

TEST(RouterTests, UpdateRoute) {
    Router r;
    std::string dest = "10.0.0.5";
    r.addRoute(dest, "OLD_GW");

    r.updateRoute(dest, "NEW_GW");
    std::string result = r.findRoute(dest);

    EXPECT_EQ(result, "NEW_GW");
}

TEST(RouterTests, RemoveRoute) {
    Router r;
    std::string dest = "8.8.8.8";
    r.addRoute(dest, "1.1.1.1");

    r.removeRoute(dest);
    std::string result = r.findRoute(dest);

    EXPECT_EQ(result, "Route not found");
}

TEST(PacketTests, StringPayload) {
    Packet<std::string> p("Src", "Dst", "SecretData");
    std::string info = p.getPacketInfo();

    EXPECT_NE(info.find("SecretData"), std::string::npos);
}

TEST(PacketTests, IntPayload) {
    Packet<int> p("Src", "Dst", 404);
    std::string info = p.getPacketInfo();

    EXPECT_NE(info.find("404"), std::string::npos);
}

TEST(SwitchTests, ConnectDevice) {
    Switch s("S1", "IP", "MAC", true, "Loc", 8, "Gen");
    s.connectDevice(1, "PC-1");

    EXPECT_EQ(s.getDeviceAtPort(1), "PC-1");
}

TEST(SwitchTests, DisconnectDevice) {
    Switch s("S1", "IP", "MAC", true, "Loc", 8, "Gen");
    s.connectDevice(2, "Printer");
    s.disconnectDevice(2);

    EXPECT_EQ(s.getDeviceAtPort(2), "Empty");
}

TEST(SwitchTests, PortInitiallyEmpty) {
    Switch s;

    EXPECT_EQ(s.getDeviceAtPort(5), "Empty");
}

TEST(ManagedSwitchTests, ConfigureVlan) {
    ManagedSwitch ms("MS1", "1.1.1.1", "MAC", true, "Loc", 24, "Cisco", "10.0.0.1");
    ms.configureVlan(5, 100);

    EXPECT_EQ(ms.getVlanAtPort(5), 100);
}

TEST(ManagedSwitchTests, RemoveVlan) {
    ManagedSwitch ms("MS1", "1.1.1.1", "MAC", true, "Loc", 24, "Cisco", "10.0.0.1");

    ms.configureVlan(10, 200);
    ms.removeVlan(10);

    EXPECT_EQ(ms.getVlanAtPort(10), -1);
}

TEST(GraphTests, AdjacencyList_AddRemoveEdge) {
    AdjacencyListGraph g;
    g.addNode(5);

    g.addEdge(1, 2);

    EXPECT_TRUE(g.hasEdge(1, 2));

    g.removeEdge(1, 2);

    EXPECT_FALSE(g.hasEdge(1, 2));
}

TEST(GraphTests, AdjacencyMatrix_AddEdge) {
    AdjacencyMatrixGraph g;
    g.addNode(5);

    g.addEdge(0, 4);

    EXPECT_TRUE(g.hasEdge(0, 4));
    EXPECT_FALSE(g.hasEdge(0, 3));
}

TEST(GraphTests, DirectedGraph_Directionality) {
    DirectedGraph g;
    g.addNode(5);
    g.addEdge(1, 2);

    EXPECT_TRUE(g.hasEdge(1, 2));

    EXPECT_FALSE(g.hasEdge(2, 1));
}

TEST(ProtocolTests, TCPSend) {
    TCP tcpProtocol;
    std::string msg = "Hello World";
    std::string output = tcpProtocol.send(msg);
    EXPECT_EQ(output, "TCP sending: Hello World");
}

TEST(ProtocolTests, UDPSend) {
    UDP udpProtocol;
    std::string msg = "Data Packet";
    std::string output = udpProtocol.send(msg);

    EXPECT_EQ(output, "UDP sending: Data Packet");
}

TEST(ProtocolTests, Polymorphism) {
    Protocol* p = new TCP();
    std::string output = p->send("Test");

    EXPECT_EQ(output, "TCP sending: Test");

    delete p;
}

TEST(ManagedSwitchTests, ConfigureVlan_InvalidPort_Negative) {
    ManagedSwitch ms("MS1", "IP", "MAC", true, "Loc", 24, "Cisco", "MgmtIP");
    ms.configureVlan(-5, 100);

    EXPECT_EQ(ms.getVlanAtPort(-5), -1);
}

TEST(ManagedSwitchTests, ConfigureVlan_InvalidPort_OutOfBounds) {
    ManagedSwitch ms("MS1", "IP", "MAC", true, "Loc", 24, "Cisco", "MgmtIP");
    ms.configureVlan(25, 100);

    EXPECT_EQ(ms.getVlanAtPort(25), -1);
}

TEST(RouterTests, FindRoute_NeverExisted) {
    Router r;
    std::string result = r.findRoute("1.2.3.4");

    EXPECT_EQ(result, "Route not found");
}

TEST(GraphTests, SelfLoopEdge) {
    AdjacencyListGraph g;
    g.addNode(5);
    g.addEdge(1, 1);

    EXPECT_TRUE(g.hasEdge(1, 1));
}

TEST(PacketTests, EmptyPayload) {
    Packet<std::string> p("Src", "Dst", "");
    std::string info = p.getPacketInfo();

    EXPECT_NE(info.find("Payload: \"\""), std::string::npos);
}

TEST(SwitchTests, ConnectDevice_InvalidPort_TooHigh) {
    Switch s("S1", "IP", "MAC", true, "Loc", 8, "D-Link");
    s.connectDevice(100, "HackerPC");

    EXPECT_EQ(s.getDeviceAtPort(100), "Empty");
}

TEST(SwitchTests, HotSwapDevice) {
    Switch s("S1", "IP", "MAC", true, "Loc", 8, "Gen");
    s.connectDevice(1, "PC-Old");

    EXPECT_EQ(s.getDeviceAtPort(1), "PC-Old");

    s.connectDevice(1, "PC-New");

    EXPECT_EQ(s.getDeviceAtPort(1), "PC-New");
}

TEST(RouterTests, OverwriteExistingRoute_ViaAdd) {
    Router r;
    r.addRoute("10.0.0.5", "Gateway_A");
    r.addRoute("10.0.0.5", "Gateway_B");

    EXPECT_EQ(r.findRoute("10.0.0.5"), "Gateway_B");
}

TEST(GraphTests, DirectedGraph_RemoveNode_ClearsIncidentEdges) {
    DirectedGraph g;
    g.addNode(3);

    g.addEdge(1, 2);
    EXPECT_TRUE(g.hasEdge(1, 2));
    g.removeNode(2);

    EXPECT_FALSE(g.hasEdge(1, 2));
}

TEST(GraphTests, StressTest_ManyNodes) {
    AdjacencyListGraph g;
    int nodeCount = 1000;
    for (int i = 0; i < nodeCount; ++i) {
        g.addNode(i);
    }
    for (int i = 0; i < nodeCount - 1; ++i) {
        g.addEdge(i, i + 1);
    }

    EXPECT_TRUE(g.hasEdge(0, 1));
    EXPECT_TRUE(g.hasEdge(998, 999));
}

TEST(RouterTests, StressTest_RoutingTableCheck) {
    Router r;
    int routesCount = 500;
    for (int i = 0; i < routesCount; ++i) {
        std::string ip = "192.168.1." + std::to_string(i);
        std::string gw = "10.0.0." + std::to_string(i);
        r.addRoute(ip, gw);
    }

    EXPECT_EQ(r.findRoute("192.168.1.0"), "10.0.0.0");
    EXPECT_EQ(r.findRoute("192.168.1.499"), "10.0.0.499");
}