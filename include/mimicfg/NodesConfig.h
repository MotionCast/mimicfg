/** @file
 * @author Jacob SP <jacob@moca.st>
 */

#ifndef NODES_CFG_H
#define NODES_CFG_H

#include <vector>
#include <iostream>
#include <string>
#include <toml.hpp>

namespace mocast {

	/**
	 * @brief Contains data to setup a single node
	 */
	struct Node {
		unsigned int id = 0;
		unsigned int parent = 0;
		std::string serial = "";
		std::string name = "";

		Node(unsigned int id, unsigned int parent, std::string serial, std::string name) :
			id(id), parent(parent), serial(serial), name(name) {}
		Node() {}
	};

	/**
	 * @brief TOML conversion of nodes
	 */
	struct NodesConfig {
		std::vector<Node> nodes = {};

		NodesConfig() {}

		NodesConfig(std::vector<toml::table> v) {
			nodes.resize(v.size());

			for (toml::value nodeTable : v)
			{
				const auto id = toml::find<unsigned int>(nodeTable, "id");
				const auto parent = toml::find<unsigned int>(nodeTable, "parent");
				const auto serial = toml::find<std::string>(nodeTable, "serial");
				const auto name = toml::find<std::string>(nodeTable, "name");
				nodes[id] = Node(id, parent, serial, name);
			}
		}

		Node& operator[](unsigned int index) {
			return nodes[index];
		}

		unsigned int Size() { return nodes.size(); }
	};
}

#endif
