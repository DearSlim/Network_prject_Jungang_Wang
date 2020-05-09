using namespace wjg_graph;

namespace wjg_problem {
	// Extension for question 4.13 on book.
	// This class formulate the single-duty crew scheduling problem. 
	// The class contains necessary data and functions for solving the problem.
	// intervals: time intervals for each driver.
	// costs: cost for each of the drivers. The array is of the same size as intervals.
	class Schedule_problem {
	public:
		Schedule_problem(const vector<pair<int, int>>& intervals, const vector<int>& costs);
		vector<pair<int, int>> getIntervals() const;
		vector<int> getCosts() const;
		bool insertInterval(const pair<int, int>& interval, const int& cost);
		// Formulate the problem into a graph.
		// For this problem we would defaultly find the min cost program from earliest start time to latest end time.
		Graph formulateGraph();
		// Use graph to resolve the question.
		pair<int, vector<int>> resolveProblem();
	private:
		vector<pair<int, int>> intervals;
		vector<int> costs;
	};
} 