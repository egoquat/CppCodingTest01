#include <string>
#include <vector>
#include <functional>
#include <queue>
#include <set>

using namespace std;

string solution(vector<int> nums, string hand) {
	vector<vector<int>> Adjs(12);
	Adjs[0].push_back(8);
	Adjs[1].push_back(2); Adjs[1].push_back(4);
	Adjs[2].push_back(1); Adjs[2].push_back(3); Adjs[2].push_back(5);
	Adjs[3].push_back(2); Adjs[3].push_back(6);
	Adjs[4].push_back(1); Adjs[4].push_back(5); Adjs[4].push_back(7);
	Adjs[5].push_back(2); Adjs[5].push_back(4); Adjs[5].push_back(6); Adjs[5].push_back(8);
	Adjs[6].push_back(3); Adjs[6].push_back(5); Adjs[6].push_back(9);
	Adjs[7].push_back(4); Adjs[7].push_back(8);
	Adjs[8].push_back(0); Adjs[8].push_back(5); Adjs[8].push_back(7); Adjs[8].push_back(9);
	Adjs[9].push_back(6); Adjs[9].push_back(8);
	Adjs[10].push_back(0); Adjs[10].push_back(7);
	Adjs[11].push_back(0); Adjs[11].push_back(9);
	function<int(vector<int>, set<int>&, int, int)> GetDist = [&](vector<int> ps, set<int>& vs, int depth, int n) {
		vector<int> nexts;
		++depth;
		for (int i = 0; i < ps.size(); ++i) {
			int curr = ps[i];
			if (curr == n) return depth;
			vector<int>& adjs = Adjs[curr];
			for (int j = 0; j < adjs.size(); ++j) {
				int adj = adjs[j];
				if (vs.find(adj) != vs.end()) continue;
				if (adj == n) return depth + 1;
				vs.insert(adj);
				nexts.push_back(adj);
			}
		}
		return GetDist(nexts, vs, depth, n);
	};
	string ans;
	ans.resize(nums.size());
	bool isR = hand[0] == 'r';
	int currR = 11, currL = 10;
	vector<int> ps; set<int> vs;
	for (int i = 0; i < nums.size(); ++i) {
		int n = nums[i];
		char c;
		if (n == 1 || n == 4 || n == 7) {
			c = 'L';
		}
		else if (n == 3 || n == 6 || n == 9) {
			c = 'R';
		}
		else {
			int distR = 0, distL = 0;
			vs.clear(); ps.clear(); ps.push_back(currR);
			distR = GetDist(ps, vs, 0, n);
			vs.clear(); ps.clear(); ps.push_back(currL);
			distL = GetDist(ps, vs, 0, n);
			if (distR == distL) {
				c = isR == true ? 'R' : 'L';
			}
			else {
				c = distR < distL ? 'R' : 'L';
			}
		}
		if (c == 'R') currR = n;
		else currL = n;
		ans[i] = c;
	}
	return ans;
}

int main() {
	vector<int> nums = { 7, 0, 8, 2, 8, 3, 1, 5, 7, 6, 2 };
	string hand = "left";
	string touches = solution(nums, hand);
	return 0;
}