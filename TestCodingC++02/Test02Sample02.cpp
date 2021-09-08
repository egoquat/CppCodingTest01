#include <iostream>
#include <cstdio>
using namespace std;

namespace namespace01{
	int main__() {
		int a = 0, b = 0, number = 0;
		scanf("%d", &a); scanf("%d", &b);
		for (int i = a; i <= b; ++i) {
			scanf("%d", &number);
			if (i <= 9) {
				if (i == 1)
					printf("one\n");
				else if (i == 2)
					printf("two\n");
				else if (i == 3)
					printf("three\n");
				else if (i == 4)
					printf("four\n");
				else if (i == 5)
					printf("five\n");
				else if (i == 6)
					printf("six\n");
				else if (i == 7)
					printf("seven\n");
				else if (i == 8)
					printf("eight\n");
				else if (i == 9)
					printf("nine\n");
			}
			else {
				printf((i % 2 == 0 ? "even\n" : "odd\n"));
			}
		}
		return 0;
	}
}


#include <iostream>
#include <cstdio>
using namespace std;

namespace namespace02 {
	int max_of_four(int a, int b, int c, int d) {
		int max = a;
		int nums[]{ a, b, c, d };
		for (int i = 1; i < 4; ++i) {
			if (nums[i] > max) max = nums[i];
		}
		return max;
	}

	int main__() {
		int a, b, c, d;
		scanf("%d %d %d %d", &a, &b, &c, &d);
		int ans = max_of_four(a, b, c, d);
		printf("%d", ans);

		return 0;
	}
}

#include <stdio.h>

namespace namespace03 {
	void update(int* a, int* b) {
		int n01 = *a; int n02 = *b;
		*a = n01 + n02;
		*b = n01 - n02;
		if (*b <= -1) *b = *b * -1;
	}

	int main__() {
		int a, b;
		int* pa = &a, * pb = &b;

		scanf("%d %d", &a, &b);
		update(pa, pb);
		printf("%d\n%d", a, b);

		return 0;
	}
}

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

namespace namespace04 {
	int main() {
		int nTotal, qTotal, n = 0, q = 0;
		cin >> nTotal >> qTotal;
		vector<vector<int>> nums(nTotal);
		for (int i = 0; i < nTotal; ++i) {
			int count = 0;
			cin >> count;
			nums[i].resize(count);
			for (int j = 0; j < count; ++j) {
				cin >> n;
				nums[i][j] = n;
			}
		}

		for (int i = 0; i < qTotal; ++i) {
			cin >> n >> q;
			cout << nums[n][q] << '\n';
		}

		return 0;
	}
}


#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

namespace namespace05 {
	struct Matrix {
		vector<vector<int>> a;
		Matrix operator+(Matrix& o) {
			Matrix r(*this);
			for (int i = 0; i < a.size(); ++i) {
				for (int j = 0; j < a[i].size(); ++j) {
					r.a[i][j] = a[i][j] + o.a[i][j];
				}
			}
			return r;
		}
		Matrix() {}
		Matrix(const Matrix& o) { a = o.a; }
	};

	int main() {
		int cases, k;
		cin >> cases;
		for (k = 0; k < cases; k++) {
			Matrix x;
			Matrix y;
			Matrix result;
			int n, m, i, j;
			cin >> n >> m;
			for (i = 0; i < n; i++) {
				vector<int> b;
				int num;
				for (j = 0; j < m; j++) {
					cin >> num;
					b.push_back(num);
				}
				x.a.push_back(b);
			}
			for (i = 0; i < n; i++) {
				vector<int> b;
				int num;
				for (j = 0; j < m; j++) {
					cin >> num;
					b.push_back(num);
				}
				y.a.push_back(b);
			}
			result = x + y;
			for (i = 0; i < n; i++) {
				for (j = 0; j < m; j++) {
					cout << result.a[i][j] << " ";
				}
				cout << endl;
			}
		}
		return 0;
	}
}


#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

namespace namespace06 {
	//Define the structs Workshops and Available_Workshops.
	//Implement the functions initialize and CalculateMaxWorkshops
	struct Workshop {
		int Start = 0, Duration = 0, End = 0, Overlap = 0;
		Workshop(int s, int d) : Start(s), Duration(d), End(s + d) {};
	};

	struct Available_Workshops {
		vector<Workshop> Workshops;
		void Add(int s, int d)
		{
			Workshop* w = nullptr;
			for (int i = 0; i < Workshops.size(); ++i) {
				if (Workshops[i].Start == s) { w = &Workshops[i]; }
			}
			if (w == nullptr) {
				Workshops.push_back(Workshop(s, d));
				w = &Workshops[Workshops.size() - 1];
			}
			w->Duration = std::min(w->Duration, d);
			w->End = w->Start + w->Duration;
		}
		void Sort() {
			std::sort(Workshops.begin(), Workshops.end(),
				[&](Workshop& a, Workshop& b) {
					return a.End < b.End;
				});
		}
		int Calculate() {
			int count = 1, next = 0;
			Workshop* w = &Workshops[0];
			next = w->End;
			vector<Workshop*> works{ w };
			for (int i = 1; i < Workshops.size(); ++i) {
				Workshop* iter = &Workshops[i];
				if (iter->Start < next) continue;
				next = iter->End;
				count++;
				works.push_back(iter);
			}
			return count;
		}
	};

	Available_Workshops Available;
	Available_Workshops* initialize(int* starts, int* durations, int n) {
		for (int i = 0; i < n; ++i) {
			Available.Add(starts[i], durations[i]);
		}
		Available.Sort();
		return &Available;
	}
	int CalculateMaxWorkshops(Available_Workshops* available) {
		return available->Calculate();
	}

	int main(int argc, char* argv[]) {
		int n; // number of workshops
		cin >> n;
		// create arrays of unknown size n
		int* start_time = new int[n];
		int* duration = new int[n];

		for (int i = 0; i < n; i++) {
			cin >> start_time[i];
		}
		for (int i = 0; i < n; i++) {
			cin >> duration[i];
		}

		Available_Workshops* ptr;
		ptr = initialize(start_time, duration, n);
		cout << CalculateMaxWorkshops(ptr) << endl;
		return 0;
	}
}


#include <iostream>
using namespace std;

namespace namespace07 {

	enum class Fruit { apple, orange, pear };
	enum class Color { red, green, orange };

	template <typename T> struct Traits;

	string Fruits[3]{ "apple", "orange", "pear" };
	string Colors[3]{ "red", "green", "orange" };
	bool OutRange(int idx) { return idx <= -1 || idx >= 3; }
	template <> struct Traits<Fruit> {
		static string name(int idx) {
			if (OutRange(idx)) return "unknown";
			return Fruits[idx];
		}
	};
	template <> struct Traits<Color> {
		static string name(int idx) {
			if (OutRange(idx)) return "unknown";
			return Colors[idx];
		}
	};

	int main()
	{
		int t = 0; std::cin >> t;

		for (int i = 0; i != t; ++i) {
			int index1; std::cin >> index1;
			int index2; std::cin >> index2;
			cout << Traits<Color>::name(index1) << " ";
			cout << Traits<Fruit>::name(index2) << "\n";
		}
		return 0;
	}
}


#include <iostream>
using namespace std;

namespace namespace07 {
	// Code Start ==============================================
	template <bool a> int reversed_binary_value() { return a; }

	template <bool a, bool b, bool... d> int reversed_binary_value() {
		int r = reversed_binary_value<b, d...>();
		return (r << 1) + a;
	}
	// Code End ================================================

	template <int n, bool...digits>
	struct CheckValues {
		static void check(int x, int y)
		{
			CheckValues<n - 1, 0, digits...>::check(x, y);
			CheckValues<n - 1, 1, digits...>::check(x, y);
		}
	};

	template <bool...digits>
	struct CheckValues<0, digits...> {
		static void check(int x, int y)
		{
			int z = reversed_binary_value<digits...>();
			std::cout << (z + 64 * y == x);
		}
	};

	int main__()
	{
		int t; std::cin >> t;

		for (int i = 0; i != t; ++i) {
			int x, y;
			cin >> x >> y;
			CheckValues<6>::check(x, y);
			cout << "\n";
		}
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

namespace namespace08 {
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
