#include <string>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

vector<int> solution(vector<int> numbers) {
	vector<int> answer;
	set<int> sums;
	int a, b, sum;
	for (int i = 0; i < numbers.size(); ++i) {
		a = numbers[i];
		for (int j = i + 1; j < numbers.size(); ++j) {
			b = numbers[j];
			sum = a + b;
			if (sums.find(sum) == sums.end()) {
				answer.push_back(sum);
				sums.insert(sum);
			}
		}
	}
	sort(answer.begin(), answer.end(), less<int>());
	return answer;
}