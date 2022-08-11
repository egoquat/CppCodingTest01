#include <string>
#include <functional>
#include <map>
#include <iostream>
#include <queue>

using namespace std;

bool isnum(char c) {
	return c >= '0' && c <= '9';
}

int solution(string darts) {
	map<char, function<int(int)>> Eqs = {
		{'S', [](int n) { return n; }},
		{'D', [](int n) { return n * n; }},
		{'T', [](int n) { return n * n * n; }},
		{'*', [](int n) { return n * 2; }},
		{'#', [](int n) { return n * -1; }},
	};
	int numunit = 0, cntsum = 0;
	vector<int> numunits; vector<bool> stars;
	bool isstar = false;
	for (int i = 0; i < darts.size(); ++i) {
		char c = darts[i];
		bool isnumeric = isnum(c);
		if (isnumeric == true) {
			numunit = (numunit * 10) + (darts[i] - '0');
			cout << " n:" << numunit;
		}
		else {
			numunit = Eqs[c](numunit);
			cout << " c:" << c << ",n:" << numunit;
			if (c == '*') {
				if (cntsum == 0) {
					numunit = Eqs[c](numunit);
				}
				else if (cntsum == 1) {
					if (stars[0] == false) {
						numunits[0] = Eqs[c](numunits[0]);
					}
				}
				else if (cntsum >= 2) {
					numunits[cntsum - 1] = Eqs[c](numunits[cntsum - 1]);
				}
				isstar = true;
			}
		}
		bool islast = ((isnumeric == false
			&& i + 1 <= darts.size() - 1
			&& isnum(darts[i + 1]) == true)
			|| i == darts.size() - 1);
		if (islast == true) {
			cout << " a:" << numunit << endl;
			numunits.push_back(numunit); numunit = 0; ++cntsum;
			stars.push_back(isstar);
		}
	}

	int ans = 0;
	for (int i = 0; i < numunits.size(); ++i) {
		int num = numunits[i];
		ans += num;
		cout << " r:" << num << "/rr:" << ans << endl;
	}
	return ans;
}

int main() {
	//string input = "1S*2T*3S";
	string input = "1S2D*3T*"; // 72
	int output = solution(input);
	return 0;
}