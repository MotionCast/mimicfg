/** @file
 * @author Jacob SP <jacob@moca.st>
 */

#ifndef ICE_CFG_H
#define ICE_CFG_H

#include <string>
#include <vector>
#include <toml.hpp>

namespace mocast {
	/**
	 * @brief TOML conversion of ICE server config.
	 */
	struct ICEConfig {
		std::vector<std::string> urls = {};

		void from_toml(const toml::value& v) {
			this->urls = toml::find<std::vector<std::string>>(v, "urls");
			return;
		}
	};
}

#endif
