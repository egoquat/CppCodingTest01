// 200316_TestProgrammers.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <vector>
#include <cmath>
using namespace std;
vector<int> solution02(int n) {
	vector<int> answer, added;
	answer.push_back(0);
	added.push_back(0);
	for (int i = 1; i < n; ++i)
	{
		vector<int> cache = added; added.clear();
		for (int j = 0; j < cache.size(); ++j)
		{
			int idx = cache[j] + (j * 2);
			answer.insert(answer.begin() + idx, 0);
			answer.insert(answer.begin() + idx + 2, 1);
			added.push_back(idx); added.push_back(idx + 2);
		}
	}
	bool isOutput = true;
	if (true == isOutput)
	{
		int count = (1 << (n)) - 1;
		cout << "n:" << n << "/count:" << count << endl;
		for (int i = 0; i < answer.size(); ++i)
		{
			cout << answer[i];
			if ((i + 1) % 4 == 0)
				cout << " ";
		}
		cout << endl;
	}

	return answer;
}
//กต	n : 2 / count : 3
// 0010 011
// 0001 001
void fill(vector<int>& answer, int idx, int depth, int fold)
{
	int depthCurr = depth - 1;
	int idxCurr = idx + ((1 << depthCurr) -1);
	if (idxCurr >= answer.size()) return;
	answer[idxCurr] = fold;
	cout << " ("<<idxCurr<<":" << fold << ")";
	if (depthCurr <= 0)
		return;
	fill(answer, idx, depthCurr, 0);
	fill(answer, idxCurr+1, depthCurr, 1);
}
vector<int> solution03(int n) {
	int count = (1 << n) - 1;
	vector<int> answer;
	cout << "n:" << n << "/count:" << count << endl;
	answer.resize(count);
	fill(answer, 0, n, 0);
	cout << endl; 
	bool isOutput = true;
	if (true == isOutput)
	{
		for (int i = 0; i < answer.size(); ++i)
		{
			cout << answer[i];
			if ((i + 1) % 4 == 0)
				cout << " ";
		}
		cout << endl;
	}

	return answer;
}
bool IsPower2(int n)
{
	if (n == 0)
		return false;

	return (ceil(log2(n)) == floor(log2(n)));
}
vector<int> solution(int n) {
	vector<int> answer;
	int count = (1 << (n)) - 1;
	cout<<"n:"<<n<<"/count:"<<count<<endl;
	for (int i = 1; i <= count; ++i)
	{
		//int add = (IsPower2(i) || i % 4 == 1 || ((i % 4 == 2) && (i / 4 % 2 == 0)) ? 0 : 1);
		int add = (IsPower2(i) ? 0 : 1);
		answer.push_back(add);
		cout<<add;
		if (i % 4 == 0)
			cout << " ";
	}
	cout<<endl;
	return answer;
}
vector<int> solution__(int n) {
	vector<int> answer;
	vector<int> t;
	int temp, s;
	for (int i = 1; i <= n; i++) {
		t.clear();
		temp = 0;
		s = answer.size();
		while (temp <= s) {
			if (temp % 2 == 0)
				t.push_back(0);
			else
				t.push_back(1);
			if ((answer.size() > 0) && (temp < s))
				t.push_back(answer[temp]);
			temp++;
		}
		answer = t;
	}
	return answer;
}
//int main()
//{
//	vector<int> returns;
//	for (int i = 1; i < 7; ++i)
//	{
//		//solution(i);
//		//solution02(i);
//		solution03(i);
//	}
//	return 0;
//}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
