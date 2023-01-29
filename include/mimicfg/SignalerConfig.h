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
		std::string ip = "localhost";
		std::string local = "local";
		std::string remote = "remote";
		std::string endpoint = "ws://localhost:8000/local";
		int port = 8000;
		bool secure = false;

		void from_toml(const toml::value& v) {
			this->ip = toml::find_or<std::string>(v, "ip", ip);
			this->local = toml::find_or<std::string>(v, "local", local);
			this->remote = toml::find_or<std::string>(v, "remote", remote);
			this->port = toml::find_or<int>(v, "port", 8000);
			this->secure = toml::find_or<bool>(v, "secure", false);

			std::string protocol = this->secure ? "wss" : "ws";
			this->endpoint = protocol + "://" + this->ip + ":" + std::to_string(this->port) + "/" + this->local;
			return;
		}
	};
}

#endif
