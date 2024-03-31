#pragma once
#include "KnowledgeBase.h"
#include <string>
#include <vector>
#include <map>

class Strategy {
public:
	bool Separate_Statement_Into_Symbols_And_Connectives(KnowledgeBase& kb);

	void insertSeparatedStatement(std::vector<std::string>& separatedStatement);
	std::vector<std::vector<std::string>> getSeparatedStatements();

	virtual void PrintSuccessfulResult() const = 0;
	void PrintUnsuccessfulResult();

protected:
	std::vector<std::vector<std::string>> separatedStatements;
	std::vector<std::string> symbolsAdded;
};

class TruthTable : public Strategy {
public: 
	void addSymbol(std::string symbol);
	std::vector<std::string> getAddedSymbols();

	bool CheckConclusionsFromPremises(KnowledgeBase& kb);
};

class ForwardChaining : virtual public Strategy {
public:

	void addSymbol(std::string symbol);
	std::vector<std::string> getAddedSymbols();

	bool AddConclusionsFromPremises(KnowledgeBase& kb);
	bool RecheckInvalidStatements(std::map<std::vector<std::string>, std::string>& invalidStatements, KnowledgeBase& kb);

	void PrintSuccessfulResult() const override;
};