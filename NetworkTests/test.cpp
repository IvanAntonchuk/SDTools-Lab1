#include "pch.h"
#include "gtest/gtest.h"
#include "../NetworkProject/Router.h"
#include "../NetworkProject/Packet.h"

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