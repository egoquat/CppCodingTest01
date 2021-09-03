#include <iostream>

using namespace std;

namespace InputOutput01
{
	int main(void)
	{
		double a, b;
		cin >> a >> b;
		cout.precision(9);
		cout << std::fixed << (a / b) << endl;

		return 0;
	}
}

namespace InputOutput02
{
	int main(void)
	{
		int a, b;
		cin >> a >> b;

		cout << (a + b) << endl;
		cout << (a - b) << endl;
		cout << (a * b) << endl;
		cout << (a / b) << endl;
		cout << (a % b) << endl;

		return 0;
	}
}

namespace InputOutput03
{
	int main(void)
	{
		int a, b, c;
		cin >> a >> b >> c;
		int rAC = a % c;
		int rBC = b % c;

		cout << ((a + b) % c) << endl;
		cout << ((rAC + rBC) % c) << endl;
		cout << ((a * b) % c) << endl;
		cout << ((rAC * rBC) % c) << endl;

		return 0;
	}
}

namespace InputOutput04
{
	int main(void)
	{
		int a, b;
		cin >> a >> b;
		int ba, bb, bc;
		ba = b % 10;
		bb = (b % 100) / 10;
		bc = b / 100;
		cout << (a * ba) << endl;
		cout << (a * bb) << endl;
		cout << (a * bc) << endl;
		cout << (a * b) << endl;

		return 0;
	}
}

namespace IF01
{
	int main(void)
	{
		int a, b;
		cin >> a >> b;

		if (a > b)
			cout << ">" << endl;
		else if (a < b)
			cout << "<" << endl;
		else
			cout << "==" << endl;

		return 0;
	}
}

namespace IF02
{
	int main(void)
	{
		int a, b;
		cin >> a >> b;

		if (a > b)
			cout << ">" << endl;
		else if (a < b)
			cout << "<" << endl;
		else
			cout << "==" << endl;

		return 0;
	}
}
