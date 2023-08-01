/** @file
 * @author Jacob SP <jacob@moca.st>
 */

#ifndef KALMAN_CFG_H
#define KALMAN_CFG_H

#include <vector>
#include <toml.hpp>

namespace mocast {
	/**
	 * @brief TOML conversion of Kalman Filter config.
	 */
	struct KalmanConfig {
		std::vector<double> process_noise = {};
		std::vector<double> measurement_noise = {};
		std::vector<double> estimate_error = {};

		void from_toml(const toml::value& v) {
			this->process_noise = toml::find<std::vector<double>>(v, "process_noise");
			this->measurement_noise = toml::find<std::vector<double>>(v, "measurement_noise");
			this->estimate_error = toml::find<std::vector<double>>(v, "estimate_error");
			return;
		}
	};
}

#endif
