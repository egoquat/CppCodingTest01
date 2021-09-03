#include <iostream>

using namespace std;

int main(void)
{
	int h, m;
	cin >> h >> m;
	int to = (h * 60) + m - 45;
	if (to <= -1) to = (24 * 60) + to;

	int hh = to / 60;
	int mm = to % 60;
	cout << hh << " " << mm << endl;

	return 0;
}