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
	int X = NONE, Y = NONE, Idx = NONE;
	int Rsc = NONE;
	vector<int> Adjs;
	void Set(int idx, int x, int y, int rsc) { Idx = idx; X = x; Y = y; Rsc = rsc; }
	void AddAdj(int adj) { AddSafe(Adjs, adj); }
	static vector<Node> Ns; static vector<int> NIs;
	static int W; static int H;
};
vector<Node> Node::Ns; vector<int> Node::NIs; int Node::W; int Node::H;
void DfsRec(int no, umap& vs, int dlim, int d, int r, int& rmax) {
	Node& n = Node::Ns[no];
	r = r + n.Rsc; vs[no] = true;
	d++;
	if (d >= dlim) { rmax = std::max(rmax, r); vs[no] = false; return; }
	for (int i = 0; i < n.Adjs.size(); ++i) {
		int adj = n.Adjs[i];
		if (vs[adj] == true) continue;
		DfsRec(adj, vs, dlim, d, r, rmax);
	}
	vs[no] = false;
}
bool Linked(const vector<int>& subset){
	map<int, bool> contains; for (int i = 0; i < subset.size(); ++i) { contains[subset[i]] = true; }
	map<int, bool> visits;
	vector<int> ids { subset[0] };
	int pos = 0;
	for (int t = 0; t < subset.size() - 1; ++t){
		int cnt = ids.size();
		for (int i = pos; i < cnt; ++i){
			Node& n = Node::Ns[ids[i]];
			visits[ids[i]] = true;
			for (int j = 0; j < n.Adjs.size(); ++j){
				int iA = n.Adjs[j];
				if (visits[iA] == true || contains[iA] == false) continue;
				AddSafe(ids, iA);
			}
		}
		if (ids.size() == cnt) return false;
		if (ids.size() == subset.size()) return true;
		pos = cnt;
	}
	return true;
}
int GetDistH(int a, int b) { int ha = a / Node::W, hb = b / Node::W; return std::abs(hb - ha); }
int GetDistW(int a, int b) { int wa = a % Node::W, wb = b % Node::W; return std::abs(wb - wa); }
int GetDist(int a, int b) { return GetDistH(a, b) + GetDistW(a, b); }
bool IsOut(vector<int>& sets, int lim, int pos) {
	for (int i = 0; i < sets.size(); ++i) {
		if (GetDist(sets[i], pos) >= lim) return true;
	}
	return false;
}
void GetSubsetsRec(const vector<int>& ns, const int lim, int idx, vector<int>& sets, vector<vector<int>>& sets_o) {
	if (sets.size() == lim) {
		if (Linked(sets) == false) return;
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
	Node::Ns.resize(w * h);	Node::NIs.resize(w * h);
	for (int i = 0; i < grid.size(); ++i) {
		for (int j = 0; j < grid[i].size(); ++j) {
			int rsc = grid[i][j], idx = j + (i * grid[i].size());
			Node& node = Node::Ns[idx];
			Node::NIs[idx] = idx;
			node.Set(idx, j, i, rsc);
		}
	}
	function<int(int, int)> getxy = [&](int x, int y) {
		if (x <= -1 || x >= w) return NONE; if (y <= -1 || y >= h) return NONE;
		return x + (y * w);
	};
	int checks[4];
	for (int i = 0; i < Node::Ns.size(); ++i) {
		int x = i % w, y = i / w;
		checks[0] = getxy(x + 1, y);
		checks[1] = getxy(x, y + 1);
		checks[2] = getxy(x - 1, y);
		checks[3] = getxy(x, y - 1);
		for (int j = 0; j < 4; ++j) {
			if (checks[j] == NONE) continue;
			Node::Ns[i].AddAdj(checks[j]);
			Node::Ns[checks[j]].AddAdj(i);
		}
	}
	int rmax = 0;
	//int d = 0, r = 0; const int dlim = lim;
	// for (int i = 0; i < Node::Ns.size(); ++i) {
	//     umap vs; d = r = 0;
	//     DfsRec(i, vs, dlim, d, r, rmax);
	// }
	vector<vector<int>> subsets;
	GetSubsets(Node::NIs, lim, subsets);
	for (int i = 0; i < subsets.size(); ++i){
		vector<int>& sets = subsets[i];
		int rsc = 0;
		for (int j = 0; j < sets.size(); ++j){
			rsc += Node::Ns[sets[j]].Rsc;
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