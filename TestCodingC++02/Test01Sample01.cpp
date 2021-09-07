#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include <iomanip>
#include <sstream>

using namespace std;

bool IsRepeat(string str, string& repeat, int& pos, int& len) {
	for (int i = 0; i < str.size() / 2 - 1; ++i) {
		for (int j = 1; j < str.size(); ++j) {
			string sub = str.substr(i, j);
			int r = 0, count = (str.size() - i) / sub.size(), rem = (str.size() - i) % sub.size();
			if (rem == 0) rem = sub.size();
			for (int k = 0; k < count; ++k) {
				int sizeSub = (k == (count - 1)) ? rem : sub.size();
				if (str.compare(i + (k * sub.size()), sizeSub, sub, 0, sizeSub) == 0) {
					r++;
				}
				else {
					break;
				}
			}
			if (r >= 2 && r >= count - 1) {
				repeat = sub; pos = i; len = sub.size();
				return true;
			}
		}
	}

	return false;
}

void reciprocal2(int N) {
	double r = 1.0 / (double)N;

	std::stringstream stream;
	stream << std::fixed << std::setprecision(19) << r;
	string output(stream.str().substr(0, 19));
	int dot = 1;

	string fstr = output.substr(2, output.size() - 1);
	string rstr;
	int rpos = 0, rlen = 0;
	bool isRepeat = IsRepeat(fstr, rstr, rpos, rlen);
	
	string result;
	printf("%d// %d // %s // %s\n", N, isRepeat, output.c_str(), rstr.c_str());
	 
	//if (isRepeat){
	//	result = output.substr(0, rpos + 2 + rlen);
	//	printf("%s %s\n", result.c_str(), rstr.c_str());
	//}
	//else {
	//	result = output;
	//	printf("%s", result.c_str());
	//}
}

string Divide2(int num, int div, int precise = 20) {
	string output;
	int n = num, d = div, r = 0, v = 0;
	if (n < d) {
		output += "0.";
	}
	else {
		output += to_string((int)(n / d)) + ".";
		r = n % d;
		n = r;
	}
	int iter = 0;
	while (iter++ < precise) {
		n = n * 10;
		char append = '0';
		if (n >= d) {
			r = n % d;
			v = n / d;
			append = '0' + v;
			n = r;
		}
		output += append;
	}
	return output;
}

void reciprocal(int N) {
	string output2 = Divide2(1, N, 100);

	int dot = 1;
	string fstr = output2.substr(2, output2.size() - 1);
	string rstr;
	int rpos = 0, rlen = 0;
	bool isRepeat = IsRepeat(fstr, rstr, rpos, rlen);

	printf("%d// %d // %s // %s\n", N, isRepeat, output2.c_str(), rstr.c_str());

	//string result;
	//if (isRepeat) {
	//	result = output2.substr(0, rpos + 2 + rlen);
	//	printf("%s %s\n", result.c_str(), rstr.c_str());
	//}
	//else {
	//	result = output2;
	//	printf("%s", result.c_str());
	//}
}

int main() {
	//int n = 0;
	//scanf("%d", &n);
	//reciprocal(n);
	for (int i = 1; i < 100; ++i) {
		reciprocal(i);
	}

	int n = 0;
	scanf("%d", &n);
	return 0;
}