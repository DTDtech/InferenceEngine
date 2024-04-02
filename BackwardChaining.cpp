#include "Strategy.h"
#include "KnowledgeBase.h"
#include <string>
#include <vector>
#include <iostream>
#include <regex>

using namespace std;

BackwardChaining::BackwardChaining() {}

void BackwardChaining::addSymbol(string symbol)
{
	symbolsAdded.push_back(symbol);
}

vector<string> BackwardChaining::getAddedSymbols() const
{
	return symbolsAdded;
}

void BackwardChaining::AddPremisesFromQuery(KnowledgeBase& kb)
{
	vector<vector<string>> separatedStatementsList = getSeparatedStatements();
	for (vector<string> separatedStatement : separatedStatementsList) {
		ptrdiff_t implicationSymbolPosition = distance(separatedStatement.begin(), find(separatedStatement.begin(), separatedStatement.end(), "=>"));
		if (separatedStatement[implicationSymbolPosition + 1] == kb.getQuery()) {
			vector<string> premise = vector<string>(separatedStatement.begin(), separatedStatement.begin() + implicationSymbolPosition);
			vector<string> premiseHolder = premise;
			vector<string> kbSymbols = kb.getSymbols();
			for (string p : premise) {
				if (find(kbSymbols.begin(), kbSymbols.end(), p) != kbSymbols.end()) {
					premise.erase(remove(premise.begin(), premise.end(), p), premise.end());
				}
				if (empty(premise)) {
					addSymbol(separatedStatement[implicationSymbolPosition + 1]);
					PrintSuccessfulResult();
					return;
				}
				else {
					premise = premiseHolder;
					if (Find_Statement_Matching_With_Symbols(premise, separatedStatementsList, kb)) {
						addSymbol(separatedStatement[implicationSymbolPosition + 1]);
						PrintSuccessfulResult();
						return;
					}
					else {
						PrintUnsuccessfulResult();
						return;
					}
				}
			}
		}
	}
	PrintUnsuccessfulResult();
	return;
}

bool BackwardChaining::Find_Statement_Matching_With_Symbols(vector<string> unEstablishedPremise, vector<vector<string>>& separatedStatementsList, KnowledgeBase& kb)
{
	vector<vector<string>> initialSeparatedStatementsList;
	vector<string> premise = unEstablishedPremise;
	vector<string> kbSymbols = kb.getSymbols();

	for (vector<string> separatedStatement : separatedStatementsList) {
		for (string p : premise) {
			if (separatedStatement.back() == p) {
				ptrdiff_t matching_Statement_Implication_Symbol_Position = distance(separatedStatement.begin(), find(separatedStatement.begin(), separatedStatement.end(), "=>"));
				vector<string> matching_Statement_Premise = vector<string>(separatedStatement.begin(), separatedStatement.begin() + matching_Statement_Implication_Symbol_Position);
				vector<string> matching_Statement_Premise_Holder = matching_Statement_Premise;
				for (string m : matching_Statement_Premise) {
					if (find(kbSymbols.begin(), kbSymbols.end(), m) != kbSymbols.end()) {
						matching_Statement_Premise.erase(remove(matching_Statement_Premise.begin(), matching_Statement_Premise.end(), m), matching_Statement_Premise.end());
					}
				}
				if (empty(matching_Statement_Premise)) {
					matching_Statement_Premise = matching_Statement_Premise_Holder;
					for (string matchedSymbol : matching_Statement_Premise) {
						addSymbol(matchedSymbol);
					}
					addSymbol(p);
					return true;
				}
				else {
					if (Find_Statement_Matching_With_Symbols(matching_Statement_Premise, separatedStatementsList, kb)) {
						addSymbol(p);
					}
				}
			}
		}
		if (initialSeparatedStatementsList == separatedStatementsList) {
			return false;
		}
	}
	return true;
}

void BackwardChaining::PrintSuccessfulResult() const {
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



