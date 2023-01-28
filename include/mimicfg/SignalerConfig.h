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
		std::string endpoint;
		int port;
		bool ssl;

		void from_toml(const toml::value& v) {
			this->ip = toml::find_or<std::string>(v, "ip", "localhost");
			this->local = toml::find_or<std::string>(v, "local", "local");
			this->remote = toml::find_or<std::string>(v, "remote", "remote");
			this->port = toml::find_or<int>(v, "port", 8000);
			this->ssl = toml::find_or<bool>(v, "ssl", false);

			std::string protocol = this->ssl ? "wss" : "ws";
			this->endpoint = protocol + "://" + this->ip + ":" + std::to_string(this->port) + "/" + this->local;
		}
	};
}

#endif
