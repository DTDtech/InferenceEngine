#pragma once
#include "KnowledgeBase.h"
#include <string>

class Strategy {
public:
	//Strategy(std::vector<std::vector<std::string>> separatedPropositionStatements);
	bool Separate_Statement_Into_Symbols_And_Connectives(KnowledgeBase& kb);

	void insertSeparatedStatement(std::vector<std::string>& separatedStatement);
	std::vector<std::vector<std::string>> getSeparatedStatements();

	/*void setPropositionSymbols(std::vector<std::string>& symbols);
	std::vector<std::string> getPropositionSymbols();*/
private:
	std::vector<std::vector<std::string>> separatedStatements;
//	std::vector<std::string> propositionSymbols;
//	std::string query;
};

class TruthTable : public Strategy {
public: 
};

class ForwardChaining : virtual public Strategy {
public:
	//ForwardChaining(std::vector<std::vector<std::string>> separatedPropositionStatements) : Strategy(separatedPropositionStatements) {};
	bool AddConclusionsFromPremises(KnowledgeBase& kb);
	void PrintResult();
};