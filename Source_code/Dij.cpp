#include "graph_data.h"
#include "Schedule_problem.h"
#include <queue>

using namespace wjg_graph;
using namespace wjg_problem;
using std::priority_queue;


// Dij algorithm.
// Input data are key values of start and destination nodes
// return value: first is min cost, second is route (represented by key value of nodes)
pair<int, vector<int>> Graph::Dij(const int& start, const int& destination) {
	//For priority queue comparison
	struct cmp {
		bool operator () (const vector<int>& a, const vector<int>& b) {
			return a[2] > b[2];
		}
	}; 

	unordered_map<int, GraphNode>& nodelist = this->nodelist;
	if (nodelist.find(start) == nodelist.end() || nodelist.find(destination) == nodelist.end())
		throw("Vs or Vt doesn't exist in graph!\n");
	//Each element in queue represents an arc expressed by 3 data. 1st: start. 2nd: destination. 3rd: weight
	priority_queue<vector<int>, vector<vector<int>>, cmp> que;
	//Key: key value of a node; Value: min cost of the node
	unordered_map<int, int> ans_cost;
	//Key: key value of a node; Value: key value of its pred
	unordered_map<int, int> ans_pred;

	//Initialization
	for (auto p : nodelist) {
		ans_cost[p.first] = INT_MAX;
	}
	ans_cost[start] = 0;
	vector<pair<GraphNode,int>> adjList = nodelist[start].getAdj();
	for (unsigned int i = 0; i < adjList.size(); i++) {
		vector<int> temp = { start, adjList[i].first.getKey(), adjList[i].second };
		que.push(temp);
	}

	//Start labeling
	while (!que.empty() && ans_cost[destination] == INT_MAX) {
		while (!que.empty() && ans_cost[que.top()[1]] != INT_MAX) {
			que.pop();
		}
		if (que.empty()) break;
		auto selection = que.top();
		que.pop();
		ans_cost[selection[1]] = ans_cost[selection[0]] + selection[2];
		ans_pred[selection[1]] = selection[0];

		adjList = nodelist[selection[1]].getAdj();
		for (unsigned int i = 0; i < adjList.size(); i++) {
			vector<int> temp = { selection[1], adjList[i].first.getKey(), adjList[i].second };
			que.push(temp);
		}
	}

	//Process results
	if (ans_cost[destination] == INT_MAX) {
		return make_pair(INT_MAX, vector<int>(1, 0));
	}
	vector<int> route;
	int key = destination;
	while (key != start) {
		route.push_back(key);
		key = ans_pred[key];
	}
	route.push_back(start);
	std::reverse(route.begin(), route.end());
	return make_pair(ans_cost[destination], route);
}

