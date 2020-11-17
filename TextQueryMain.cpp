#include<iostream>
#include<fstream>
#include"QueryResult.h"
#include"TextQuery.h"
#include"QueryResult.h"

using namespace std;

void runQueries(ifstream& infile);
ostream& print(ostream& os, const QueryResult& qr);

int main() {
	ifstream ifs("C:\\Users\\��Ӣ��\\Desktop\\c++��������.txt");
	runQueries(ifs);
}

//int judgeNull(const shared_ptr<set<vector<std::string>::size_type>> &ptr) {
//	if (!ptr->size())//��Ϊ��
//		return -1;
//	else
//		return ptr->size();
//}

ostream& print(ostream& os, const QueryResult& qr) {
	os << qr.sought << " occurs " << qr.lines->size() << " times" << endl;
	//��ӡÿ�е���
	for (auto m : *qr.lines) {
		os << "(line " << m + 1 << ") " << (*qr.file)[m] << endl;
	}
	return os;
}

void runQueries(ifstream& infile) {

	//���ļ�infile��ʼ��TextQuery
	TextQuery tq(infile);
	while (true) {
		cout << "enter word to look for,or q to quit" << endl;
		string s;
		if (!(cin >> s) || s == "q")
			break;
		print(cout, tq.query(s));
	}
}

