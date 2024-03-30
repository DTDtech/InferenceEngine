#include "KnowledgeBase.h"
#include <string>
#include <vector>
using namespace std;

KnowledgeBase::KnowledgeBase() : statements(vector<string>(0)) {}

vector<string> KnowledgeBase::getStatements() {
	return statements;
}

void KnowledgeBase::insertStatement(std::string statement) {
	statements.push_back(statement);
}

vector<string> KnowledgeBase::getSymbols() {
	return symbols;
}

void KnowledgeBase::insertSymbol(string symbol) {
	symbols.push_back(symbol);
}

string KnowledgeBase::getQuery() {
	return query;
}

void KnowledgeBase::setQuery(string queryFromAsk) {
	query = queryFromAsk;
}