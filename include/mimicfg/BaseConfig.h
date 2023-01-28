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
		BaseConfig() {}
		/**
		 * @brief Read a TOML table and parse configuration parameters
		 * @param table A `toml::value` containing the config parameters
		 */
		BaseConfig(toml::value table);
		std::vector<std::string> IceServers() const;
		/// Return the signaling server url
		inline std::string_view ServerURL() const { return endpoint_; }
		inline std::string_view LocalID() const { return signaler_.local; }
		inline std::string_view RemoteID() const { return signaler_.remote; }
		inline const std::vector<std::string>& ICEServers() const { return ice_.urls; }
	protected:
		/// Signaling server endpoint
		std::string endpoint_;
		SignalerConfig signaler_;
		ICEConfig ice_;
	};
}

#endif
