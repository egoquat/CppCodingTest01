#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

using namespace std;

void GetCombsR(vector<bool> visits, int depth, vector<string>& combs) {
	if (depth >= visits.size()) {
		string combination;
		for (int j = 0; j < visits.size(); ++j) {
			combination += visits[j] == true ? '1' : '0';
		}
		combs.push_back(combination);
		return;
	}

	visits[depth] = true;
	GetCombsR(visits, depth + 1, combs);
	visits[depth] = false;
	GetCombsR(visits, depth + 1, combs);
}

void GetCombs(int n, vector<string>& combs) {
	vector<bool> visits(n, false);
	GetCombsR(visits, 0, combs);
}

int solution(vector<int> numbers, int target) {
	unordered_map<char, int> operates = { make_pair('0', 1), make_pair('1', -1) };
	vector<string> combs;
	GetCombs(numbers.size(), combs);
	int answer = 0;
	vector<int> numbs(combs.size());
	for (int i = 0; i < combs.size(); ++i) {
		string& operate = combs[i];
		int num = 0;
		for (int j = 0; j < operate.length(); ++j) {
			num = num + (numbers[j] * operates[operate[j]]);
		}
		numbs[i] = num;
		if (num == target) answer++;
	}
	return answer;
}
