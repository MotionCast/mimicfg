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
#include "KalmanConfig.h"
#include "NodesConfig.h"

namespace mocast {

	/**
	 * @brief Parses a TOML table with configuration parameters which can be then be obtained.
	 */
	class BaseConfig {
	public:
		BaseConfig() {
			signaler_ = SignalerConfig();
			ice_ = ICEConfig();
			kalman_ = KalmanConfig();
			nodes_ = NodesConfig();
		}

		/**
		 * @brief Read a TOML table and parse configuration parameters
		 * @param table A `toml::value` containing the config parameters
		 */
		BaseConfig(toml::value table) {
			signaler_ = toml::find_or<SignalerConfig>(table, "signaling", SignalerConfig());
			ice_ = toml::find_or<ICEConfig>(table, "ice", ICEConfig());
			kalman_ = toml::find_or<KalmanConfig>(table, "kalman", KalmanConfig());

			const auto nodes = toml::find_or<std::vector<toml::table>>(table, "nodes", {});
			nodes_ = NodesConfig(nodes);
		}

		// Signaler Config
		/// Return the signaling server url
		std::string& ServerURL() { return signaler_.endpoint; }
		std::string& LocalID() { return signaler_.local; }
		std::string& RemoteID() { return signaler_.remote; }

		// ICE Config
		std::vector<std::string>& ICEServers() { return ice_.urls; }

		// Kalman Config
		std::vector<double>& ProcessNoise() { return kalman_.process_noise; }
		std::vector<double>& EstimateError() { return kalman_.estimate_error; }
		std::vector<double>& MeasurementNoise() { return kalman_.measurement_noise; }

		// Nodes Config
		std::vector<Node> GetNodes() { return nodes_.nodes; }
		Node GetNode(unsigned int index = 0) { return nodes_[index]; }
		unsigned int NodeCount() { return nodes_.Size(); }


	protected:
		SignalerConfig signaler_;
		ICEConfig ice_;
		KalmanConfig kalman_;
		NodesConfig nodes_;
	};
}

#endif
