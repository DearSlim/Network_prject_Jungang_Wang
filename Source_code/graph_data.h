#include <vector>
#include <iostream>
#include <vector>
#include <unordered_map>
 
namespace wjg_graph {

	using std::vector;
	using std::unordered_map;
	using std::pair;

	// Class representing a node.
	// Each node contains 2 parts: a user defined unique key value (Only for mark) and an adjacency list.
	class GraphNode {
	public:
		GraphNode();
		GraphNode(const int& input);
		int getKey() const;
		vector<pair<GraphNode, int>> getAdj() const;
		bool insertAdj(const GraphNode& destination, const int& weight);
	private:
		int key;
		vector<pair<GraphNode, int>> adj;
	};

	// Class representing a graph. the class contains a hash map with every node's key stored for quickly finding specific node.
	class Graph {
	public:
		Graph();
		Graph(const GraphNode& node);
		Graph(const vector<GraphNode>& nodes);
		unordered_map<int, GraphNode> getList() const;
		bool existVex(const int& key) const;
		bool insertVex(const GraphNode& node);
		bool insertVex(const int& key);
		bool insertArc(const GraphNode& start, const GraphNode& destination, const int& weight);
		bool insertArc(const int& start, const int& destination, const int& weight);
		pair<int, vector<int>> Dij(const int& start, const int& destination);
	private:
		unordered_map<int, GraphNode> nodelist;
	};

}
