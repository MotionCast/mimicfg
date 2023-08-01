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
