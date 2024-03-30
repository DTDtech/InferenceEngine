#pragma once
#include <string>
#include <vector>

class KnowledgeBase {
public:
	KnowledgeBase();
	std::vector<std::string> getStatements();
	void insertStatement(std::string statement);

	std::vector<std::string> getSymbols();
	void insertSymbol(std::string symbol);

	std::string getQuery();
	void setQuery(std::string queryFromAsk);
	
private: 
	std::vector<std::string> statements;
	std::vector<std::string> symbols;
	std::string query;
};