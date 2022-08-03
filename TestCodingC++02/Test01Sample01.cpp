#include <string>
#include <vector>
#include <map>
#include <functional>
#include <algorithm>
#include <iostream>

using namespace std;

struct Func {
	char A, B;
	char Eq;
	int diff;
	function<bool(int, int, int)> Con;
	bool Check(string& names) {
		int pA = names.find(A);
		int pB = names.find(B);
		return Con(pA, pB, diff);
	}
	Func() {}
	Func(string& eq) {
		A = eq[0]; B = eq[2]; Eq = eq[3]; diff = eq[4] - '0' + 1;
		cout << " new Func:" << A << Eq << B << diff << endl;
	}
};

char Chs[8] = { 'A', 'C', 'F', 'J', 'M', 'N', 'R', 'T' };
string Names(8, ' ');
bool visits[8] = { false };
vector<Func> Checks;
void dfs(int depth, int& count, const vector<string>& conds) {
	if (depth == 8) {
		//cout << " dfs 8 check:" << Names << endl;
		for (int i = 0; i < conds.size(); ++i) {
			const string& cond = conds[i];
			const char a = cond[0];
			const char b = cond[2];
			const char c = cond[3];
			const int diff = cond[4] - '0' + 1;
			int ia = Names.find(a);
			int ib = Names.find(b);
			switch (c) {
			case '=':
				if (abs(ia - ib) != 1) return;
				break;
			case '>':
				if ((abs(ia - ib) > diff) != true) return;
				break;
			case '<':
				if ((abs(ia - ib) < diff) != true) return;
				break;
			}
		}
		//cout << Names << endl;
		count++;
	}
	else {
		for (int i = 0; i < 8; ++i) {
			if (visits[i] == false) {
				visits[i] = true;
				Names[depth] = Chs[i];
				dfs(depth + 1, count, conds);
				visits[i] = false;
			}
		}
	}
}

int solution(int n, vector<string> data) {
	map<char, function<bool(int, int, int)>> Conditions = {
		{'>', [](int a, int b, int diff) {
			return abs(a - b) > diff;
		}},
		{'<', [](int a, int b, int diff) {
			return abs(a - b) < diff;
		}},
		{'=', [](int a, int b, int diff) {
			return abs(a - b) == 1;
		}}
	};
	Checks.resize(data.size());
	for (int i = 0; i < data.size(); ++i) {
		Checks[i] = Func(data[i]);
		Checks[i].Con = Conditions[Checks[i].Eq];
	}

	int answer = 0;
	dfs(0, answer, data);
	return answer;
}

int main() {
	int n = 2;
	vector<string> data = { "N~F=0", "R~T>2" };
	int answer = solution(n, data);
	return 0;
}