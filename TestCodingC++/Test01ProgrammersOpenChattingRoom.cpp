https://school.programmers.co.kr/learn/courses/30/lessons/42888

#include <string>
#include <vector>
#include <map>
#include <iostream>

using namespace std;

struct Record {
	string Id;
	char Stat;
	void Set(string& id, char stat) { Id = id; Stat = stat; }
};

vector<string> solution(vector<string> records) {
	map<string, string> ids;
	map<char, string> msgs = {
		{'E', "님이 들어왔습니다."},
		{'L', "님이 나갔습니다."},
	};
	vector<Record> Rs(records.size());
	char stat; string name, id;
	for (int i = 0; i < records.size(); ++i) {
		string& r = records[i];
		vector<string> strs; string str; stat = 'L';
		for (int j = 0; j < r.size(); ++j) {
			char c = r[j];
			if (c == ' ') { strs.push_back(str); str.clear(); continue; }
			str += c;
			if (j == r.size() - 1) { strs.push_back(str); }
		}
		stat = strs[0][0];
		id = strs[1];
		if (stat == 'E' || stat == 'C') {
			name = strs[2];
			ids[id] = name;
		}
		Rs[i].Set(id, stat);
		//cout << " record:" << i << ":" << id << "/" << name << "/" << stat << endl;
	}

	vector<string> ans;
	for (int i = 0; i < Rs.size(); ++i) {
		Record& r = Rs[i];
		if (r.Stat == 'C') continue;
		string msg = ids[r.Id] + msgs[r.Stat];
		//cout << msg << endl;
		ans.push_back(msg);
	}
	return ans;
}
