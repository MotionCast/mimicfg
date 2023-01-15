#include "BaseConfig.h"

#include <string>
#include <vector>
#include <iostream>
#include <string_view>

#include <toml.hpp>

using namespace mocast;

BaseConfig::BaseConfig(toml::value table) {
	auto signaling = table["signaling"];
	serverIP_ = signaling["ip"].value<std::string>().value_or(serverIP_);

	const std::optional<int> signalPort = signaling["port"].value<int>();
	serverPort_= signalPort.has_value() ?
		std::to_string(signalPort.value()) : serverPort_;
	localID_ = signaling["local"].value<std::string>().value_or(localID_);
	remoteID_ = signaling["remote"].value<std::string>().value_or(remoteID_);
	useSSL_ = signaling["secure"].value<bool>().value_or(useSSL_);

	std::string protocol = useSSL_ ? "wss" : "ws";
	endpoint_ = protocol + "://" + serverIP_ + ":" +
		serverPort_ + "/" + localID_;

	auto ice = table["ice"]["urls"];

	if (toml::array* arr = ice.as_array()) {
		arr->for_each([this](auto&& el) {
			if constexpr (toml::is_string<std::decltype(el)>) {
				iceServers_.push_back(el.get());
			}
		});
	}
}
