#include "pch.h"
#include "gtest/gtest.h"
#include "../NetworkProject/Router.h"
#include "../NetworkProject/Packet.h"
#include "../NetworkProject/Switch.h"
#include "../NetworkProject/ManagedSwitch.h"
#include "../NetworkProject/Graph.h"

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
    Switch s;
    s.connectDevice(1, "PC-1");

    EXPECT_EQ(s.getDeviceAtPort(1), "PC-1");
}

TEST(SwitchTests, DisconnectDevice) {
    Switch s;
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