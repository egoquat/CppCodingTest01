// 100%

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> solution(vector<vector<int> > v) {
	vector<vector<int>> counts(2);
	vector<vector<int>> mms(2);
	for (int i = 0; i < 2; ++i) { counts[i].resize(2); mms[i].resize(2); }
	mms[0][0] = mms[0][1] = 1 << 30;
	mms[1][0] = mms[1][1] = 0;
	for (int i = 0; i < 3; ++i) {
		mms[0][0] = min(v[i][0], mms[0][0]);
		mms[0][1] = min(v[i][1], mms[0][1]);
		mms[1][0] = max(v[i][0], mms[1][0]);
		mms[1][1] = max(v[i][1], mms[1][1]);
	}
	cout << "min:" << mms[0][0] << "/" << mms[0][1] << endl;
	cout << "max:" << mms[1][0] << "/" << mms[1][1] << endl;
	for (int i = 0; i < 3; ++i) {
		if (v[i][0] == mms[0][0]) counts[0][0]++;
		if (v[i][0] == mms[1][0]) counts[1][0]++;
		if (v[i][1] == mms[0][1]) counts[0][1]++;
		if (v[i][1] == mms[1][1]) counts[1][1]++;
	}
	cout << "min:" << counts[0][0] << "/" << counts[0][1] << endl;
	cout << "max:" << counts[1][0] << "/" << counts[1][1] << endl;
	vector<int> ans(2);
	ans[0] = counts[0][0] != 2 ? mms[0][0] : mms[1][0];
	ans[1] = counts[0][1] != 2 ? mms[0][1] : mms[1][1];
	return ans;
}