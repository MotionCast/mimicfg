#include "mimicfg/BaseConfig.h"

#include <string_view>
#include <gtest/gtest.h>
#include <toml.hpp>

using namespace mocast;
using namespace std::literals;
using namespace toml::literals::toml_literals;

/**
 * @brief An empty configuration file should be valid and have default values.
 */
TEST(UserConfigTest, EmptyConfig) {
	auto config = BaseConfig(u8R"()"_toml);

	EXPECT_EQ("local", config.LocalID());
	EXPECT_EQ("remote", config.RemoteID());
	EXPECT_EQ("ws://localhost:8000/local", config.ServerURL());
}

/**
 * @brief Config parameters for the signaling server should match.
 */
TEST(UserConfigTest, BasicSignalingConfig) {
	auto config = BaseConfig(u8R"(
		[signaling]
		ip = "rtc.moca.st"
		port = 9000
		local = "pilot"
		remote = "robot"
		secure = true
	)"_toml);
	EXPECT_EQ("pilot", config.LocalID());
	EXPECT_EQ("robot", config.RemoteID());
	EXPECT_EQ("wss://rtc.moca.st:9000/pilot", config.ServerURL());
}

TEST(UserConfigTest, BasicICEConfig) {
	auto config = BaseConfig(u8R"(
		[ice]
		urls = ["http://username:password@example.com:8080"]
	)"_toml);
	EXPECT_EQ("http://username:password@example.com:8080", config.ICEServers()[0]);
}

TEST(UserConfigTest, BasicKalmanConfig) {
	auto config = BaseConfig(u8R"(
		[kalman]
		process_noise = [ 0.1, 0.22, 3.3 ]
		measurement_noise = [ 0.123, 0.31415, 99.0 ]
		estimate_error = [ 99.0, 0.1, 0.0, 1.0 ]
	)"_toml);

	EXPECT_EQ(0.31415, config.MeasurementNoise()[1]);
	EXPECT_EQ(0, config.EstimateError()[2]);
}

TEST(UserConfigTest, BasicNodesConfig) {
	auto config = BaseConfig(u8R"(
		[[nodes]]
		id = 0
		parent = 0
		serial = "SERIAL1"
		name = "ROOT"

		[[nodes]]
		id = 1
		parent = 0
		serial = "SERIAL2"
		name = "RARM"

		[[nodes]]
		id = 2
		parent = 1
		serial = "SERIAL3"
		name = "RHAND"

		[[nodes]]
		id = 3
		parent = 0
		serial = "SERIAL4"
		name = "LARM"

		[[nodes]]
		id = 4
		parent = 3
		serial = "SERIAL5"
		name = "LHAND"
	)"_toml);

	EXPECT_EQ("ROOT", config.GetNode().name);
	EXPECT_EQ("RARM", config.GetNode(1).name);
	EXPECT_EQ("RHAND", config.GetNode(2).name);
	EXPECT_EQ("LARM", config.GetNode(3).name);
	EXPECT_EQ("LHAND", config.GetNode(4).name);

	EXPECT_EQ(0, config.GetNode().parent);
	EXPECT_EQ(0, config.GetNode(1).parent);
	EXPECT_EQ(1, config.GetNode(2).parent);
	EXPECT_EQ(0, config.GetNode(3).parent);
	EXPECT_EQ(3, config.GetNode(4).parent);
}
