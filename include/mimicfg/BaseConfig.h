/** @file
 * @author Jacob SP <jacob@moca.st>
 */

#ifndef BASECONFIG_H
#define BASECONFIG_H

#include <vector>
#include <string>
#include <string_view>

#include <toml.hpp>

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
		inline std::string_view LocalID() const { return localID_; }
		inline std::string_view RemoteID() const { return remoteID_; }
		inline const std::vector<std::string>& ICEServers() const { return iceServers_; }
	protected:
		/// List of ICE servers
		std::vector<std::string> iceServers_ = {};
		/// IP address of signaling server
		std::string serverIP_ {"127.0.0.1"};
		/// Port of signaling server
		std::string serverPort_ {"8000"};
		/// ID of local (operator) device
		std::string localID_ {"local"};
		/// ID of remote (teleoperated) device
		std::string remoteID_ {"remote"};
		/// Signaling server endpoint
		std::string endpoint_;
		/// Whether websockets should use secure layer
		bool useSSL_ = false;
	};
}

#endif
