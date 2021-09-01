#include <iostream>
#include <string>
#include <vector>
using namespace std;
//vector<int> solution02(int n) {
//	vector<int> answer, added;
//	answer.push_back(0);
//	added.push_back(0);
//	for (int i = 1; i < n; ++i)
//	{
//		vector<int> cache = added; added.clear();
//		for (int j = 0; j < cache.size(); ++j)
//		{
//			int idx = cache[j] + (j * 2);
//			answer.insert(answer.begin() + idx, 0);
//			answer.insert(answer.begin() + idx + 2, 1);
//			added.push_back(idx); added.push_back(idx + 2);
//			cout << "insert 0:" << idx << "/1:" << (idx + 2) << endl;
//		}
//	}
//	return answer;
//}

//bool IsPower2(int n)
//{
//	if (n == 0)
//		return false;
//
//	return (ceil(log2(n)) == floor(log2(n)));
//}
//vector<int> solution(int n) {
//	vector<int> answer;
//	int count = (1 << (n)) - 1;
//	//cout<<"count:"<<count<<endl;
//	for (int i = 1; i <= count; ++i)
//	{
//		int add = (IsPower2(i) || i % 4 == 1 || (i % 4 == 2 && (i / 4 % 2 == 0) || (i % 4 == 4) && (i % 8)) ? 0 : 1);
//		answer.push_back(add);
//		//cout<<add;
//	}
//	//cout<<endl;
//	return answer;
//}
