#include "BaseConfig.h"

#include <string>
#include <vector>
#include <iostream>
#include <string_view>

#include <toml.hpp>

using namespace mocast;

BaseConfig::BaseConfig(toml::value table) {
	signaler_ = toml::find<SignalerConfig>(table, "signaling");
	ice_ = toml::find<ICEConfig>(table, "ice");

}
