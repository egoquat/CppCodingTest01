#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include <iomanip>
#include <sstream>

using namespace std;
namespace namespace01 {
	bool IsRepeat(string str, string& repeat, int& pos, int& len) {
		for (int i = 0; i < str.size() / 2 - 1; ++i) {
			for (int j = 1; j < str.size(); ++j) {
				string sub = str.substr(i, j);
				int r = 0, count = (str.size() - i) / sub.size(), rem = (str.size() - i) % sub.size();
				if (rem == 0) rem = sub.size();
				for (int k = 0; k < count; ++k) {
					int sizeSub = (k == (count - 1)) ? rem : sub.size();
					if (str.compare(i + (k * sub.size()), sizeSub, sub, 0, sizeSub) == 0) {
						r++;
					}
					else {
						break;
					}
				}
				if (r >= 2 && r >= count - 1) {
					repeat = sub; pos = i; len = sub.size();
					return true;
				}
			}
		}

		return false;
	}

	string Divide2(int num, int div, int precise = 20) {
		string output;
		int n = num, d = div, r = 0, v = 0;
		if (n < d) {
			output += "0.";
		}
		else {
			output += to_string((int)(n / d)) + ".";
			r = n % d;
			n = r;
		}
		int iter = 0;
		while (iter++ < precise) {
			n = n * 10;
			char append = '0';
			if (n >= d) {
				r = n % d;
				v = n / d;
				append = '0' + v;
				n = r;
			}
			output += append;
		}
		return output;
	}

	void reciprocal(int N) {
		string output2 = Divide2(1, N, 100);

		int dot = 1;
		string fstr = output2.substr(2, output2.size() - 1);
		string rstr;
		int rpos = 0, rlen = 0;
		bool isRepeat = IsRepeat(fstr, rstr, rpos, rlen);

		printf("%d// %d // %s // %s\n", N, isRepeat, output2.c_str(), rstr.c_str());

		//string result;
		//if (isRepeat) {
		//	result = output2.substr(0, rpos + 2 + rlen);
		//	printf("%s %s\n", result.c_str(), rstr.c_str());
		//}
		//else {
		//	result = output2;
		//	printf("%s", result.c_str());
		//}
	}

	int main() {
		//int n = 0;
		//scanf("%d", &n);
		//reciprocal(n);
		for (int i = 1; i < 100; ++i) {
			reciprocal(i);
		}

		int n = 0;
		scanf("%d", &n);
		return 0;
	}
}



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

namespace namespace02 {
	struct City {
		string Name;
		int Idx = -1;
		int Pos[2];
		City* Adj[2]{ nullptr };
		City* GetNearst() {
			City* adjX = Adj[0]; City* adjY = Adj[1];
			if (adjX == nullptr) return adjY;
			if (adjY != nullptr && GetDist(adjX, 0) > GetDist(adjY, 1)) return adjY;
			return adjX;
		}
		int GetDist(City* o, int dim) { return std::abs(Pos[dim] - o->Pos[dim]); }
		void SetAdj(City* adj, int dim) {
			if (Adj[dim] == nullptr || GetDist(Adj[dim], dim) > GetDist(adj, dim)) {
				Adj[dim] = adj;
			}
		}
		void Set(int idx, string& name, int x, int y) { Idx = idx; Name = name; Pos[0] = x; Pos[1] = y; }
	};

	vector<string> closestStraightCity(vector<string> cs, vector<int> xs, vector<int> ys, vector<string> qs) {
		vector<City> cities;
		map<string, City*> citiesMap;
		map<int, vector<int>> distsX;
		map<int, vector<int>> distsY;

		cities.resize(cs.size());
		for (int i = 0; i < cs.size(); ++i) {
			string& name = cs[i]; int x = xs[i]; int y = ys[i];
			cities[i].Set(i, name, x, y);
			citiesMap[name] = &cities[i];
			distsX[x].push_back(i);
			distsY[y].push_back(i);
		}

		int dim = 0;
		std::function<bool(int, int)> compare = [&](int a, int b) {
			City& ca = cities[a]; City& cb = cities[b];
			return ca.Pos[dim] < cb.Pos[dim];
		};

		map<int, vector<int>>* iterations[]{ &distsY, &distsX };
		for (int i = 0; i < 2; ++i) {
			map<int, vector<int>>::iterator iter = iterations[i]->begin();
			for (; iter != iterations[i]->end(); ++iter) {
				vector<int>& line = iter->second;
				if (line.size() <= 1) continue;
				dim = i;
				std::sort(line.begin(), line.end(), compare);
				for (int j = 0; j < line.size() - 1; ++j) {
					City& curr = cities[line[j]]; City& next = cities[line[j + 1]];
					curr.SetAdj(&next, dim); next.SetAdj(&curr, dim);
				}
			}
		}

		const string NONE = "NONE";
		vector<string> outputs(qs.size());
		map<int, vector<int>>::iterator iterX, iterY;
		map<string, City*>::iterator iterCity;
		for (int i = 0; i < qs.size(); ++i) {
			string output = NONE;
			string& q = qs[i];
			iterCity = citiesMap.find(q);
			if (iterCity != citiesMap.end()) {
				City& c = *citiesMap[q];
				City* adj = c.GetNearst();
				if (adj != nullptr) { output = adj->Name; }
			}

			outputs[i] = output;
		}
		return outputs;
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

	int main()
	{
		//ofstream fout(getenv("OUTPUT_PATH"));

		string c_count_temp;
		getline(cin, c_count_temp);

		int c_count = stoi(ltrim(rtrim(c_count_temp)));

		vector<string> c(c_count);

		for (int i = 0; i < c_count; i++) {
			string c_item;
			getline(cin, c_item);

			c[i] = c_item;
		}

		string x_count_temp;
		getline(cin, x_count_temp);

		int x_count = stoi(ltrim(rtrim(x_count_temp)));

		vector<int> x(x_count);

		for (int i = 0; i < x_count; i++) {
			string x_item_temp;
			getline(cin, x_item_temp);

			int x_item = stoi(ltrim(rtrim(x_item_temp)));

			x[i] = x_item;
		}

		string y_count_temp;
		getline(cin, y_count_temp);

		int y_count = stoi(ltrim(rtrim(y_count_temp)));

		vector<int> y(y_count);

		for (int i = 0; i < y_count; i++) {
			string y_item_temp;
			getline(cin, y_item_temp);

			int y_item = stoi(ltrim(rtrim(y_item_temp)));

			y[i] = y_item;
		}

		string q_count_temp;
		getline(cin, q_count_temp);

		int q_count = stoi(ltrim(rtrim(q_count_temp)));

		vector<string> q(q_count);

		for (int i = 0; i < q_count; i++) {
			string q_item;
			getline(cin, q_item);

			q[i] = q_item;
		}

		vector<string> result = closestStraightCity(c, x, y, q);

		for (int i = 0; i < result.size(); i++) {
			cout << result[i];

			if (i != result.size() - 1) {
				cout << "\n";
			}
		}

		cout << "\n";

		//cout.close();

		return 0;
	}
}


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

namespace namespace03 {
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
	int AddNode(vector<Node>& ns, map<int, int>& nsm, EType t, int x, int y) {
		ns.push_back(Node(ns.size(), t, x, y));
		int idxAdded = ns.size() - 1;
		Node* last = &ns[idxAdded];
		int com = last->ToXY();
		nsm[com] = ns.size() - 1;
		return idxAdded;
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
		vector<int> golds;
		int idxAdd = IDXNONE;
		for (int i = 0; i < maze.size(); ++i) {
			vector<int>& row = maze[i];
			for (int j = 0; j < row.size(); ++j) {
				EType type = (EType)row[j];

				if (type == EType::Block) continue;
				idxAdd = AddNode(ns, nsm, type, i, j);

				AddAdj(ns, nsm, i, j);
				if (type == EType::Gold) AddSafe(golds, idxAdd);
			}
		}
		ns[nsm[ToCom(x, y)]].Type = EType::Goal;

		vector<int> gdcs, frs{ 0 };
		map<int, bool> visits; bool foundGoal = false; int depth = 0;
		BfsRec(ns, frs, visits, depth, false, [&](Node& n)
			{
				if (n.Type == EType::Gold) { AddSafe(gdcs, n.Idx); }
				if (n.Type == EType::Goal) { foundGoal = true; }
				return false;
			});
		if (false == foundGoal || golds.size() != gdcs.size()) {
			return -1;
		}

		vector<int> gds = gdcs;
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

		visits.clear(); frs.clear(); frs.push_back(pos); depth = 0;
		BfsRec(ns, frs, visits, depth, false, [&](Node& n)
			{
				if (n.Type == EType::Goal) {
					return true;
				}
				return false;
			});
		move += depth;

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
}


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

namespace namespace04 {
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
	int AddNode(vector<Node>& ns, map<int, int>& nsm, EType t, int x, int y) {
		ns.push_back(Node(ns.size(), t, x, y));
		int idxAdded = ns.size() - 1;
		Node* last = &ns[idxAdded];
		int com = last->ToXY();
		nsm[com] = ns.size() - 1;
		return idxAdded;
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
		vector<int> golds;
		int idxAdd = IDXNONE;
		for (int i = 0; i < maze.size(); ++i) {
			vector<int>& row = maze[i];
			for (int j = 0; j < row.size(); ++j) {
				EType type = (EType)row[j];
				if (type == EType::Block) continue;
				idxAdd = AddNode(ns, nsm, type, i, j);
				AddAdj(ns, nsm, i, j);
				if (type == EType::Gold) AddSafe(golds, idxAdd);
			}
		}
		ns[nsm[ToCom(x, y)]].Type = EType::Goal;

		vector<int> gdcs, frs{ 0 };
		map<int, bool> visits; bool foundGoal = false; int depth = 0;
		BfsRec(ns, frs, visits, depth, false, [&](Node& n)
			{
				if (n.Type == EType::Gold) { AddSafe(gdcs, n.Idx); }
				if (n.Type == EType::Goal) { foundGoal = true; }
				return false;
			});
		if (false == foundGoal || golds.size() != gdcs.size()) {
			return -1;
		}

		vector<int> gds = gdcs;
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

		visits.clear(); frs.clear(); frs.push_back(pos); depth = 0;
		BfsRec(ns, frs, visits, depth, false, [&](Node& n)
			{
				if (n.Type == EType::Goal) {
					return true;
				}
				return false;
			});
		move += depth;

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
}
