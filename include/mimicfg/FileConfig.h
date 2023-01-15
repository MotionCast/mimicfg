/** @file
 * @author Jacob SP <jacob@moca.st>
 */

#ifndef FILECONFIG_H
#define FILECONFIG_H

#include "BaseConfig.h"

#include <string_view>

#include <toml.hpp>

namespace mocast {

	/**
	 * @brief Reads a `.toml` configuration file.
	 */
	class FileConfig : public BaseConfig {
	public:
		FileConfig() : BaseConfig() {}
		/**
		 * @brief Parse a `.toml` file or parse a TOML string.
		 * @param config The file to parse.
		 */
		FileConfig(std::string& configFile) : BaseConfig(toml::parse(configFile)) {}
	};
}

#endif
