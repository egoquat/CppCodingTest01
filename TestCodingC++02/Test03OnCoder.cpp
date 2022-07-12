
// 10. 평형점 구하기
#include "iostream"
#include "algorithm"

using namespace std;

class Solution {
public:
	double solution(int x1, int m1, int x2, int m2) {
		double r = x2 - x1;
		double dx1 = x1, dx2 = x2;
		double dm1 = sqrt(m1), dm2 = sqrt(m2);
		double p = dx1 + (r * (dm1 / (dm1 + dm2)));

		return p;
	}
};

