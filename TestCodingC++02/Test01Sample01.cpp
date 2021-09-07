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
	int Idx, Adj = -1;
	int Pos[2];
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

	const int NONE_IDX = -1;
	const int DEFAULT_CLOSEST = std::pow(10, 9) + 1;
	std::function<int(vector<int>*, int, int)> closestStraight = [&](vector<int>* dists, int idxFrom, int posIdxCurrent) {
		int idx = NONE_IDX;
		if (dists == nullptr) return idx;

		int closest = DEFAULT_CLOSEST;
		int posIdx = (posIdxCurrent + 1 % 2);
		int pos = cities[idxFrom].Pos[posIdx];
		for (int i = 0; i < (*dists).size(); ++i) {
			int iter = (*dists)[i];
			if (iter == idxFrom) continue;
			int dist = std::abs(pos - cities[iter].Pos[posIdx]);
			if (closest > dist){
				closest = dist; idx = iter;
			}
		}
		return closest;
	};

	const string NONE = "NONE";
	vector<string> outputs(qs.size());
	map<int, vector<int>>::iterator iterX, iterY;
	for (int i = 0; i < qs.size(); ++i) {
		string& q = qs[i];
		City& c = *citiesMap[q];
		iterX = distsX.find(c.Pos[0]);
		iterY = distsY.find(c.Pos[1]);
		vector<int>* dsX = iterX != distsX.end()? &(iterX->second) : nullptr;
		vector<int>* dsY = iterY != distsY.end()? &(iterY->second) : nullptr;
		int idx = NONE_IDX;
		idx = closestStraight(dsX, c.Idx, 0);
		if (idx == NONE_IDX){
			idx = closestStraight(dsY, c.Idx, 1);
		}

		string output = NONE;
		if (idx != NONE_IDX) output = cities[idx].Name;
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
	ofstream fout(getenv("OUTPUT_PATH"));

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
		fout << result[i];

		if (i != result.size() - 1) {
			fout << "\n";
		}
	}

	fout << "\n";

	fout.close();

	return 0;
}
