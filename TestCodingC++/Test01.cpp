#include "Test01.h"
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <stack>
#include <map>
#include <algorithm>
#include <iostream>
#include <cmath>
#include <functional>

using namespace std;

namespace test01
{
string solutiontest(vector<string> participant, vector<string> completion) {
	string answer = "";
	for (int i = 0; i < completion.size(); ++i)
	{
		const string& nameC = completion[i];
		vector<string>::iterator* iterRemove = nullptr;
		for (vector<string>::iterator iterP = participant.begin(); iterP != participant.end(); ++iterP)
		{
			if (*iterP == nameC)
			{
				iterRemove = &iterP;
				break;
			}
		}
		if (nullptr != iterRemove)
		{
			cout << "Erase : " << *(*iterRemove) << endl;
			participant.erase(*iterRemove);
		}
	}
	return answer;
}
}

///////////////////////// 참고
namespace marathon
{

string solution(vector<string> participant, vector<string> completion) {
	string answer = "";
	unordered_map<string, int> strMap;
	for (auto elem : completion)
	{
		if (strMap.end() == strMap.find(elem))
			strMap.insert(make_pair(elem, 1));
		else
			strMap[elem]++;
	}

	for (auto elem : participant)
	{
		if (strMap.end() == strMap.find(elem))
		{
			answer = elem;
			break;
		}
		else
		{
			strMap[elem]--;
			if (strMap[elem] < 0)
			{
				answer = elem;
				break;
			}
		}
	}
	return answer;
}
}
///////////////////////// 참고 //


///////////////////////// 참고 해쉬
/*전화번호 목록
문제 설명
전화번호부에 적힌 전화번호 중, 한 번호가 다른 번호의 접두어인 경우가 있는지 확인하려 합니다.
전화번호가 다음과 같을 경우, 구조대 전화번호는 영석이의 전화번호의 접두사입니다.
구조대 : 119
박준영 : 97 674 223
지영석 : 11 9552 4421
전화번호부에 적힌 전화번호를 담은 배열 phone_book 이 solution 함수의 매개변수로 주어질 때, 
어떤 번호가 다른 번호의 접두어인 경우가 있으면 false를 그렇지 않으면 true를 return 하도록 solution 함수를 작성해주세요.*/
bool solution_phone_book(vector<string> phone_book) {
	bool answer = true;
	//01
	/*sort(phone_book.begin(), phone_book.end());
	for (int idx = 0; idx < phone_book.size(); ++idx)
	{
		if (idx >= phone_book.size() - 1)
			break;
		string& phone = phone_book[idx];
		string& phoneNext = phone_book[idx+1];
		if (phoneNext.compare(0, phone.length(), phone) == 0)
		{
			answer = false;
			break;
		}
	}*/

	//02
	unordered_map<string, bool> map_phone;
	for (string& phone : phone_book)
	{
		map_phone[phone] = true;
	}

	for (string& phone : phone_book)
	{
		string phoneCheck;
		for (char& c : phone)
		{
			phoneCheck += c;
			if (0 == phoneCheck.compare(phone))
				break;
			if (true == map_phone[phoneCheck])
			{
				return false;
			}
		}
	}

	return answer;
}
///////////////////////// 참고 //

///////////////////////// 참고 경우의 수
/*해시 : 위장
스파이들은 매일 다른 옷을 조합하여 입어 자신을 위장합니다.
예를 들어 스파이가 가진 옷이 아래와 같고 오늘 스파이가 동그란 안경, 긴 코트, 파란색 티셔츠를 입었다면 
다음날은 청바지를 추가로 입거나 동그란 안경 대신 검정 선글라스를 착용하거나 해야 합니다.

종류	이름
얼굴	동그란 안경, 검정 선글라스
상의	파란색 티셔츠
하의	청바지
겉옷	긴 코트
스파이가 가진 의상들이 담긴 2차원 배열 clothes가 주어질 때 서로 다른 옷의 조합의 수를 return 하도록 solution 함수를 작성해주세요.*/
int solution_clothes(vector<vector<string>> clothes) {
	unordered_map<string, int> Parts;
	int total = 0;
	for (vector<string>& cloth : clothes)
	{
		Parts[cloth[1]]++; total++;
	}

	int answer = Parts.size() >= 1 ? 1 : 0;
	for (pair<string, int> pair : Parts)
	{
		answer = answer * (pair.second + 1);
	}

	return answer - 1;
}
///////////////////////// 참고 //

///////////////////////// 참고
#include <queue>
/*힙: 더 맵게
문제 설명
매운 것을 좋아하는 Leo는 모든 음식의 스코빌 지수를 K 이상으로 만들고 싶습니다.
모든 음식의 스코빌 지수를 K 이상으로 만들기 위해 Leo는 스코빌 지수가 가장 낮은 두 개의 음식을 아래와 같이 특별한 방법으로 섞어 새로운 음식을 만듭니다.
섞은 음식의 스코빌 지수 = 가장 맵지 않은 음식의 스코빌 지수 + (두 번째로 맵지 않은 음식의 스코빌 지수 * 2)
Leo는 모든 음식의 스코빌 지수가 K 이상이 될 때까지 반복하여 섞습니다.*/
int solution(vector<int> scoville, int K) {
	priority_queue<int, vector<int>, greater<int>> queue;
	for (int item : scoville)
	{
		queue.push(item);
	}

	int answer = 0, a = 0, b = 0;
	while (queue.top() < K)
	{
		a = queue.top(); queue.pop();
		if (queue.size() <= 0)
			return -1;
		b = queue.top(); queue.pop();
		queue.push(a + (b * 2));
		answer++;
	}

	return queue.top() < K ? -1 : answer;
}
///////////////////////// 참고 //

///////////////////////// 참고
/*힙: 디스크 컨트롤러
문제 설명
하드디스크는 한 번에 하나의 작업만 수행할 수 있습니다.디스크 컨트롤러를 구현하는 방법은 여러 가지가 있습니다.가장 일반적인 방법은 요청이 들어온 순서대로 처리하는 것입니다.

예를들어

- 0ms 시점에 3ms가 소요되는 A작업 요청
- 1ms 시점에 9ms가 소요되는 B작업 요청
- 2ms 시점에 6ms가 소요되는 C작업 요청*/
struct Compare
{
	bool operator()(vector<int>& a, vector<int>& b) { return a[1] > b[1]; }
};

int solution(vector<vector<int>> jobs) {
	sort(jobs.begin(), jobs.end());

	priority_queue<vector<int>, vector<vector<int>>, Compare> queue;
	int i = 0, time = 0, time_sum = 0;
	while (i < jobs.size() || false == queue.empty())
	{
		if (i < jobs.size() && time >= jobs[i][0])
		{
			//cout << " queue.push/i:" << i << endl;
			queue.push(jobs[i++]);
			continue;
		}

		if (true == queue.empty())
		{
			time = jobs[i][0];
			//cout << " (true == queue.empty())/i:" << i << "/time:" << time << endl;
		}
		else
		{
			time = time + queue.top()[1];
			time_sum = time_sum + (time - queue.top()[0]);
			queue.pop();
			//cout << " queue.pop()/i:" << i << "/time:" << time << endl;
		}
	}

	int answer = time_sum / jobs.size();
	return answer;
}
///////////////////////// 참고 // 


///////////////////////// 참고
/*이중우선순위큐
문제 설명
이중 우선순위 큐는 다음 연산을 할 수 있는 자료구조를 말합니다.

명령어	수신 탑(높이)
I 숫자	큐에 주어진 숫자를 삽입합니다.
D 1	큐에서 최댓값을 삭제합니다.
D - 1	큐에서 최솟값을 삭제합니다.*/
vector<int> solution_deque(vector<string> operations) {
	deque<int> numbers;

	for (string& o : operations)
	{
		char operate = o[0];
		int num = stoi(o.substr(2));
		if (operate == 'I') {
			numbers.push_back(num);
			sort(numbers.begin(), numbers.end());
		}
		else if (numbers.size() >= 1) {
			if (num >= 1)
				numbers.pop_back();
			else
				numbers.pop_front();
		}
	}
	vector<int> answer;
	answer.push_back(0); answer.push_back(0);
	if (numbers.empty() == false)
	{
		answer[0] = numbers.back(); answer[1] = numbers.front();
	}
	return answer;
}

///////////////////////// 참고 // 


///////////////////////// 참고
/*주식가격
문제 설명
초 단위로 기록된 주식가격이 담긴 배열 prices가 매개변수로 주어질 때, 가격이 떨어지지 않은 기간은 몇 초인지를 return 하도록 solution 함수를 완성하세요.*/
#include <stack>
vector<int> solution(vector<int> prices) {
	int count = prices.size();
	vector<int> answer(count);

	stack<int> s;
	for (int i = 0; i < count; ++i)
	{
		while (false == s.empty() && prices[s.top()] > prices[i])
		{
			int last = s.top(); s.pop();
			answer[last] = i - last;
		}
		s.push(i);
	}

	while (false == s.empty())
	{
		int last = s.top(); s.pop();
		answer[last] = count - last - 1;
	}

	return answer;
}
///////////////////////// 참고 //


///////////////////////// 참고 
/*정렬 01*/
vector<int> solutionsort01(vector<int> array, vector<vector<int>> commands) {
	vector<int> answer(commands.size());
	vector<int> partial;
	for (int i = 0; i < commands.size(); ++i)
	{
		vector<int>& cmd = commands[i];
		partial.assign(array.begin() + cmd[0]-1, array.begin() + cmd[1]);
		sort(partial.begin(), partial.end());
		answer[i] = partial[cmd[2]-1];
	}
	return answer;
}
///////////////////////// 참고 //


///////////////////////// 참고 테스트
/*가장큰수 테스트*/
string solutionhighestnumber_test(vector<int> numbers) {
	vector<string> nums;
	for (int i = 0; i < numbers.size(); ++i) {
		nums.push_back(to_string(numbers[i]));
	}
	sort(nums.begin(), nums.end(), [](string& a, string& b)
		{
			string& l = a.length() < b.length() ? a : b;
			string& h = a.length() < b.length() ? b : a;
			int i = 0, iHigh = 0; bool isHighB = a.length() < b.length();
			while (iHigh < h.length())
			{
				for (i = 0; i < l.length() && i + iHigh < h.length(); ++i)
				{
					int numl = l[i] - '0', numh = h[i + iHigh] - '0';
					if (i + iHigh == h.length() - 1) numl = l[l.length() - 1] - '0';
					if (numl == numh) continue;
					if (numl > numh) return isHighB;
					else return !isHighB;
				}
				iHigh += l.length();
			}
			return false;
		});

	string answer = "";
	for (int i = 0; i < numbers.size(); ++i) {
		answer += nums[i];
	}
	cout << answer << endl;
	return answer;
}
///////////////////////// 참고 테스트 //

///////////////////////// 참고
/*가장큰수*/
string solutionhighestnumber(vector<int> numbers) {
	vector<string> nums;
	for (int i = 0; i < numbers.size(); ++i) {
		nums.push_back(to_string(numbers[i]));
	}
	sort(nums.begin(), nums.end(), [](string& a, string& b)
	{
		return a + b > b + a;
	});

	if (nums[0] == "0") return "0";
	string answer = "";
	for (int i = 0; i < nums.size(); ++i) {
		answer += nums[i];
	}
	cout << answer << endl;
	return answer;
}
///////////////////////// 참고 //

///////////////////////// 참고 
/*모의고사*/
vector<int> solutionexamination(vector<int> answers) {
	vector<vector<int>> pattern = {
		{1,2,3,4,5},
		{2,1,2,3,2,4,2,5},
		{3,3,1,1,2,2,4,4,5,5}
	};
	vector<int> checks(3); int n0 = pattern[0].size(), n1 = pattern[1].size(), n2 = pattern[2].size();
	for (int i = 0; i < answers.size(); ++i)
	{
		int a = answers[i];
		if (pattern[0][i%n0] == a) checks[0]++;
		if (pattern[1][i%n1] == a) checks[1]++;
		if (pattern[2][i%n2] == a) checks[2]++;
	}

	vector<int> answer;
	int first = max(checks[0], max(checks[1], checks[2]));
	for (int i = 0; i < 3; ++i) { if (first == checks[i]) answer.push_back(i + 1); }
	return answer;
}
///////////////////////// 참고 //

///////////////////////// 참고 
/*소수찾기*/
namespace primefind
{
#include <unordered_set>
#include <cmath>
#include <queue>

void GetComsTestR(const vector<char>& arr, int depth, string stack, vector<bool>& visits, unordered_set<int>& combs) {
	if (depth >= arr.size()) return;
	for (int i = 0; i < arr.size(); ++i) {
		if (true == visits[i]) continue;
		visits[i] = true;
		stack.push_back(arr[i]);
		combs.insert(stoi(stack));
		GetComsTestR(arr, depth + 1, stack, visits, combs);
		stack.pop_back();
		visits[i] = false;
	}
}

void GetComsTest(const vector<char>& arr, unordered_set<int>& combs) {
	vector<bool> visits(arr.size(), false);
	string stack;
	GetComsTestR(arr, 0, stack, visits, combs);
}

void GetComsTestQR(const vector<char>& arr, int depth, string stack, vector<bool>& visits, priority_queue<int>& combs) {
	if (depth >= arr.size()) return;
	for (int i = 0; i < arr.size(); ++i) {
		if (true == visits[i]) continue;
		visits[i] = true;
		stack.push_back(arr[i]);
		combs.push(stoi(stack));
		GetComsTestQR(arr, depth + 1, stack, visits, combs);
		stack.pop_back();
		visits[i] = false;
	}
}

void GetComsTestQ(const vector<char>& arr, priority_queue<int>& combs) {
	vector<bool> visits(arr.size(), false);
	string stack;
	GetComsTestQR(arr, 0, stack, visits, combs);
}

bool IsPrimeSimple(int n) {
	if (n <= 1) return false;
	if (n <= 3) return true;
	//int s = sqrt(n + 1);
	int s = n / 2;
	for (int i = 2; i <= s; ++i) {
		if (n % i == 0) return false;
	}
	return true;
}

int solution(string nums) {
	vector<char> arr(nums.begin(), nums.end());
	unordered_set<int> combs;
	GetComsTest(arr, combs);

	priority_queue<int> combsq;
	GetComsTestQ(arr, combsq);

	vector<pair<int, bool>> isprimes(combs.size());
	unordered_set<int>::iterator iter = combs.begin();
	for (int i = 0; iter != combs.end(); ++iter, ++i) {
		int num = *iter;
		isprimes[i] = make_pair(num, IsPrimeSimple(num));
	}

	int answer = 0;
	return answer;
}
}
///////////////////////// 참고 //

///////////////////////// 참고
/*타겟넘버 완전탐색*/
#include <unordered_set>

void GetCombsR(vector<bool> visits, int depth, vector<string>& combs) {
	if (depth >= visits.size()){
		string combination;
		for (int j = 0; j < visits.size(); ++j) {
			combination += visits[j] == true ? '1' : '0';
		}
		combs.push_back(combination);
		return;
	}
	
	visits[depth] = true;
	GetCombsR(visits, depth + 1, combs);
	visits[depth] = false;
	GetCombsR(visits, depth + 1, combs);
}

void GetCombs(int n, vector<string>& combs) {
	vector<bool> visits(n, false);
	GetCombsR(visits, 0, combs);
}

int solutiontargetnumbertest(vector<int> numbers, int target) {
	unordered_map<char, int> operates = { make_pair('0', 1), make_pair('1', -1) };
	vector<string> combs;
	GetCombs(numbers.size(), combs);
	int answer = 0;
	vector<int> numbs(combs.size());
	for (int i = 0; i < combs.size(); ++i) {
		string& operate = combs[i];
		int num = 0;
		for (int j = 0; j < operate.length(); ++j) {
			num = num + (numbers[j] * operates[operate[j]]);
		}
		numbs[i] = num;
		if (num == target) answer++;
	}
	return answer;
}
///////////////////////// 참고 // 

///////////////////////// 참고
/*네트워크 깊이너비우선탐색 DFS,BFS*/
void GetLinkR(int idx, vector<vector<int>>& coms, vector<bool>& visits, int depth) {
	if (true == visits[idx]) return;
	vector<int> links = coms[idx];
	visits[idx] = true;
	for (int i = 0; i < links.size(); ++i) {
		if (i == idx || links[i] == 0) continue;
		GetLinkR(i, coms, visits, depth + 1);
	}
}

int GetLink(vector<vector<int>>& coms) {
	vector<bool> visits(coms.size(), false);
	int num = 0;
	for (int i = 0; i < coms.size(); ++i) {
		if (true == visits[i]) continue;
		GetLinkR(i, coms, visits, 0); num++;
	}
	return num;
}

int solutionnetwork(int n, vector<vector<int>> computers) {
	int answer = GetLink(computers);
	return answer;
}
///////////////////////// 참고 //

///////////////////////// 참고
/*
단어변환 깊이/너비 우선 탐색(DFS/BFS)*/
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

int Find(vector<string>& words, string& target){
	vector<string>::iterator it = std::find(words.begin(), words.end(), target);
	if (it == words.end()) return -1;
	return std::distance(words.begin(), it);
}

bool IsAdj(string& a, string& b){
	int diff = 0;
	for (int i = 0; i < a.size(); ++i){
		if (a[i] == b[i]) continue;
		diff++;
	}
	return 1 == diff;
}

void GetLinkWordR(vector<string>& words, vector<bool>& visits, int current, int target, int depth, int& link_out) {
	if (target == current) {
		link_out = std::min(depth, link_out);
		return;
	}
	visits[current] = true;
	for (int i = 0; i < words.size(); ++i) {
		if (true == visits[i]) continue;
		if (IsAdj(words[i], words[current]) == false) continue;
		GetLinkWordR(words, visits, i, target, depth + 1, link_out);
	}
}

int GetLinkWord(vector<string>& words, string& start, int target){
	int min = words.size();
	//vector<int> counts(words.size(), -1);
	for (int i = 0; i <words.size(); ++i){
		if (IsAdj(words[i], start) == false) continue;
		vector<bool> visits(words.size(), false);
		int cnt = words.size();
		GetLinkWordR(words, visits, i, target, 1, cnt);
		//counts[i] = cnt;
		min = std::min(min, cnt);
	}
	return min;
}
int solutionwordsimilar(string begin, string target, vector<string> words) {
	int idx = Find(words, target);
	if (-1 == idx) return 0;
	GetLinkWord(words, begin, idx);
	int answer = 0;
	return answer;
}
///////////////////////// 참고 //

///////////////////////// 참고
/*여행경로 깊이/너비 우선 탐색(DFS/BFS)*/
#include <string>
#include <vector>

vector<string> solutiontairportpath(vector<vector<string>> tickets) {
	vector<string> answer;
	return answer;
}
///////////////////////// 참고 //

///////////////////////// 참고
/*체육복 탐욕법*/
#include <string>
#include <vector>

int solutiontrainingwear(int n, vector<int> lost, vector<int> reserve) {
	
	int answer = 0;
	return answer;
}
///////////////////////// 참고 //

///////////////////////// 참고
/*가장먼노드: fault : 시간초과 테스트 */
#include <string>
#include <vector>
#include <algorithm>
namespace fartestnode{
struct Node {
	int Idx = -1;
	int Dist = 999999;
	vector<int> Adjs;
};
vector<Node> Nodes;
void AddEdge(vector<int>& edge) {
	for (int i = 0; i <= 1; ++i) {
		Node& node = Nodes[edge[i]];
		node.Idx = edge[i];
		node.Adjs.push_back(edge[1 - i]);
	}
}
void SetDistR(int idx, vector<bool> visits, int depth) {
	Node& node = Nodes[idx];
	if (node.Dist > depth) node.Dist = depth;
	if (true == visits[idx]) return;
	visits[idx] = true;
	for (int adj : node.Adjs) {
		SetDistR(adj, visits, depth + 1);
	}
}
void SetDist() {
	vector<bool> visits(Nodes.size() + 1, false);
	SetDistR(1, visits, 0);
}
int solutionfarstnodetest01(int n, vector<vector<int>> edge) {
	Nodes.resize(n + 1);
	for (vector<int>& e : edge) {
		AddEdge(e);
	}
	SetDist();
	vector<int> orders(Nodes.size() - 1);
	for (int i = 1; i < Nodes.size(); ++i) {
		orders[i - 1] = i;
	}
	sort(orders.begin(), orders.end(), [&](const int& a, const int& b) {
		return Nodes[a].Dist > Nodes[b].Dist;
		 });
	int answer = 0;
	int farst = Nodes[orders[0]].Dist;
	for (int idx : orders) {
		if (farst == Nodes[idx].Dist) answer++;
		else break;
	}
	return answer;
}

int solutionfarstnodetest02(int n, vector<vector<int>> edge) {
	int answer = 0;

	return answer;
}
}
///////////////////////// 참고 // 

///////////////////////// 참고
namespace cardscompare
{

vector<string> solutioncard(vector<string> card, vector<string> word) {
	function<void(string&, map<char, int>&)> mapping = [](string& str, map<char, int>& wordmap) {
		for (int j = 0; j < str.length(); ++j) {
			wordmap[str[j]]++;
		}
	};
	vector<map<char, int>> bases(card.size());
	for (int i = 0; i < card.size(); ++i) {
		string& str = card[i];
		map<char, int>& base = bases[i];
		mapping(str, base);
	}

	vector<string> answer = {};
	for (string& w : word) {
		map<char, int> wordmap;
		mapping(w, wordmap);
		vector<bool> uses(bases.size(), false);
		bool noneany = false;
		for (char c : w) {
			bool found = false;
			for (int i = 0; i < bases.size(); ++i) {
				map<char, int>& base = bases[i];
				int count = base[c];
				if (0 == count) continue;
				if (count - wordmap[c] >= 0) {
					found = true;
					uses[i] = true;
					break;
				}
			}
			if (false == found) {
				noneany = true;
				break;
			}
		}
		if (true == noneany) continue;
		bool alluse = find(uses.begin(), uses.end(), false) == uses.end();
		if (true == alluse) {
			answer.push_back(w);
		}
	}

	return answer;
}
}
///////////////////////// 참고 //

///////////////////////// 참고
long long solutionrobotrail(string block, int pos) {
	std::function<int(char&)> getdir = [](char& c) {
		if (c == '>') { c = '<'; return 1; }
		c = '>';
		return -1;
	};
	long long answer = 0;
	int cur = pos - 1;
	while (true) {
		char c = block[cur];
		int nextcur = getdir(c);
		block[cur] = c;
		cur = cur + nextcur;
		cout << "next:" << cur << "/" << block << endl;
		++answer;
		if ((cur >= block.length() && block.back() == '<')
			|| (cur <= -1 && block.front() == '>')) {
			break;
		}
	}
	return answer;
}
///////////////////////// 참고 //

///////////////////////// 참고
#include <string>
#include <vector>
#include <cmath>

namespace quadtreestring
{
struct CNode {
	int Idx;
	int IdxParent = -1;
	int Depth = 0;
	char State = 'n';
	vector<int> Childs;
	bool IsRoot() { return IdxParent == -1; }
	int GetSize() { return std::pow(32 / (Depth + 1), 2); }
	void Set(char state, int depth, int parent) { State = state; Depth = depth; IdxParent = parent; }
};
vector<CNode> N1;
vector<CNode> N2;
vector<CNode> N3;
void SetNodesR(vector<CNode>& nodes, string& s, int cur, int parent, int depth) {
	char state = s[cur];
	nodes[cur].Set(state, depth, parent);
	if (state == 'b' || state == 'w') {
		return;
	}
	nodes[cur].Childs.resize(4);
	for (int i = 1; i <= 4; ++i) {
		int idxnext = cur + i;
		nodes[cur].Childs[i - 1] = idxnext;
		SetNodesR(nodes, s, idxnext, cur, depth + 1);
	}
}
void SetNodes(string& s, vector<CNode>& nodes) {
	nodes[0].Set(s[0], 1, -1);
	SetNodesR(nodes, s, 1, 0, 0);
}
int solutionquadtree(string S1, string S2) {
	N1.resize(S1.length());
	N2.resize(S2.length());
	SetNodes(S1, N1);
	SetNodes(S2, N2);
	int answer = 0;
	return answer;
}
}
///////////////////////// 참고 //

///////////////////////// 참고
/* 스택 / 큐 : 다리를 지나는 트럭 */
namespace truck
{
#include <string>
#include <vector>
#include <queue>
#include <iostream>
#include <map>

struct Truck {
	int W = 0;
	int Idx = 0;
	int T = 0;
	Truck(int w, int idx) { W = w; Idx = idx; }
	Truck(Truck& o, int t) { W = o.W; Idx = o.Idx; T = t; }
};
int solution(int bridge_length, int weight, vector<int> truck_weights) {
	int answer = 0;
	queue<Truck> queue01, queue02;
	for (int i = 0; i < truck_weights.size(); ++i) {
		int w = truck_weights[i];
		queue01.push(Truck(w, i));
	}
	int w = 0, len = bridge_length;
	cout << " 01 : " << queue01.size() << " /02 : " << queue02.size() << endl;
	while (true != queue01.empty() || true != queue02.empty()) {
		bool ispoped = false;
		if (queue02.size() >= 1 && answer >= queue02.front().T) {
			w = w - queue02.front().W;
			cout << " pop 02 T : " << (queue02.front().T) << endl;
			queue02.pop();
			ispoped = true;
		}

		if (true != queue01.empty() && w + queue01.front().W <= weight) {
			w += queue01.front().W;
			cout << " push 02 T : " << (answer + len) << endl;
			queue02.push(Truck(queue01.front(), answer + len));
			queue01.pop();
		}
		answer++;
	}
	return answer;
}
}
///////////////////////// 참고 //

///////////////////////// 참고
/* 스택 / 큐 : 프린터 */
namespace printer
{
#include <string>
#include <vector>
#include <queue>
#include <algorithm>

struct Pr {
	int P = -1;
	int Idx = -1;
	Pr(int p, int idx) { P = p; Idx = idx; }
};
int solution(vector<int> priorities, int location) {
	priority_queue<int> pqueue;
	queue<Pr> queue;
	for (int i = 0; i < priorities.size(); ++i) {
		queue.push(Pr(priorities[i], i));
		pqueue.push(priorities[i]);
	}

	int answer = 0;
	while (queue.empty() != true) {
		Pr pr = queue.front();
		queue.pop();

		if (pr.P == pqueue.top()) {
			pqueue.pop();
			answer++;

			if (pr.Idx == location) {
				break;
			}
		}
		else {
			queue.push(pr);
		}
	}
	return answer;
}
}
///////////////////////// 참고 //

namespace sumint
{
#include <string>
#include <vector>
#include <algorithm>

void GetCombsR(const vector<int>& nums,
			   int depth,
			   int sum,
			   int target,
			   vector<int> stack,
			   vector<bool>& visits,
			   vector<vector<int>>& combs) {
	if (depth >= nums.size()) return;
	if (stack.size() >= 2) return;
	for (int i = 0; i < nums.size(); ++i) {
		if (true == visits[i]) continue;
		visits[i] = true;
		int sumnext = sum + nums[i];
		if (sumnext > target) continue;
		vector<int> stacknew = stack;
		stacknew.push_back(i);
		if (sumnext == target) {
			combs.push_back(stacknew);
			continue;
		}
		GetCombsR(nums, depth + 1, sumnext, target, stacknew, visits, combs);
		visits[i] = false;
	}
}

void GetCombs(const vector<int>& nums, vector<vector<int>>& combs, int target) {
	vector<bool> visits(nums.size(), false);
	vector<int> stack;
	int sum = 0, depth = 0; 
	GetCombsR(nums, depth, sum, target, stack, visits, combs);
}

vector<int> solution(vector<int> nums, int target) {
	vector<vector<int>> combs;
	GetCombs(nums, combs, target);
	vector<int> answer;
	sort(combs.begin(), combs.end());

	if (combs.size() >= 1){
		answer = combs[0];
	}
	return answer;
}
}

namespace operatorstring
{
#include <string>
#include <vector>

int GetOp(char op, int num, int sum) {
	switch (op) {
	case '+':
	sum += num; break;
	case '-':
	sum -= num; break;
	case '*':
	sum *= num; break;
	case '/':
	sum /= num; break;
	}
	return sum;
}
int GetNum(char c) { return c - '0'; }
bool IsNum(char c) { return c >= '0' && c <= '9'; }
bool IsDivByZero(char op, int num) { return op == '/' && num == 0; }
string solution(string input) {
	int sum = GetNum(input[0]);
	string buf;
	for (int i = 1; i < input.length(); i = i + 2) {
		char op = input[i];
		int num = GetNum(input[i+1]);
		if (true == IsDivByZero(op, num))
		{
			return "Impossible";
		}
		sum = GetOp(op, num, sum);
	}
	string answer = to_string(sum);
	return answer;
}
}

namespace landarea
{
#include <string>
#include <vector>

struct Area {
	int W = 0, H = 0;
	int idxW = 0, idxH = 0;
	bool IsSameSize(Area& o) { return (W == o.H && H == o.W) || (W == o.W && H == o.H); }
	Area(int h, int w) { W = w; H = h; }
};

int solution(vector<int> buildingSize, vector<vector<int>> land) {
	for (int w = 0; w < land.size(); ++w) {
		vector<int>& vers = land[w];
		for (int h = 0; h < vers.size(); ++h) {
			int state = land[w][h];
			if (state == 1) continue;

		}
	}
	int answer = 0;
	return answer;
}
}

int main()
{
	//vector<string> phone_book = { "123","1235","12","567","88" };
	//solution_phone_book(phone_book);

	//vector<int> array = { 1, 5, 2, 6, 3, 7, 4 };
	//vector<vector<int>> commands = { {2, 5, 3}, {4, 4, 1}, {1, 7, 3} };
	//solutionsort01(array, commands);

	//vector<int> array = { 1, 25, 2, 26, 3, 7, 34, 34343, 3434,3434343 };
	//solutionhighestnumber(array);
	
	//string numfindprime = "7025361";
	//string numfindprime = "17";
	//string numfindprime = "702";
	string numfindprime = "011038";
	primefind::solution(numfindprime);

	//vector<int> numbers = { 1, 1, 1, 1, 1 };
	//int target = 3;
	//solutiontargetnumbertest(numbers, target);

	//vector<vector<int>> computers = {{1, 1, 0}, {1, 1, 0}, {0, 0, 1}};
	//int n = 3;
	//solutionnetwork(n, computers);

	//vector<string> words = { "hot", "dot", "dog", "lot", "log", "cog" };
	//string begin = "hit";
	//string target = "cog";
	//solutionwordsimilar(begin, target, words);

	//vector<string> card = { "ABACDEFG", "NOPQRSTU", "HIJKLKMM" };
	//vector<string> word = { "GPQM", "GPMZ", "EFU", "MMNA" };
	//solutioncard(card, word);

	//string block = ">><";
	//string block = ">><>>";
	//int pos = 2;
	//solutionrobotrail(block, pos);
	
	//string S1 = "ppwwwbpbbwwbw";
	//string S2 = "pwbwpwwbw";
	//quadtreestring::solutionquadtree(S1, S2);

	//int bridge_length = 2;
	//int weight = 10;
	//vector<int> truck_weights = { 7,4,5,6 };
	//truck::solution(bridge_length, weight, truck_weights);

	//int location = 5;
	////vector<int> priorities = { 2,1,3,2 };
	//vector<int> priorities = { 1,1,9,1,1,1 };
	//printer::solution(priorities, location);

	//vector<int> nums = { 1, 2, 3, 4, 5 };
	//int target = 6;
	//sumint::solution(nums, target);
	//string input = "2+3";
	//operatorstring::solution(input);

	//vector<int> buildingSize;
	//vector<vector<int>> land;
	//landarea::solution(buildingSize, land);

	return 0;
}