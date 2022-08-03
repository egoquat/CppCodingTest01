#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <iostream>

using namespace std;

vector<int> solution(int N, vector<int> stages) {
	unordered_map<int, int> stays;
	unordered_map<int, int> tries;
	vector<int> ss;
	sort(stages.begin(), stages.end(), less<int>());
	int laststage = -1;
	for (int i = 0; i < stages.size(); ++i) {
		int s = stages[i];
		if (s > N && tries.find(N) == tries.end()) {
			tries[N] = stages.size() - i;
			ss.push_back(N);
			cout << " stageN(" << N << "):" << tries[N] << endl;
			break;
		}
		if (laststage != s) {
			tries[s] = stages.size() - i;
			laststage = s;
			ss.push_back(s);
			cout << " stage(" << s << "):" << tries[s] << endl;
		}
		stays[s]++;
	}

	if (tries.find(N) == tries.end()) {
		tries[N] = 0; stays[N] = 0; ss.push_back(N);
		cout << " stageL:" << tries[N] << endl;
	}

	vector<int> sr; vector<float> srr;
	sr.resize(N); srr.resize(N);
	float rate = 0.0f; int cntremain = stages.size();
	for (int s = 1; s <= N; ++s) {
		sr[s - 1] = s;
		unordered_map<int, int>::iterator itert = tries.find(s);
		if (itert == tries.end()) {
			rate = 0;
			cout << " rates2(" << s << "):" << rate << endl;
		}
		else {
			int cnttry = itert->second;
			int cntstay = stays[s];
			if (cnttry == 0)
				rate = 0;
			else
				rate = (float)cntstay / (float)cnttry;
			cntremain -= cntstay;
			cout << " rates1(" << s << "):" << rate << endl;
		}

		srr[s - 1] = rate;
	}
	sort(sr.begin(), sr.end(), [&](int a, int b) {
		float ar = srr[a - 1];
		float br = srr[b - 1];
		if (ar == br) {
			return a < b;
		}
		return ar > br;
		});

	//
	cout << " answer [";
	for (int i = 0; i < sr.size(); ++i) {
		cout << " " << sr[i];
	}
	cout << " ]" << endl;
	//
	return sr;
}