#include <string>
#include <vector>

using namespace std;
long GetNextCollatz(long n) {
	if (n % 2 == 0) {
		return n / 2;
	}
	else {
		return (n * 3) + 1;
	}
}

int solution(int num) {
	int ans = -1;
	if (num == 1) return 0;
	long numiter = num;
	for (int i = 0; i < 500; ++i) {
		numiter = GetNextCollatz(numiter);
		if (numiter == 1) {
			ans = i + 1; break;
		}
	}
	return ans;
}

int main() {
	int n = 626331;
	int answer = solution(n);
	return 0;
}