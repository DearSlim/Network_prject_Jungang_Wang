#include "graph_data.h"

using namespace wjg_graph;

GraphNode::GraphNode() {
	this->key = INT_MIN;
}
 
GraphNode::GraphNode(const int& input) {
	this->key = input;
}

int GraphNode::getKey() const {
	return this->key;
}

vector<pair<GraphNode, int>> GraphNode::getAdj() const {
	return this->adj;
}

bool GraphNode::insertAdj(const GraphNode& destination, const int& weight) {
	this->adj.push_back(std::make_pair(destination, weight));
	return true;
}


Graph::Graph() {
	unordered_map<int, GraphNode> nodelist = unordered_map<int, GraphNode>();
	this->nodelist = nodelist;
}

Graph::Graph(const GraphNode& node) {
	this->nodelist[node.getKey()] = node;
}

Graph::Graph(const vector<GraphNode>& nodes) {
	for (auto node : nodes) {
		this->nodelist[node.getKey()] = node;
	}
}

unordered_map<int, GraphNode> Graph::getList() const {
	return this->nodelist;
}

bool Graph::insertVex(const GraphNode& node) {
	if (this->nodelist.find(node.getKey()) == this->nodelist.end()) {
		this->nodelist[node.getKey()] = node;
		return true;
	}
	else
		return false;
}

bool Graph::insertVex(const int& key) {
	if (this->nodelist.find(key) == this->nodelist.end()) {
		GraphNode node = GraphNode(key);
		this->nodelist[node.getKey()] = node;
		return true;
	}
	else
		return false;
}

bool Graph::existVex(const int& key) const {
	return this->nodelist.find(key) != this->nodelist.end();
}

bool Graph::insertArc(const GraphNode& start, const GraphNode& destination, const int& weight) {
	if (this->nodelist.find(start.getKey()) == this->nodelist.end() || this->nodelist.find(destination.getKey()) == this->nodelist.end() || weight < 0)
		return false;
	nodelist[start.getKey()].insertAdj(nodelist[destination.getKey()], weight);
	return true;
}

bool Graph::insertArc(const int& start, const int& destination, const int& weight) {
	if (this->nodelist.find(start) == this->nodelist.end() || this->nodelist.find(destination) == this->nodelist.end() || weight < 0)
		return false;
	nodelist[start].insertAdj(nodelist[destination], weight);
	return true;
}