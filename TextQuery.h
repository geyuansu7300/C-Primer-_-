#ifndef TEXTQUERY_H
#define TEXTQUERY_H

#include<iostream>
#include<vector>
#include<map>
#include<set>
#include<string>
#include<fstream>
#include<sstream>
#include<memory>
#include"QueryResult.h"

class  TextQuery{
public:
	using line_no=std::vector<std::string>::size_type;
	 TextQuery()=default;
	 TextQuery(std::ifstream& ifs) :file(new std::vector<std::string>) {
		 std::string text;
		 while (std::getline(ifs, text)) {//����ÿһ��
			 file->push_back(text);//�����ı�
			 int n = file->size() - 1;

			 std::istringstream iss(text);
			 std::string word;
			 while (iss >> word) {//����ÿһ����
				 //�����ʲ���wm�У����һ��
				 //auto lines = wm.find(word);//�õ�һ��wm�ĵ�����
				 //if (lines==wm.end())//��wm���޴˵��ʣ���linesָ��wm.end(),��ҪΪ��shared_ptr�������
					// lines->second.reset(new std::set<line_no>);
				 //lines->second->insert(n);
				 auto& lines = wm[word];//һ��Ҫд������auto &,��������ͨ��share_ptr�ı�set
				 if (!lines)
					 lines.reset(new std::set<line_no>);
				 lines->insert(n);
			 }
		 }
	 }
	~TextQuery() = default;
	
	QueryResult query(const std::string & s)const;

private:
	std::shared_ptr<std::vector<std::string>> file;//ָ�������ļ�������ָ��,�������ļ���vector����Ϊ��λ
	std::map<std::string, std::shared_ptr<std::set<line_no>>> wm;//ÿ�����ʺ��������ڵ��кţ�֮���ӳ��
};

QueryResult TextQuery::query(const std::string& s)const {
	//��wm�в����Ƿ��ж�Ӧ��set��ָ��(map������)����û�У����ص�ָ�����wm.end()
	auto loc = wm.find(s);
	//��û�У�����һ��ָ���set��ָ��
	static std::shared_ptr<std::set<line_no>> nodata (new std::set<line_no>);
	if (loc == wm.end())//��wm��û��õ��ʵ��к�
		return QueryResult(s, file, nodata);
	else
		return QueryResult(s, file, loc->second);
 }

#endif // !TEXTQUERY_H