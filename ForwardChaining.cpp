#include "Strategy.h"
#include "KnowledgeBase.h"
#include <string>
#include <vector>
#include <iostream>
#include <regex>

using namespace std;

bool ForwardChaining::AddConclusionsFromPremises(KnowledgeBase& kb)
{
	for (vector<string> separatedStatement : getSeparatedStatements()) {
		if (find(separatedStatement.begin(), separatedStatement.end(), "=>") != separatedStatement.end()) {
			ptrdiff_t implicationSymbolPosition = distance(separatedStatement.begin(), find(separatedStatement.begin(), separatedStatement.end(), "=>"));

			if (count(separatedStatement.begin(), separatedStatement.end(), "&") > 0) {
				ptrdiff_t firstConjunctionSymbolPosition = distance(separatedStatement.begin(), find(separatedStatement.begin(), separatedStatement.end(), "&"));
				if (count(separatedStatement.begin(), separatedStatement.end(), "&") > 1) {

				}
				vector<string> propositionalSymbolList = kb.getSymbols();
				if (find(propositionalSymbolList.begin(), propositionalSymbolList.end(), separatedStatement[firstConjunctionSymbolPosition - 1]) != propositionalSymbolList.end()
					&& find(propositionalSymbolList.begin(), propositionalSymbolList.end(), separatedStatement[firstConjunctionSymbolPosition + 1]) != propositionalSymbolList.end()) {
						
					}
			}

		}
	}
	return false;	
}




