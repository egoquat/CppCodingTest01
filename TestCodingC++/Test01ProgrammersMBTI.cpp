#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <algorithm>

using namespace std;

string solution(vector<string> surveys, vector<int> choices) {
	map<char, int> cnts;
	cnts['R'] = cnts['T'] = cnts['C'] = cnts['F'] = cnts['J'] = cnts['M'] = cnts['A'] = cnts['N'] = 0;
	for (int i = 0; i < surveys.size(); ++i) {
		string& sur = surveys[i];
		char c0 = sur[0];
		char c1 = sur[1];
		int ch = choices[i];
		int chn0, chn1; chn0 = chn1 = 0;
		if (ch <= 3) chn0 = 3 - ch + 1;
		else if (ch >= 5) chn1 = ch - 4;
		cnts[c0] += chn0; cnts[c1] += chn1;
		//cout << "0:" << c0 << chn0 << "/1:" << c1 << chn1 << endl;
	}
	string ans = "";
	vector<string> posts = { "RT", "CF", "JM", "AN" };
	for (int i = 0; i < posts.size(); ++i) {
		string& p = posts[i];
		char c0 = p[0], c1 = p[1];
		char c;
		int n0 = cnts[c0], n1 = cnts[c1];
		if (n0 == n1) { c = c0; }
		else {
			if (n0 > n1) { c = c0; }
			else { c = c1; }
		}
		//cout << "p:" << p << "/" << c << "/c0:" << c0 << n0 << ",c1:" << c1 << n1 << endl;
		ans += c;
	}
	return ans;
}
