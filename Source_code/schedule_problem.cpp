#include "graph_data.h"
#include "Schedule_problem.h"
#include <algorithm>
#include <windows.h>

using namespace wjg_problem;
using namespace wjg_graph;

Schedule_problem::Schedule_problem(const vector<pair<int, int>>& intervals, const vector<int>& costs) {
	if (costs.size() != intervals.size())
		throw("Size of cost must equal to size of intervals!\n");
	for (auto interval : intervals) {
		if (interval.first >= interval.second)
			throw("The start of a period must be smaller than the end!\n");
		if (interval.first < 0 || interval.first >= 23 || interval.second <= 0 || interval.second > 23)
			throw("Time must range from 0 to 23!\n");
	}
	for (auto cost : costs) {
		if(cost < 0)
			throw("The cost cannot be negative in schedule problem!\n");
	}
	this->intervals = intervals;
	this->costs = costs;
}

vector<pair<int, int>> Schedule_problem::getIntervals() const {
	return this->intervals;
}

vector<int> Schedule_problem::getCosts() const {
	return this->costs;
} 

bool Schedule_problem::insertInterval(const pair<int, int>& interval, const int& cost) {
	if (interval.first >= interval.second)
		return false;
	if (interval.first < 0 || interval.first >= 23 || interval.second <= 0 || interval.second > 23)
		return false;
	if (cost < 0)
		return false;

	this->intervals.push_back(interval);
	this->costs.push_back(cost);
	return true;
}

Graph Schedule_problem::formulateGraph() {
	Graph gra = Graph();
	vector<int> times;
	for (unsigned int i = 0; i < this->costs.size(); i++) {
		if (gra.insertVex(intervals[i].first))
			times.push_back(intervals[i].first);
		if (gra.insertVex(intervals[i].second))
			times.push_back(intervals[i].second);
		gra.insertArc(intervals[i].first, intervals[i].second, costs[i]);
	}
	sort(times.begin(), times.end());
	for (int i = times.size() - 1; i > 0; i--) {
		gra.insertArc(times[i], times[i - 1], 0);
	}
	return gra;
}

pair<int, vector<int>> Schedule_problem::resolveProblem() {
	int start = 25, destination = -1;
	for (unsigned int i = 0; i < this->intervals.size(); i++) {
		start = min(start, intervals[i].first);
		destination = max(destination, intervals[i].second);
	}
	return formulateGraph().Dij(start, destination);
}