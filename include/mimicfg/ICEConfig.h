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
		std::vector<std::string> urls;
	};
}
