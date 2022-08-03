#include <string>
#include <vector>

using namespace std;

string DAYS[] = { "SUN","MON","TUE","WED","THU","FRI","SAT" };
int MONTH[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };

void ApplyLeapYear(int year) {
	if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
		MONTH[1] = 29;
}

string GetDay(int year, int month, int day) {
	int total = 0;
	ApplyLeapYear(year);
	for (int i = 1; i < month; ++i) {
		total += MONTH[i - 1];
	}
	total += day - 1;

	int resultday = (5 + total) % 7;
	return DAYS[resultday];
}

string solution(int a, int b) {
	string answer = GetDay(2016, a, b);
	return answer;
}