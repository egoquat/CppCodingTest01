#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


int main() {
	int cnt = 0;
	scanf("%d", &cnt);
	vector<int> nums(cnt);
	for (int i = 0; i < cnt; ++i) {
		scanf("%d", &nums[i]);
	}
	int epos = 0, eend = 0;
	scanf("%d", &epos);
	nums.erase(nums.begin() + epos - 1);

	scanf("%d %d", &epos, &eend);
	nums.erase(nums.begin() + epos - 1, nums.begin() + eend - 1);


	printf("%d\n", nums.size());
	for (int i = 0; i < nums.size(); ++i) {
		printf("%d ", nums[i]);
	}
	return 0;
}