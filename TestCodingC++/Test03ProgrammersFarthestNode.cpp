#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <iostream>

using namespace std;

struct Node {
	int Idx; int Dist; vector<int> Adjs;
	Node(int idx) : Dist(0) { Idx = idx; }
};
vector<Node> Nodes;

int solution(int n, vector<vector<int>> edge) {
	for (int i = 0; i <= n; i++) {
		Nodes.push_back(Node(i));
	}

	for (int i = 0; i < edge.size(); ++i) {
		vector<int>& es = edge[i];
		Nodes[es[0]].Adjs.push_back(es[1]);
		Nodes[es[1]].Adjs.push_back(es[0]);
	}

	unordered_map<int, int> dists;
	unordered_map<int, int> visits;
	int dist_max = 0, dist = 0;
	visits[Nodes[1].Idx] = 0;

	//BFS.
	vector<int> next_nodes = Nodes[1].Adjs;
	while (next_nodes.size() >= 1) {
		dist++;
		vector<int> nextadj_nodes;
		for (int i = 0; i < next_nodes.size(); ++i) {
			Node& adj = Nodes[next_nodes[i]];
			bool exist = visits.find(adj.Idx) != visits.end();
			if (exist) {
				continue;
			}

			visits[adj.Idx] = dist;
			dists[dist]++;
			dist_max = std::max(dist, dist_max);
			for (int j = 0; j < adj.Adjs.size(); ++j) {
				nextadj_nodes.push_back(adj.Adjs[j]);
			}
			//cout << " SetDist:Idx:" << adj.Idx << "/dist:" << dist << endl;
		}
		next_nodes = nextadj_nodes;
	}

	int answer = dists[dist_max];
	return answer;
}
