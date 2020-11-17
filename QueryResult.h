#ifndef QUERYRESULT_H
#define QUERYRESULT_H

#include<iostream>
#include<string>
#include<vector>
#include<set>


class QueryResult{
public:
	friend std::ostream & print(std::ostream&, const QueryResult&);
	using line_no = std::vector<std::string>::size_type;
	QueryResult() = default;
	QueryResult(std::string s,
		std::shared_ptr<std::vector<std::string>> file, std::shared_ptr<std::set<line_no>> lines) :sought(s), file(file), lines(lines) {
	}
	~QueryResult() = default;
private:
	std::string  sought;//��ѯ�ĵ���
	std::shared_ptr<std::vector<std::string>> file;//�����ļ�
	std::shared_ptr<std::set<line_no>> lines;//�к�
};

#endif // !QUERYRESULT_H

