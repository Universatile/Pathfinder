//Pathfinder library, version 1.3
//Written by Arc676/Alessandro Vinciguerra <alesvinciguerra@gmail.com>
//Copyright (C) 2017-2018 Arc676/Alessandro Vinciguerra

//This program is free software: you can redistribute it and/or modify
//it under the terms of the GNU General Public License as published by
//the Free Software Foundation (version 3)

//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.

//You should have received a copy of the GNU General Public License
//along with this program.  If not, see <http://www.gnu.org/licenses/>.
//See README and LICENSE for more details

//Based on work by Matthew Chen
//Copyright (C) 2017 Matthew Chen

#include "pathfinder.h"

std::list<Node*> Pathfinder::dijkstra(Graph* graph, Node* start, Node* end) {
	std::map<std::string, Node*> nodes = graph->getNodes();
	Node* current = nodes[start->getName()];

	std::map<Node*, NodeInfo> nodeInfo;
	for (auto const& [nodeName, node] : nodes) {
		nodeInfo[node] = {false, -1, nullptr};
	}
	nodeInfo[start].distance = 0;
	nodeInfo[start].bestPath = start;

	while (true) {
		nodeInfo[current].locked = true;
		if (nodeInfo[end].locked) {
			break;
		}
		std::map<std::string, Edge*> adjacent = current->getAdjacentNodes();
		for (auto const& [nodeName, edge] : adjacent) {
			Node* nextNode = nodes[nodeName];
			float currentDistance = edge->getWeight() + nodeInfo[current].distance;
			if (nodeInfo[nextNode].distance < 0 ||
			    currentDistance < nodeInfo[nextNode].distance) {
				nodeInfo[nextNode].distance = currentDistance;
				nodeInfo[nextNode].bestPath = current;
			}
		}
		float lowestDistance = -1;
		for (auto const& [nodeName, node] : nodes) {
			if (!nodeInfo[node].locked && (lowestDistance < 0 || 
							(nodeInfo[node].distance > 0 && nodeInfo[node].distance < lowestDistance))) {
				lowestDistance = nodeInfo[node].distance;
				current = node;
			}
		}
	}

	std::list<Node*> path;
	path.push_front(current);
	while (current->getName() != start->getName()) {
		current = nodeInfo[current].bestPath;
		if (current == nullptr) {
			path.clear();
			break;
		}
		path.push_front(current);
	}
	return path;
}
