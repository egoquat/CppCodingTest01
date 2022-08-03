#include <string>
#include <cstdio>
#include <vector>
#include <map>

using namespace std;

char candidate[8];
int visit[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
int answer;
void dfs(int n, int depth, const string& str, const vector<string>& data)
{
	if (n == depth) {
		map<char, int> candidate_map;
		for (int i = 0; i < depth; i++)
			candidate_map[candidate[i]] = i;

		for (int i = 0; i < data.size(); i++) {
			char from = data[i][0];
			char to = data[i][2];
			char op = data[i][3];
			int dist = 1 + data[i][4] - '0';
			int f = candidate_map[data[i][0]];
			int t = candidate_map[data[i][2]];
			if (op == '=') {
				if (abs(f - t) != dist)
					return;
			}
			else if (op == '<') {
				if (abs(f - t) >= dist)
					return;
			}
			else {
				if (abs(f - t) <= dist)
					return;
			}
		}
		answer++;
		return;
	}

	for (int i = 0; i < 8; i++) {
		if (visit[i] == 1)
			continue;
		visit[i] = 1;
		candidate[depth] = str[i];
		dfs(n, depth + 1, str, data);
		visit[i] = 0;
	}
}
int solution(int n, vector<string> data) {
	answer = 0;
	string str = "ACFJMNRT";

	dfs(8, 0, str, data);

	return answer;
}