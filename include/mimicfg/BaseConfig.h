/** @file
 * @author Jacob SP <jacob@moca.st>
 */

#ifndef BASECONFIG_H
#define BASECONFIG_H

#include <vector>
#include <string>
#include <string_view>

#include <toml.hpp>

#include "ICEConfig.h"
#include "SignalerConfig.h"

namespace mocast {

	/**
	 * @brief Parses a TOML table with configuration parameters which can be then be obtained.
	 */
	class BaseConfig {
	public:
		/**
		 * @brief Read a TOML table and parse configuration parameters
		 * @param table A `toml::value` containing the config parameters
		 */
		BaseConfig(toml::value table) {
			signaler_ = toml::find_or<SignalerConfig>(table, "signaling", SignalerConfig());
			ice_ = toml::find_or<ICEConfig>(table, "ice", ICEConfig());
		}

		/// Return the signaling server url
		std::string& ServerURL() { return signaler_.endpoint; }
		std::string& LocalID() { return signaler_.local; }
		std::string& RemoteID() { return signaler_.remote; }
		std::vector<std::string>& ICEServers() { return ice_.urls; }
	protected:
		SignalerConfig signaler_;
		ICEConfig ice_;
	};
}

#endif
