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
		std::string name = "";

		Node(unsigned int id, unsigned int parent, std::string name) : id(id), parent(parent), name(name) {}
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
				const auto name = toml::find<std::string>(nodeTable, "name");
				const auto parent = toml::find<unsigned int>(nodeTable, "parent");
				nodes[id] = Node(id, parent, name);
			}
		}

		Node& operator[](unsigned int index) {
			return nodes[index];
		}

		unsigned int Size() { return nodes.size(); }
	};
}

#endif
