#include <string>
#include <vector>
#include <iostream>

using namespace std;

vector<int> GetDivisors(int n) {
	vector<int> divisors;
	int m = n / 2;
	for (int i = 1; i <= m; ++i) {
		if (n % i == 0) { divisors.push_back(i); }
	}
	divisors.push_back(n);
	return divisors;
}

int solution(int n) {
	int ans = 0;
	vector<int> divisors = GetDivisors(n);
	for (int i = 0; i < divisors.size(); ++i) {
		ans += divisors[i];
	}
	return ans;
}