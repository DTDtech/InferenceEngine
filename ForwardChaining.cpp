#include "Strategy.h"
#include "KnowledgeBase.h"
#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <regex>

using namespace std;

void ForwardChaining::addSymbol(string symbol)
{
	symbolsAdded.push_back(symbol);
}

vector<string> ForwardChaining::getAddedSymbols()
{
	return symbolsAdded;
}


bool ForwardChaining::AddConclusionsFromPremises(KnowledgeBase& kb)
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
				if (premise.empty()) {
					kb.insertSymbol(separatedStatement[implicationSymbolPosition + 1]);
					addSymbol(separatedStatement[implicationSymbolPosition + 1]);
					if (separatedStatement[implicationSymbolPosition + 1] == kb.getQuery()) {
						PrintSuccessfulResult();
						return true;
					}
				}
				else {
					invalidStatements.insert(pair<vector<string>, string>(premise, separatedStatement[implicationSymbolPosition + 1]));
				}
			}
		}
	}
	if (!empty(invalidStatements)) {
		if (RecheckInvalidStatements(invalidStatements, kb)) {
			PrintSuccessfulResult();
			return true;
		}
		else {
			PrintUnsuccessfulResult();
			return false;
		}
	}
	else {
		PrintUnsuccessfulResult();
		return false;
	}

}

bool ForwardChaining::RecheckInvalidStatements(map<vector<string>, string>& invalidStatements, KnowledgeBase& kb)
{
	map<vector<string>, string> initialInvalidStatements = invalidStatements;
	for (map<vector<string>, string>::iterator it = invalidStatements.begin(); it != invalidStatements.end();) {
		vector<string> premise = it->first;
		string conclusion = it->second;
		for (string s : kb.getSymbols()) {
			if (find(premise.begin(), premise.end(), s) != premise.end()) {
				premise.erase(remove(premise.begin(), premise.end(), s), premise.end());
				if (premise.empty()) {
					kb.insertSymbol(conclusion);
					addSymbol(conclusion);
					it = invalidStatements.erase(it);
					if (conclusion == kb.getQuery()) {
						return true;
					}
				}
				else {
					it++;
				}
			}
		}
	}
	if (initialInvalidStatements == invalidStatements) {
		return false;
	}
	else {
		RecheckInvalidStatements(invalidStatements, kb);
	}
}

void ForwardChaining::PrintSuccessfulResult() const {
	cout << "YES: ";
	for (string s : symbolsAdded) {
		if (s != symbolsAdded[symbolsAdded.size() - 1]) {
			cout << s << ", ";
		} 
		else {
			cout << s;
		}
		
	}
}



