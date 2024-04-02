#include "Strategy.h"
#include "KnowledgeBase.h"
#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <regex>

using namespace std;

ForwardChaining::ForwardChaining() {}

void ForwardChaining::addSymbol(string symbol)
{
	symbolsAdded.push_back(symbol);
}

vector<string> ForwardChaining::getAddedSymbols() const
{
	return symbolsAdded;
}

void ForwardChaining::AddConclusionsFromPremises(KnowledgeBase& kb)
{
	std::map<std::vector<std::string>, std::string> invalidStatements;
	for (vector<string> separatedStatement : getSeparatedStatements()) {
		if (find(separatedStatement.begin(), separatedStatement.end(), "&") != separatedStatement.end()) {
			separatedStatement.erase(remove(separatedStatement.begin(), separatedStatement.end(), "&"), separatedStatement.end());
		}
		ptrdiff_t implicationSymbolPosition = distance(separatedStatement.begin(), find(separatedStatement.begin(), separatedStatement.end(), "=>"));
		vector<string> premise = vector<string>(separatedStatement.begin(), separatedStatement.begin() + implicationSymbolPosition);
		for (string s : kb.getSymbols()) {
			vector<string> symbolList = getAddedSymbols();
			if (find(symbolList.begin(), symbolList.end(), s) == symbolList.end()) {
				addSymbol(s);
			}
			if (find(premise.begin(), premise.end(), s) != premise.end()) {
				premise.erase(remove(premise.begin(), premise.end(), s), premise.end());
			}
		}
		if (premise.empty()) {
			kb.insertSymbol(separatedStatement[implicationSymbolPosition + 1]);
			addSymbol(separatedStatement[implicationSymbolPosition + 1]);
			if (separatedStatement[implicationSymbolPosition + 1] == kb.getQuery()) {
				PrintSuccessfulResult();
				return;
			}
		}
		else {
			invalidStatements.insert(pair<vector<string>, string>(premise, separatedStatement[implicationSymbolPosition + 1]));
		}
	}
	if (!invalidStatements.empty()) {
		if (RecheckInvalidStatements(invalidStatements, kb)) {
			PrintSuccessfulResult();
			return;
		}
		else {
			PrintUnsuccessfulResult();
			return;
		}
	}
	else {
		PrintUnsuccessfulResult();
		return;
	}
	PrintUnsuccessfulResult();
	return;
}

bool ForwardChaining::RecheckInvalidStatements(map<vector<string>, string>& invalidStatements, KnowledgeBase& kb)
{
	map<vector<string>, string> initialInvalidStatements = invalidStatements;
	map<vector<string>, string>::iterator it;
	for (it = invalidStatements.begin(); it != invalidStatements.end();) {
		vector<string> premise = it->first;
		string conclusion = it->second;
		for (string s : kb.getSymbols()) {
			if (find(premise.begin(), premise.end(), s) != premise.end()) {
				premise.erase(remove(premise.begin(), premise.end(), s), premise.end());
			}
		}
		if (empty(premise)) {
			kb.insertSymbol(conclusion);
			addSymbol(conclusion);
			if (conclusion == kb.getQuery()) {
				return true;
			}
			it = invalidStatements.erase(it);
		}
		else {
			++it;
		}
	}
	if (initialInvalidStatements == invalidStatements) {
		return false;
	}

	return RecheckInvalidStatements(invalidStatements, kb);
}

void ForwardChaining::PrintSuccessfulResult() const {
	cout << "YES: ";
	vector<string> addedSymbols = getAddedSymbols();
	for (string s : addedSymbols) {
		if (s != addedSymbols[addedSymbols.size() - 1]) {
			cout << s << ", ";
		}
		else {
			cout << s << endl;
		}

	}
}



