#include "Strategy.h"
#include "KnowledgeBase.h"
#include <string>
#include <vector>
#include <iostream>
#include <regex>

using namespace std;

bool TruthTable::CheckConclusionsFromPremises(KnowledgeBase& kb)
{
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