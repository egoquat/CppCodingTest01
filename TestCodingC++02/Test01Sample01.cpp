#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include <iomanip>
#include <sstream>
#include <functional>
#include <map>
#include <fstream>

using namespace std;

static const int IDXNONE = -1;
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
int ToCom(int x, int y) { return x << 8 | y; }
pair<int, int> ToXY(int com) {
	pair<int, int> v(com >> 8, com & 0xff);
	return v;
}

enum class EType { None = 0, Block, Gold, Goal };
struct Node {
	EType Type = EType::None;
	int Idx = IDXNONE;
	int X = -1, Y = -1;
	vector<int> Adjs;
	int ToXY() { return ToCom(X, Y); }
	Node(int idx, EType type, int x, int y) { Idx = idx; Type = type; X = x; Y = y; }
	void AddAdj(int adj) { AddSafe(Adjs, adj); }
};
void AddNode(vector<Node>& ns, map<int, int>& nsm, EType t, int x, int y) {
	ns.push_back(Node(ns.size(), t, x, y));
	Node* last = &ns[ns.size() - 1];
	int com = last->ToXY();
	nsm[com] = ns.size() - 1;
}
void AddAdj(vector<Node>& ns, map<int, int>& nsm, int x, int y) {
	int k = ToCom(x, y);
	Node& n = ns[Get(nsm, k, IDXNONE)];
	vector<int> adjs(4);
	adjs[0] = Get(nsm, ToCom(x + 1, y), IDXNONE);
	adjs[1] = Get(nsm, ToCom(x, y + 1), IDXNONE);
	adjs[2] = Get(nsm, ToCom(x - 1, y), IDXNONE);
	adjs[3] = Get(nsm, ToCom(x, y - 1), IDXNONE);
	for (int i = 0; i < 4; ++i) {
		int adj = adjs[i];
		if (adj == IDXNONE) continue;
		n.AddAdj(adj);
		ns[adj].AddAdj(n.Idx);
	}
}
void BfsRec(vector<Node>& ns, vector<int> frs, map<int, bool>& visits, int& depth, bool skipGoal, function<bool(Node&)> call) {
	vector<int> frsNext;
	for (int i = 0; i < frs.size(); ++i) {
		int idx = frs[i];
		visits[idx] = true;
		Node& f = ns[idx];
		bool isBreak = call(f);
		if (isBreak == true) return;
		for (int j = 0; j < f.Adjs.size(); ++j) {
			int idxAdj = f.Adjs[j];
			if (visits[idxAdj] == true) continue;
			if (skipGoal == true && ns[idxAdj].Type == EType::Goal) continue;
			AddSafe(frsNext, idxAdj);
		}
	}
	if (frsNext.size() <= 0) return;
	depth++;
	BfsRec(ns, frsNext, visits, depth, skipGoal, call);
}

int minMoves(vector<vector<int>> maze, int x, int y) {
	vector<Node> ns;
	map<int, int> nsm;
	for (int i = 0; i < maze.size(); ++i) {
		vector<int>& row = maze[i];
		for (int j = 0; j < row.size(); ++j) {
			EType type = (EType)row[j];
			if (type == EType::Block) continue;
			AddNode(ns, nsm, type, i, j);
			AddAdj(ns, nsm, i, j);
		}
	}
	ns[nsm[ToCom(x, y)]].Type = EType::Goal;

	vector<int> golds, frs{ 0 };
	map<int, bool> visits; bool foundGoal = false; int depth = 0;
	BfsRec(ns, frs, visits, depth, false, [&](Node& n)
		{
			if (n.Type == EType::Gold) { AddSafe(golds, n.Idx); }
			if (n.Type == EType::Goal) { foundGoal = true; }
			return false;
		});
	if (false == foundGoal) {
		return -1;
	}

	vector<int> gds = golds;
	int pos = 0;
	int move = 0;
	while (gds.size() >= 1) {
		visits.clear(); frs.clear(); frs.push_back(pos); depth = 0;
		BfsRec(ns, frs, visits, depth, true, [&](Node& n)
			{
				if (n.Type == EType::Gold && Contains(gds, n.Idx)) {
					Remove(gds, n.Idx); pos = n.Idx;
					return true;
				}
				return false;
			});
		move += depth;
	}

	int minmove = move;
	return minmove;
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

    string maze_rows_temp;
    getline(cin, maze_rows_temp);

    int maze_rows = stoi(ltrim(rtrim(maze_rows_temp)));

    string maze_columns_temp;
    getline(cin, maze_columns_temp);

    int maze_columns = stoi(ltrim(rtrim(maze_columns_temp)));

    vector<vector<int>> maze(maze_rows);

    for (int i = 0; i < maze_rows; i++) {
        maze[i].resize(maze_columns);

        string maze_row_temp_temp;
        getline(cin, maze_row_temp_temp);

        vector<string> maze_row_temp = split(rtrim(maze_row_temp_temp));

        for (int j = 0; j < maze_columns; j++) {
            int maze_row_item = stoi(maze_row_temp[j]);

            maze[i][j] = maze_row_item;
        }
    }

    string x_temp;
    getline(cin, x_temp);

    int x = stoi(ltrim(rtrim(x_temp)));

    string y_temp;
    getline(cin, y_temp);

    int y = stoi(ltrim(rtrim(y_temp)));

    int result = minMoves(maze, x, y);

    cout << result << "\n";

    //cout.close();

    return 0;
}
