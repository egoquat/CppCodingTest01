//https://school.programmers.co.kr/learn/courses/30/lessons/62048

#include <algorithm>
#include <iostream>

using namespace std;

long getgcd(long w, long h) {
	long n = max(w, h), m = min(w, h);
	while (m > 0) {
		int r = n % m;
		n = m; m = r;
	}
	return n;
}

long long solution(int w, int h) {
	int gcd = getgcd(w, h);
	int cnt = (w + h - gcd);
	long long ans = (((long long)w * (long long)h)) - cnt;
	return ans;
}
