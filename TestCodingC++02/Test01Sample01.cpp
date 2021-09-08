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
