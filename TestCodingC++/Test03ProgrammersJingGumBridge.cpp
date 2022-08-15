https://school.programmers.co.kr/learn/courses/30/lessons/43236# // Test Case 2 Failed
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

int solution(int distance, vector<int> rocks, int n) {
    rocks.push_back(distance);
    sort(rocks.begin(), rocks.end(), less<int>());
    /*
    int l = 0;
    for (int i = 0; i < rocks.size(); ++i) {
        int d = rocks[i] - l;
        l = rocks[i];
        cout << " " << d;
    }
    cout << endl;
    */
    int left = 1,
        right = distance,
        mid = (right - left) / 2,
        mindist = distance,
        last = 0,
        skipped = 0;
    while (right - left > 1) {
        skipped = 0, last = 0;
        mindist = distance;
        for (int i = 0; i < rocks.size(); ++i) {
            int d = rocks[i] - last;
            if (d < mid) {
                skipped++;
            }
            else {
                last = rocks[i];
                mindist = min(mindist, d);
            }
        }
        if (skipped == n) break;
        if (skipped < n) {
            left = mid;
        }
        else {
            right = mid;
        }
        cout << "next mid : " << mid << "/left:" << left << "/right:" << right << "/skipped:" << skipped << endl;
        mid = (left + right) / 2;
    }

    int answer = mindist;
    return answer;
}