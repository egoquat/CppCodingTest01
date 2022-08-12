////////////////////// 124 https://school.programmers.co.kr/learn/courses/30/lessons/12899/solution_groups?language=cpp
#include <string>
#include <vector>
#include <queue>
#include <iostream>

using namespace std;

string solution(int n) {
	char conv[3] = { '4', '1', '2' };
	string answer;
	int num = n;
	while (num != 0) {
		int r = num % 3;
		num = num / 3;
		if (r == 0) num--;
		answer = conv[r] + answer;
	}
	return answer;
}