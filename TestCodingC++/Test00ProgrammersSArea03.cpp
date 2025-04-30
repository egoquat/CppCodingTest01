
// 66%
#include <string>
#include <vector>
#include <iostream>

using namespace std;
vector<string> Cells;
int W, H;
void GetTopLeft(int x, int y, int& xout, int& yout) {
	char c = Cells[x][y];
	int left = x, top = y;
	for (int i = x; i >= 0; --i) {
		char ch = Cells[i][y];
		if (ch != c) break;
		left = i;
	}
	for (int i = y; i >= 0; --i) {
		char ch = Cells[x][y];
		if (ch != c) break;
		top = i;
	}
	xout = left; yout = top;
}

int GetW(int x, int y, int cond = 1) {
	char c = Cells[x][y];
	int count = 1;
	if (cond == 1) {
		for (int i = x + 1; i < W; ++i) {
			char ch = Cells[i][y];
			if (ch != c) break;
			count++;
		}
	}
	else {
		for (int i = x - 1; i >= 0; --i) {
			char ch = Cells[i][y];
			if (ch != c) break;
			count++;
		}
	}
	if (count <= 2) return -1;
	return count;
}

int GetH(int x, int y, int cond = 1) {
	char c = Cells[x][y];
	int count = 1;
	if (cond == 1) {
		for (int i = y + 1; i < H; ++i) {
			char ch = Cells[x][i];
			if (ch != c) break;
			count++;
		}
	}
	else {
		for (int i = y - 1; i >= 0; --i) {
			char ch = Cells[x][i];
			if (ch != c) break;
			count++;
		}
	}
	if (count <= 2) return -1;
	return count;
}

int GetAreaWB(int x, int y, int cond) {
	int w = GetW(x, y, cond);
	//cout << " GetAreaWB: GetW w:" << w << "/cond:" << cond << endl;
	if (w < 3) return -1;
	int area = -1;
	int c = Cells[x][y];
	for (int i = y + 1; i < H; ++i) {
		char ch = Cells[x][i];
		if (ch != c) break;
		if (i < y + 2) continue;
		int wi = GetW(x, i, cond);
		if (wi < 3) continue;
		wi = min(wi, w);
		int areai = (wi * 2) + (i - y - 1);
		area = max(area, areai);
		//cout << "  GetAreaWB: areai:" << areai << endl;
	}
	return area;
}

int GetAreaHR(int x, int y, int cond) {
	int h = GetH(x, y, cond);
	//cout << " GetAreaHR: GetH h:" << h << "/cond:" << cond << endl;
	if (h < 3) return -1;
	int area = -1;
	int c = Cells[x][y];
	for (int i = x + 1; i < W; ++i) {
		char ch = Cells[i][y];
		if (ch != c) break;
		if (i < x + 2) continue;
		int hi = GetH(i, y, cond);
		if (hi < 3) continue;
		hi = min(hi, h);
		int areai = (hi * 2) + (i - x - 1);
		area = max(area, areai);
		//cout << "  GetAreaHR: areai:" << areai << endl;
	}
	return area;
}

int GetAreaWBBoth(int x, int y) {
	//cout << "GetToWB x:" << x << "/y:" << y << endl;
	int arear = GetAreaWB(x, y, 1);
	int areal = GetAreaWB(x, y, -1);
	//cout << "  GetToWB: arear:" << arear << "/areal:" << areal << endl;
	int area = max(arear, areal);
	return area;
}

int GetAreaHRBoth(int x, int y) {
	//cout << "GetToHR x:" << x << "/y:" << y << endl;
	int areab = GetAreaHR(x, y, 1);
	int areat = GetAreaHR(x, y, -1);
	//cout << "  GetToHR: areab:" << areab << "/areat:" << areat << endl;
	int area = max(areab, areat);
	return area;
}

int GetArea(int x, int y) {
	if (x >= W - 2) return -1; if (y >= H - 2) return -1;
	int area = 0;
	int areawb = GetAreaWBBoth(x, y);
	int areahr = GetAreaHRBoth(x, y);
	area = max(areawb, areahr);
	return area;
}

int solution(vector<string> cells) {
	W = cells.size(); H = cells[0].size();
	Cells = cells;
	int ans = -1;
	for (int x = 0; x < W; ++x) {
		for (int y = 0; y < H; ++y) {
			int area = GetArea(x, y);
			ans = max(area, ans);
		}
	}
	return ans;
}

int main() {
	//vector<string> data = { "AAA", "AAA", "AAA", "AAA" };
	//vector<string> data = { "BAAA", "BAAA", "AABB", "AAAA" };
	//vector<string> data = { "aaaaa", "bbabb", "aaaaa"};
	//vector<string> data = { "aba", "aba", "aaa", "aba", "aba" };
	//vector<string> data = { "aaaabbb", "bbaabbb", "aaaabbb", "aaaabbb"};
	//vector<string> data = { "abbbba", "abbbba", "abaaba", "abbbaa" };
	vector<string> data = { "bbccddaa", "fafffffa", "ggfgggfg", "ggfffffg" };
	int answer = solution(data);
	return 0;
}