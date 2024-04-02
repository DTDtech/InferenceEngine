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
};

class TruthTable : public Strategy {
public: 
	TruthTable();
	void CheckConclusionsFromPremises(KnowledgeBase& kb);

	void PrintSuccessfulResult() const override;

	int getModelsCount() const;
	void increaseModelsCount();

private:
	int modelsCount;
};

class ForwardChaining : public Strategy {
public:
	ForwardChaining();
	void AddConclusionsFromPremises(KnowledgeBase& kb);
	bool RecheckInvalidStatements(std::map<std::vector<std::string>, std::string>& invalidStatements, KnowledgeBase& kb);

	void PrintSuccessfulResult() const override;

	void addSymbol(std::string symbol);
	std::vector<std::string> getAddedSymbols() const;

private:
	std::vector<std::string> symbolsAdded;
};

class BackwardChaining : public Strategy {
public:
	BackwardChaining();
	void AddPremisesFromQuery(KnowledgeBase& kb);
	bool Find_Statement_Matching_With_Symbols(std::vector<std::string> unEstablishedPremise, std::vector<std::vector<std::string>>& separatedStatementsList, KnowledgeBase& kb);

	void PrintSuccessfulResult() const override;

	void addSymbol(std::string symbol);
	std::vector<std::string> getAddedSymbols() const;

private:
	std::vector<std::string> symbolsAdded;
};
