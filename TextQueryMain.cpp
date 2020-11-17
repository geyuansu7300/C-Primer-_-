#include<iostream>
#include<fstream>
#include"QueryResult.h"
#include"TextQuery.h"
#include"QueryResult.h"

using namespace std;

void runQueries(ifstream& infile);
ostream& print(ostream& os, const QueryResult& qr);

int main() {
	ifstream ifs("C:\\Users\\陈英俊\\Desktop\\c++测试样例.txt");
	runQueries(ifs);
}

//int judgeNull(const shared_ptr<set<vector<std::string>::size_type>> &ptr) {
//	if (!ptr->size())//若为空
//		return -1;
//	else
//		return ptr->size();
//}

ostream& print(ostream& os, const QueryResult& qr) {
	os << qr.sought << " occurs " << qr.lines->size() << " times" << endl;
	//打印每行单词
	for (auto m : *qr.lines) {
		os << "(line " << m + 1 << ") " << (*qr.file)[m] << endl;
	}
	return os;
}

void runQueries(ifstream& infile) {

	//用文件infile初始化TextQuery
	TextQuery tq(infile);
	while (true) {
		cout << "enter word to look for,or q to quit" << endl;
		string s;
		if (!(cin >> s) || s == "q")
			break;
		print(cout, tq.query(s));
	}
}

