#include "Strategy.h"
#include "KnowledgeBase.h"
#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <regex>

using namespace std;

TruthTable::TruthTable() : modelsCount(0) {}

int TruthTable::getModelsCount() const
{
	return modelsCount;
}

void TruthTable::increaseModelsCount()
{
	modelsCount += 1;
}


void TruthTable::CheckConclusionsFromPremises(KnowledgeBase& kb)
{
	for (vector<string> separatedStatement : getSeparatedStatements()) {
		vector<string> kbSymbols = kb.getSymbols();
		if (find(separatedStatement.begin(), separatedStatement.end(), "&") != separatedStatement.end()) {
			separatedStatement.erase(remove(separatedStatement.begin(), separatedStatement.end(), "&"), separatedStatement.end());
		}
		ptrdiff_t implicationSymbolPosition = distance(separatedStatement.begin(), find(separatedStatement.begin(), separatedStatement.end(), "=>"));
		vector<string> premise = vector<string>(separatedStatement.begin(), separatedStatement.begin() + implicationSymbolPosition);
		for (string p : premise) {
			if (find(kbSymbols.begin(), kbSymbols.end(), p) != kbSymbols.end()) {	
				premise.erase(remove(premise.begin(), premise.end(), p), premise.end());
			}
		}
		if (empty(premise)) {
			kb.insertSymbol(separatedStatement[implicationSymbolPosition + 1]);
			increaseModelsCount();
			if (separatedStatement[implicationSymbolPosition + 1] == kb.getQuery()) {
				PrintSuccessfulResult();
				return;
			}
		}
	}
	PrintUnsuccessfulResult();
	return;
}

void TruthTable::PrintSuccessfulResult() const
{
	int modelsCount = getModelsCount();
	cout << "YES: " << modelsCount << endl;
}

