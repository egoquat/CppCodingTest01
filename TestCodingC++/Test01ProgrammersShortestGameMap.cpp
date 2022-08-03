#include<vector>
#include<queue>
#include<iostream>

using namespace std;

void bfs(vector<vector<int>>& maps, vector<vector<int>>& visits) {
	int dx[4] = { 1,0,-1,0 };
	int dy[4] = { 0,1,0,-1 };

	int x = 0, y = 0;
	visits[x][y] = 1;
	queue<int> que;
	que.push((x << 8) | y);

	while (que.empty() == false) {
		int current = que.front();
		que.pop();
		int cx = current >> 8;
		int cy = current & (0xff);

		for (int i = 0; i < 4; ++i) {
			int nx = cx + dx[i];
			int ny = cy + dy[i];
			if (nx < 0 || nx >= maps.size() || ny < 0 || ny >= maps[0].size())
				continue;

			if (visits[nx][ny] == 0 && maps[nx][ny] == 1) {
				visits[nx][ny] = visits[cx][cy] + 1;
				que.push((nx << 8) | ny);
			}
		}
	}
}

int solution(vector<vector<int> > maps)
{
	int row = maps.size();
	int col = maps[0].size();
	vector<vector<int>> visits;
	visits.resize(row); for (int i = 0; i < visits.size(); ++i) { visits[i].resize(col); }

	bfs(maps, visits);

	int answer = visits[row - 1][col - 1];
	return answer == 0 ? -1 : answer;
}