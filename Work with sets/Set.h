#ifndef SET_H
#define SET_H

#include "List.h"

class Set
{
private:
	struct Sets
	{
		std::string m_name;
		List m_set;
		Sets* m_nextSet;
		Sets* m_prevSet;
	};
	Sets* m_headSet;
public:
	Set();
	int createSet(std::string name);
	int delSet(std::string name);
	int addInSet(std::string name, std::string elem);
	int delFromSet(std::string name, std::string elem);
	int elemInSet(std::string name, std::string elem);
	int setCardinality(std::string name);
	int unionSets(Sets* resSet, Sets* set1, Sets* set2);
	int intersectionSets(Sets* resSet, Sets* set1, Sets* set2);
	int diffSets(Sets* resSet, Sets* set1, Sets* set2);
	int symDiffSets(Sets* resSet, Sets* set1, Sets* set2);
	bool inclusionCheck(Sets* set1, Sets* set2);
	Sets* getSet(std::string name);
	void printSet(std::string name);
	void printNameSets();
};



#endif // !SET_H
