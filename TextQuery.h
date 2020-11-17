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
		 while (std::getline(ifs, text)) {//处理每一行
			 file->push_back(text);//保存文本
			 int n = file->size() - 1;

			 std::istringstream iss(text);
			 std::string word;
			 while (iss >> word) {//处理每一单词
				 //若单词不在wm中，添加一项
				 //auto lines = wm.find(word);//得到一个wm的迭代器
				 //if (lines==wm.end())//若wm中无此单词，则lines指向wm.end(),需要为该shared_ptr分配对象
					// lines->second.reset(new std::set<line_no>);
				 //lines->second->insert(n);
				 auto& lines = wm[word];//一定要写成引用auto &,这样才能通过share_ptr改变set
				 if (!lines)
					 lines.reset(new std::set<line_no>);
				 lines->insert(n);
			 }
		 }
	 }
	~TextQuery() = default;
	
	QueryResult query(const std::string & s)const;

private:
	std::shared_ptr<std::vector<std::string>> file;//指向输入文件的智能指针,存输入文件的vector以行为单位
	std::map<std::string, std::shared_ptr<std::set<line_no>>> wm;//每个单词和它出现在的行号，之间的映射
};

QueryResult TextQuery::query(const std::string& s)const {
	//在wm中查找是否有对应的set的指针(map迭代器)，若没有，返回的指针等于wm.end()
	auto loc = wm.find(s);
	//若没有，返回一个指向此set的指针
	static std::shared_ptr<std::set<line_no>> nodata (new std::set<line_no>);
	if (loc == wm.end())//若wm中没存该单词的行号
		return QueryResult(s, file, nodata);
	else
		return QueryResult(s, file, loc->second);
 }

#endif // !TEXTQUERY_H