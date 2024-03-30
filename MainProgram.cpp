#include "KnowledgeBase.h"
#include "Strategy.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <regex>


using namespace std;

bool Insert_Input_To_KnowledgeBase(string fileName, KnowledgeBase& kb) {
	ifstream fileStream(fileName);
	if (fileStream.is_open()) {
		string line;
		regex filter_Numeric_Characters_Pattern("^[A-Za-z]{1}[0-9]{0,1}$");
		vector<string> propositions;
		vector<string>::iterator it;

		while (getline(fileStream, line)) {
			if (line.find("TELL") != line.npos) {
				getline(fileStream, line);
				line.erase(remove(line.begin(), line.end(), ' '), line.end());
				string delimiter = ";";
				do {
					size_t delimiterPosition = line.find(delimiter);
					string statement = line.substr(0, delimiterPosition);
					propositions.push_back(statement);
					line = line.substr(delimiterPosition + delimiter.length());
				} while (line.find(delimiter) != line.npos);

				for (it = propositions.begin(); it != propositions.end();) {
					if ((*it).find("=>") != (*it).npos || (*it).find("&") != (*it).npos) {
						kb.insertStatement(*it);
						it = propositions.erase(it);
					}
					else if (regex_match((*it), filter_Numeric_Characters_Pattern)) {
						kb.insertSymbol(*it);
						it = propositions.erase(it);
					}
					else {
						cout << "Input file knowledge base must only contain proposition statements and proposition symbols." << endl;
						return false;
					}
				}
			}
			else if (line.find("ASK") != line.npos) {
				getline(fileStream, line);			
				line.erase(remove(line.begin(), line.end(), ' '), line.end());
				if (regex_match(line, filter_Numeric_Characters_Pattern)) {
					kb.setQuery(line);
				}
				else {
					cout << "Query must contain one valid propositional symbol." << endl;
					return false;
				}
			}
		}
	}
	fileStream.close();
	return true;
}

int main() {
	string fileName = "test_HornKB.txt";
	//vector<vector<string>> initial_Separated_Statement_List(0, vector<string>(0));
	KnowledgeBase kb;
	//TruthTable truthTable;
	ForwardChaining fc;
	if (Insert_Input_To_KnowledgeBase(fileName, kb)) {
		if (fc.Separate_Statement_Into_Symbols_And_Connectives(kb)) {
			fc.AddConclusionsFromPremises(kb);
		}
		else {
			return -1;
		}
		/*for (vector<string> s : fc.getSeparatedStatements()) {
			for (string sf : s) {
				cout << sf;
			}
			cout << endl;
		}*/
	}
	else {
		return -1;
	}
	return 0;
}