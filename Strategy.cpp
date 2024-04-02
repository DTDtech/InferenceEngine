#include "Strategy.h"
#include "KnowledgeBase.h"
#include <string>
#include <vector>
#include <iostream>
#include <regex>

using namespace std;

void Strategy::insertSeparatedStatement(std::vector<std::string>& separatedStatement) {
	separatedStatements.push_back(separatedStatement);
}

std::vector<std::vector<std::string>> Strategy::getSeparatedStatements() {
	return separatedStatements;
}

bool Strategy::Separate_Statement_Into_Symbols_And_Connectives(KnowledgeBase& kb) {
	regex filter_By_Implication_Pattern("(.*)(=>)(.*)");
	regex filter_By_Conjuction_Pattern("(&)");
	regex filter_Numeric_Characters_Pattern("^[a-z]{1}[0-9]{0,1}$");

	vector<string>::iterator statementIterator;
	sregex_token_iterator endOfString;

	vector<string> statementsHolder = kb.getStatements();	

	for (statementIterator = statementsHolder.begin(); statementIterator != statementsHolder.end();) {
		if ((*statementIterator).find("=>")) {
			vector<string> separatedStatement;
			vector<string> separated_Statements_Without_Conjunction;
			int submatches[] = { 1, 3 };
			sregex_token_iterator symbol_Separated_By_Implication_Iterator((*statementIterator).begin(), (*statementIterator).end(), filter_By_Implication_Pattern, submatches);
			while (symbol_Separated_By_Implication_Iterator != endOfString) {
				string clause = *symbol_Separated_By_Implication_Iterator;
				if (clause.find("&") != clause.npos) {
					sregex_token_iterator symbol_Separated_By_Conjunction_Iterator(clause.begin(), clause.end(), filter_By_Conjuction_Pattern, -1);

					while (symbol_Separated_By_Conjunction_Iterator != endOfString) {
						if (!regex_match((*symbol_Separated_By_Conjunction_Iterator).str(), filter_Numeric_Characters_Pattern)) {
							cout << "Input file knowledge base must only contain valid proposition statements and proposition symbols." << endl;
							return false;
						}
						else {
							separatedStatement.push_back(*symbol_Separated_By_Conjunction_Iterator++);
							if (symbol_Separated_By_Conjunction_Iterator != endOfString) {
								separatedStatement.push_back("&");
							}
						}
					}
				}
				else {
					if (regex_match((*symbol_Separated_By_Implication_Iterator).str(), filter_Numeric_Characters_Pattern)) {
						separatedStatement.push_back(*symbol_Separated_By_Implication_Iterator);
					}
					else {
						cout << "Input file knowledge base must only contain valid proposition statements and proposition symbols." << endl;
						return false;
					}
				}
				symbol_Separated_By_Implication_Iterator++;
				if (symbol_Separated_By_Implication_Iterator != endOfString) {
					separatedStatement.push_back("=>");
				}
			}
			insertSeparatedStatement(separatedStatement);
			statementIterator = statementsHolder.erase(statementIterator);
		}

	}

	return true;
}

void Strategy::PrintUnsuccessfulResult()
{
	cout << "NO" << endl;
}

