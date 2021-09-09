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

typedef unordered_map<int, bool> umap;
static const int NONE = -1;

struct Node {
	int X = NONE, Y = NONE;
	int Rsc = NONE;
	vector<int> Adjs;
	void Set(int x, int y, int rsc) { X = x; Y = y; Rsc = rsc; }
	void AddAdj(int adj) { AddSafe(Adjs, adj); }
	static vector<Node> Ns;
};
vector<Node> Node::Ns;
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
int GetMaxRscs(vector<vector<int>>& grid, int lim) {
	int w = grid[0].size(), h = grid.size();
	Node::Ns.resize(w * h);
	for (int i = 0; i < grid.size(); ++i) {
		for (int j = 0; j < grid[i].size(); ++j) {
			int rsc = grid[i][j];
			Node& node = Node::Ns[j + (i * grid.size())];
			node.Set(j, i, rsc);
		}
	}
	function<int(int, int)> getxy = [&](int x, int y) {
		if (x <= -1 || x >= w) return NONE; if (y <= -1 || y >= h) return NONE;
		return x + (y * h);
	};
	int checks[4];
	for (int i = 0; i < Node::Ns.size(); ++i) {
		int x = i % w, y = i / h;
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
	int rmax = 0, d = 0, r = 0; const int dlim = lim;
	for (int i = 0; i < Node::Ns.size(); ++i) {
		umap vs; d = r = 0;
		DfsRec(i, vs, dlim, d, r, rmax);
	}
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