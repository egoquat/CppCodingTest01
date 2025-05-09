#include <string>
#include <vector>
#include <queue>
#include <iostream>
#include <string>

using namespace std;

int solution(vector<int> ps, int m, int k) {
    int naddt = 0;
    queue<int> qs;
    int ncurr = 0;

    for (int i = 0; i < ps.size(); ++i) {
        cerr << i;
        if (i >= k) {
            int nserv = qs.front();
            qs.pop();
            ncurr = ncurr - nserv;
            cerr << " > pop : " << nserv;
        }
        
        int nuser = ps[i];
        int nneed = nuser / m;
        cerr << " need : " << nneed << ", " << nuser;
        
        int nadds = 0;
        if (nneed > ncurr) {
            nadds = nneed - ncurr;
            naddt = naddt + nadds;
            ncurr = ncurr + nadds;
            cerr << ", add : " << nadds;
        }
        cerr << ", ncurr : " << ncurr;
        qs.push(nadds);
        cerr << endl;
    }
    return naddt;
}