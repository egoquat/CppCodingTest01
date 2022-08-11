#include <string>
#include <vector>
#include <iostream>

using namespace std;

bool IsValid(vector<string>& ps, int xin, int yin) {
	for (int i = -1; i <= 1; ++i) {
		for (int j = -1; j <= 1; ++j) {
			int x = xin - i, y = yin - j;
			if (x == xin && y == yin || x == -1 || x >= 5 || y == -1 || y >= 5) continue;
			char c = ps[x][y];
			if (c != 'P') continue;
			if (x == xin || y == yin) return false;
			char c0 = ps[x][yin];
			char c1 = ps[xin][y];
			if (c0 != 'X' || c1 != 'X') return false;
		}
	}
	int d[2] = { -2, 2 };
	for (int i = 0; i < 2; ++i) {
		int x = xin + d[i], y = yin;
		if (x <= -1 || x >= 5) continue;
		char c = ps[x][y];
		if (c != 'P') continue;
		char c0 = ps[(x + xin) / 2][y];
		if (c0 != 'X') return false;\


	}
	for (int i = 0; i < 2; ++i) {
		int x = xin, y = yin + d[i];
		if (y <= -1 || y >= 5) continue;
		char c = ps[x][y];
		if (c != 'P') continue;
		char c0 = ps[x][(y + yin) / 2];
		if (c0 != 'X') return false;
	}
	return true;
}

vector<int> solution(vector<vector<string>> places) {
	bool isValid = true;
	vector<int> ans(5);
	for (int i = 0; i < 5; ++i) {
		isValid = true;
		vector<string>& ps = places[i];
		for (int j = 0; j < 5; ++j) {
			for (int k = 0; k < 5; ++k) {
				char c = ps[j][k];
				if (c != 'P') continue;
				isValid = IsValid(ps, j, k);
				if (isValid == false) break;
			}
			if (isValid == false) break;
		}
		ans[i] = (isValid == true) ? 1 : 0;
		cout << " i(" << i << "):" << ans[i];
	}
	cout << endl;
	return ans;
}

int main() {
	vector<vector<string>> data = { {"POOOP", "OXXOX", "OPXPX", "OOXOX", "POXXP"},
		{"POOPX", "OXPXP", "PXXXO", "OXXXO", "OOOPP"},
		{"PXOPX", "OXOXP", "OXPOX", "OXXOP", "PXPOX"},
		{"OOOXX", "XOOOX", "OOOXX", "OXOOX", "OOOOO"},
		{"PXPXP", "XPXPX", "PXPXP", "XPXPX", "PXPXP"}
	};

	vector<int> answer = solution(data);
	return 0;
}