/** @file
 * @author Jacob SP <jacob@moca.st>
 */

#ifndef STRCONFIG_H
#define STRCONFIG_H

#include "BaseConfig.h"

#include <string_view>

#include <toml.hpp>

namespace mocast {

	/**
	 * @brief Reads a TOML configuration file from a string.
	 * Necessary for testing purposes.
	 */
	class StrConfig : public BaseConfig {
	public:
		StrConfig() : BaseConfig() {}
		/**
		 * @brief Parse a TOML string containing config parameters
		 * @param config The string_view to parse
		 */
		StrConfig(std::string_view configStr) : BaseConfig(toml::parse(configStr)) {}
	};
}

#endif
