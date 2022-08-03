#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

int solution(vector<vector<int>> sizes) {
	int answer = 0;
	int maxw = 0, maxh = 0;
	for (int i = 0; i < sizes.size(); ++i) {
		int w = sizes[i][0];
		int h = sizes[i][1];
		int w2 = max(w, h), h2 = min(w, h);
		maxw = max(w2, maxw);
		maxh = max(h2, maxh);
	}
	return maxw * maxh;
}