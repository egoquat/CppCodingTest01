#include <string>
#include <vector>
#include <unordered_map>
#include <list>
#include <queue>

using namespace std;

#define umap unordered_map

int w = 0, h = 0;

void UpdateSideDfs(vector<string>& stgs, int x, int y) {
    stgs[y][x] = '#';
    const int dx[] = { -1, 1, 0, 0 };
    const int dy[] = { 0, 0, -1, 1 };
    for (int i = 0; i < 4; ++i) {
        int ix = x + dx[i], iy = y + dy[i];
        if (ix >= 0 && ix < w && iy >= 0 && iy < h) {
            if (stgs[iy][ix] == '$') {
                UpdateSideDfs(stgs, ix, iy);
            }
        }
    }
}

void UpdateSideBfs(vector<string>& stgs, int x, int y) {
    queue<pair<int, int>> q;
    q.push({x, y});
    while(q.empty() == false) {
        pair<int, int> cu = q.front();
        q.pop();
        int cx = cu.first, cy = cu.second;
        stgs[cy][cx] = '#';

        const int dx[] = { -1, 1, 0, 0 };
        const int dy[] = { 0, 0, -1, 1 };
        for (int i = 0; i < 4; ++i) {
            int ix = cx + dx[i], iy = cy + dy[i];
            if (ix >= 0 && ix < w && iy >= 0 && iy < h) {
                if (stgs[iy][ix] == '$') {
                    stgs[iy][ix] = '#';
                    q.push({ix, iy});
                }
            }
        }
    }
}

bool IsSide(const vector<string>& stgs, int x, int y) {
    bool bSide = (x == 0 || x >= (w - 1)) || (y == 0 || y >= (h - 1));
    if (bSide == true) return true;
    
    int ix = 0, iy = 0; 
    ix = x - 1; iy = y;
    if (ix >= 0 && ix < w && iy >= 0 && iy < h) {
        bSide |= (stgs[iy][ix] == '#');
    }
    ix = x + 1; iy = y;
    if (ix >= 0 && ix < w && iy >= 0 && iy < h) {
        bSide |= (stgs[iy][ix] == '#');
    }
    ix = x; iy = y - 1;
    if (ix >= 0 && ix < w && iy >= 0 && iy < h) {
        bSide |= (stgs[iy][ix] == '#');
    }
    ix = x; iy = y + 1;
    if (ix >= 0 && ix < w && iy >= 0 && iy < h) {
        bSide |= (stgs[iy][ix] == '#');
    }
    return bSide;
}

int solution(vector<string> stgs, vector<string> reqs) {
    w = stgs[0].size(), h = stgs.size();
    int ntotal = w * h;
    umap<char, int> stns;
    umap<char, list<int>> stss;
    for (int i = 0; i < stgs.size(); ++i) {
        const string& stg = stgs[i];
        for (int j = 0; j < stg.size(); ++j) {
            char c = stg[j];
            stns[c]++;
            list<int>& sts = stss[c];
            int idx = i * w + j;
            sts.push_back(idx);
        }
    }
    
    int num = 0;
    for (int i = 0; i < reqs.size(); ++i) {
        const string& req = reqs[i];
        char c = req[0];
        bool bRAll = req.size() >= 2;
        list<int>& sts = stss[c];
        if (bRAll == true) {
            num += stns[c];
            stns[c] = 0;
             for (int idx : sts) {
                int x = idx % w;
                int y = idx / w;
                bool bRem = IsSide(stgs, x, y);
                if (bRem == true) {
                    UpdateSideBfs(stgs, x, y);
                } else {
                    stgs[y][x] = '$';
                }
             }
            sts.clear();
            continue;
        }
        if (sts.size() <= 0)
            continue;

        list<int> emps;
        for (list<int>::iterator it = sts.begin(); it != sts.end();) {
            int idx = *it;
            int x = idx % w;
            int y = idx / w;
            
            bool bRem = IsSide(stgs, x, y);
            if (bRem == true) {
                num++;
                stns[c]--;
                emps.push_back(idx);
                it = sts.erase(it);
            }
            else {
                ++it;
            }
        }

        for (int idx : emps) {
            int x = idx % w;
            int y = idx / w;
            UpdateSideBfs(stgs, x, y);
        }
    }
    
    int ans = ntotal - num;
    return ans;
}

int main()
{
    vector<vector<string>> stgs {
    { "BBACC","BBACC","BAAAC","BBAAC","BBACC","BBBCC" }, 
    { "BBBB","AAAB","BBBB" }, 
    { "AAAA", "ABAA", "ABAA", "ACAA", "AAAA" }, 
    { "AAA","BAB","AAA" }, 
    { "AAAA", "ABAA", "ABAA", "ACAA", "AAAA" }, 
    {"AAAAA", "ABCDA", "AGAEA", "AZAFA", "ZYAAA" }, 
    { "CCCCC", "CABAC", "CABAC", "CCABC" }, 
    { "HAH", "HBH", "HHH", "HAH", "HBH" }, 
    {"AZWQY", "CAABX", "BBDDA", "ACACA"} };
    vector<vector<string>> reqs {
    { "A","A","A","A","A" }, 
    { "BB","C" }, 
    { "A" }, 
    { "BB","C" }, 
    { "BB", "DD", "Z", "Y", "Z", "G", "C", "E", "F" }, 
    { "BB", "A" },
    { "C", "BB", "A" }, 
    { "C", "B", "B", "B", "B", "H" }, 
    {"A", "BB", "A"},  };

    for (int i = 0; i < stgs.size(); ++i) {
        solution(stgs[i], reqs[i]);   
    }
}