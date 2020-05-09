#include "graph_data.h"
#include "Schedule_problem.h"
#include <iostream>
#include <string>

using namespace wjg_graph;
using namespace wjg_problem;
using std::string;
using std::make_pair;
using std::cout;
using std::endl;
using std::cin;

// Similar to split() function in Python.
vector<string> split(string str, char dot) {
	int pre = 0;
	vector<string> re;
	for (int i = 0; i < str.size(); i++) {
		if (str[i] == dot) {
			re.push_back(str.substr(pre, i - pre));
			pre = i + 1;
		}
		// Neglect spacebar after any mark
		else if (dot != ' ' && i > 0 && str[i-1] == dot && str[i] == ' ') {
			pre = i + 1;
		}
	}
	if (pre != str.size()) {
		re.push_back(str.substr(pre));
	}
	return re;
}

void printSchedule(const pair<int, vector<int>>& answer) {
	if (answer.first == INT_MAX || answer.second[0] == -1) {
		cout << "Feasible schedule doesn't exist.\n";
		return;
	}
	cout << "Min cost of the problem is: " << answer.first << endl;
	const vector<int>& route = answer.second;
	cout << "Planned schedule with minimum cost: " << endl;
	for (unsigned int i = 1; i < route.size(); i++) {
		if (route[i] < route[i - 1]) continue;
		cout << route[i - 1] << ":00 " << "to " << route[i] << ":00 " << endl;
	}
}

// Avoid illegal user input
bool verifyInput(const vector<string>& input) {
	if (input.size() != 3) {   
		cout << "Input data must be of 3 elements, or did you use a wrong form of input?\n";
		return false;
	}
	for (auto elem : input) {
		for (auto c : elem) {
			if (c - '0' < 0 || c - '0' > 9) {
				cout << "Input data must be numbers!\n";
				return false;
			}
		}
	}
	int start = stoi(input[0]);
	int end = stoi(input[1]);
	int cost = stoi(input[2]);

	if (start >= end) {
		cout << "The start of a period must be smaller than the end!\n";
		return false;
	}
	if (start < 0 || start >= 23 || end <= 0 || end > 23) {
		cout << "Time must range from 0 to 23!\n";
		return false;
	}
	if (cost < 0) {
		cout << "Cost must not be negative!\n";
		return false;
	}
	return true;
}

// Get user input
void getInput(vector<pair<int, int>>& intervals_custom, vector<int>& costs_custom) {
	int start = 0, end = 0, cost = 0;
	string input = "";
	string a = "finish";
	while (true) {
		input = "";
		cin.clear();
		cin.sync();
		cout << "You can now type in data.\n";
		cout << "-------------------------------------\n";
		getline(cin, input);
		if (input == "finish") {
			if (!costs_custom.empty()) {
				break;
			}
			else {
				cout << "At least one driver must be added!\n";
				continue;
			}
		}
		vector<string> indata = split(input, ',');
		if (indata.size() != 3) indata = split(input, ' ');
		if (verifyInput(indata)) {
			int start = stoi(indata[0]);
			int end = stoi(indata[1]);
			int cost = stoi(indata[2]);
			intervals_custom.push_back(make_pair(start, end));
			costs_custom.push_back(cost);
			cout << "-------------------------------------\n";
			cout << "Input legal. Stored successfully.\n";
			cout << "Stored schedule: From " << start << ":00 to " << end << ":00, " << "with cost: " << cost << endl;
			cout << "----------------------------------------------------------------\n";
		}
	}
	return;
}

// Main entrance of the whole program
int main(void) {
	//Test data from textbook
	vector<pair<int, int>> intervals_textbook = { make_pair(9,13), make_pair(9,11), make_pair(12,15), 
		make_pair(12,17), make_pair(14,17), make_pair(13,16), make_pair(16,17) };
	vector<int> costs_textbook = { 30,18,21,38,20,22,9 };
	Schedule_problem textbook_problem = Schedule_problem(intervals_textbook, costs_textbook);
	pair<int, vector<int>> answer1 = textbook_problem.resolveProblem();
	printSchedule(answer1);

	cout << endl << endl << endl;
	cout << "You can now type in the start, end and cost of a driver's time period. \nE.g. \"10,12,9\"  means a period from 10:00 to 12:00 with cost of 9.\n";
	cout << "You can also use form like \"10 12 9\ or \"10, 12, 9\", but don't use form like \"10,12 9\"\n";
	cout << "Time range should be 0 to 23, cost shouldn't be extremely large.\n";
	cout << "You would get notice if any of the input data is illegal.\n\n";
	cout << "If you want to finish entering data and get answer, type \"finish\" and enter.\n\n";

	vector<pair<int, int>> intervals_custom;
	vector<int> costs_custom;

	getInput(intervals_custom, costs_custom);

	Schedule_problem custom_problem = Schedule_problem(intervals_custom, costs_custom);
	pair<int, vector<int>> answer3 = custom_problem.resolveProblem();
	printSchedule(answer3);
	cout << "Calculation finished, press any key to close the program.\n";
	system("pause");
	return 0;
} 