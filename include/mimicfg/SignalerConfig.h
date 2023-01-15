/** @file
 * @author Jacob SP <jacob@moca.st>
 */

#ifndef SIGNALER_CFG_H
#define SIGNALER_CFG_H

#include <string>
#include <toml.hpp>

namespace mocast {
	/**
	 * @brief TOML conversion of signaler config.
	 */
	struct SignalerConfig {
		std::string ip;
		std::string local;
		std::string remote;
		int port;
	};
}
