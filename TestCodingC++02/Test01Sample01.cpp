#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <string>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <functional>

using namespace std;

typedef unordered_map<int, bool> umap;
static const int NONE = -1;
template<typename T> static T Last(vector<T>& v, T d)
{
	if (v.size() <= 0) return d;
	return v[v.size()-1];
}
template<typename T> static bool Remove(vector<T>& v, const T t)
{
	auto it = std::find(v.begin(), v.end(), t);
	if (it != v.end()) {
		std::swap(*it, v.back());
		v.pop_back();
		return true;
	}
	return false;
}
template<typename T> static bool AddSafe(vector<T>& v, const T t) {
	if (v.size() <= 0) {
		v.push_back(t); return true;
	}
	typedef typename vector<T>::iterator iter_v;
	iter_v iter = std::find(v.begin(), v.end(), t);
	if (v.end() == iter) {
		v.push_back(t);
		return true;
	}
	return false;
}
template<typename T> static bool Contains(vector<T>& v, const T t)
{
	typedef typename vector<T>::iterator iter_v;
	iter_v iter = std::find(v.begin(), v.end(), t);
	return iter != v.end();
}
template<typename T, typename V> static V Get(map<T, V>& m, const T t, V d)
{
	typedef typename map<T, V>::iterator iter_v;
	iter_v iter = m.find(t);
	return iter == m.end() ? d : iter->second;
}
struct Node {
	static vector<int> NIs;
	static vector<int> NRscs;
	static int W; static int H;
};
vector<int> Node::NIs; vector<int> Node::NRscs; int Node::W; int Node::H;
int GetDistH(int a, int b) { int ha = a / Node::W, hb = b / Node::W; return std::abs(hb - ha); }
int GetDistW(int a, int b) { int wa = a % Node::W, wb = b % Node::W; return std::abs(wb - wa); }
int GetDist(int a, int b) { return GetDistH(a, b) + GetDistW(a, b); }
bool IsOut(vector<int>& sets, int lim, int pos) {
	for (int i = 0; i < sets.size(); ++i) {
		if (GetDist(sets[i], pos) >= lim) return true;
	}
	return false;
}
bool Linked2(const vector<int>& subset) {
	map<int, bool> visits;
	vector<int> iters { subset[0] };
	visits[iters[0]] = true;
	//TEST
	//if (subset[0] + subset[1] + subset[2]+ subset[3] == 26) {
	//	int k = 0;
	//}
	int pos = 0;
	for (int n = 0; n < subset.size(); ++n) {
		int s = iters.size();
		for (int i = pos; i < s; ++i)
		{
			int v = iters[i];
			for (int j = 0; j < subset.size(); ++j) {
				int sub = subset[j];
				if (visits[sub] == true) continue;
				if (GetDist(sub, v) <= 1) {
					iters.push_back(sub);
					visits[sub] = true;
				}
			}
		}
		if (iters.size() == s) break;
		pos = s;
	}

	return iters.size() == subset.size();
}
void GetSubsetsRec(const vector<int>& ns, const int lim, int idx, vector<int>& sets, vector<vector<int>>& sets_o) {
	if (sets.size() == lim) {
		if (Linked2(sets) == false) return;
		sets_o.push_back(sets);
		//TEST
		//cout << ">" << sets_o.size() <<"\t"; for (int i = 0; i < lim; ++i) { cout << sets[i] << " "; } cout << '\n';
		return; 
	}
	for (int i = idx; i < ns.size(); ++i) {
		if (sets.size() >= 1){
			int dh = GetDistH(Last(sets, NONE), i);
			if (dh >= 2) continue;
			if (IsOut(sets, lim, i) == true) continue;
		}
			
		sets.push_back(i);
		GetSubsetsRec(ns, lim, i + 1, sets, sets_o);
		sets.pop_back();
	}
}
void GetSubsets(const vector<int>& ns, const int lim, vector<vector<int>>& sets_o) {
	int idx = 0;
	vector<int> sets;
	GetSubsetsRec(ns, lim, idx, sets, sets_o);
}
int GetMaxRscs(vector<vector<int>>& grid, int lim) {
	int w = grid[0].size(), h = grid.size();
	Node::W = w; Node::H = h;
	Node::NIs.resize(w * h); Node::NRscs.resize(w * h);
	for (int i = 0; i < grid.size(); ++i) {
		for (int j = 0; j < grid[i].size(); ++j) {
			int rsc = grid[i][j], idx = j + (i * grid[i].size());
			Node::NIs[idx] = idx;
			Node::NRscs[idx] = rsc;
		}
	}

	int rmax = 0;
	vector<vector<int>> subsets;
	GetSubsets(Node::NIs, lim, subsets);
	for (int i = 0; i < subsets.size(); ++i){
		vector<int>& sets = subsets[i];
		int rsc = 0;
		for (int j = 0; j < sets.size(); ++j){
			rsc += Node::NRscs[sets[j]];
		}
		rmax = std::max(rmax, rsc);
	}

	//cin >> rmax; //TEST
	return rmax;
}


string ltrim(const string& str) {
	string s(str);

	s.erase(
		s.begin(),
		find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace)))
	);

	return s;
}

string rtrim(const string& str) {
	string s(str);

	s.erase(
		find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
		s.end()
	);

	return s;
}

vector<string> split(const string& str) {
	vector<string> tokens;

	string::size_type start = 0;
	string::size_type end = 0;

	while ((end = str.find(" ", start)) != string::npos) {
		tokens.push_back(str.substr(start, end - start));

		start = end + 1;
	}

	tokens.push_back(str.substr(start));

	return tokens;
}

int main()
{
	//ofstream fout(getenv("OUTPUT_PATH"));
	string read_temp;
	vector<string> reads_temp;

	getline(cin, read_temp);
	reads_temp = split(rtrim(read_temp));

	int mars_rsc_row = stoi(ltrim(rtrim(reads_temp[0])));
	int mars_rsc_col = stoi(ltrim(rtrim(reads_temp[1])));
	int mars_rwc_count = stoi(ltrim(rtrim(reads_temp[2])));

	vector<vector<int>> mars_rscs(mars_rsc_row);

	for (int i = 0; i < mars_rsc_row; i++) {
		reads_temp.clear();
		mars_rscs[i].resize(mars_rsc_col);

		getline(cin, read_temp);
		read_temp = ltrim(rtrim(read_temp));

		for (int j = 0; j < mars_rsc_col; j++) {
			int rsc_item = (char)read_temp[j] - '0';
			mars_rscs[i][j] = rsc_item;
		}
	}

	int result = GetMaxRscs(mars_rscs, mars_rwc_count);

	cout << result << "\n";

	//cout.close();

	return 0;
}