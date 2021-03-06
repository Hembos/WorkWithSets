#include "Set.h"

Set::Set()
{
	m_headSet = nullptr;
}

int Set::createSet(std::string name)
{
	Sets* newSet;

	newSet = new Sets;
	newSet->m_name = name;
	newSet->m_nextSet = nullptr;
	newSet->m_prevSet = nullptr;

	Sets* tmp = m_headSet;

	if (tmp == nullptr)
	{
		m_headSet = newSet;
		return SUCCESS;
	}

	int cmpStrRes;
	while (tmp != nullptr)
	{
		cmpStrRes = compareStr(name, tmp->m_name);
		if (cmpStrRes == 2)
		{
			if (tmp->m_prevSet == nullptr)
			{
				newSet->m_nextSet = tmp;
				tmp->m_prevSet = newSet;
				m_headSet = newSet;
				break;
			}
			tmp->m_prevSet->m_nextSet = newSet;
			newSet->m_prevSet = tmp->m_prevSet;
			newSet->m_nextSet = tmp;
			tmp->m_prevSet = newSet;
			break;
		}
		else
		{
			if (cmpStrRes == 3)
			{
				return NAME_ALREADY_EXISTS;
			}
			if (cmpStrRes == 1 && tmp->m_nextSet == nullptr)
			{
				tmp->m_nextSet = newSet;
				newSet->m_prevSet = tmp;
				break;
			}
		}
		tmp = tmp->m_nextSet;
	}

	return SUCCESS;
}

int Set::delSet(std::string name)
{
	Sets* tmp = m_headSet;

	while (tmp != nullptr)
	{
		if (tmp->m_name == name)
		{
			break;
		}
		tmp = tmp->m_nextSet;
	}

	if (tmp == NULL)
	{
		return NOT_FOUND;
	}
	if (tmp->m_prevSet == nullptr)
	{
		if (tmp->m_nextSet != nullptr)
		{
			tmp->m_nextSet->m_prevSet = nullptr;
		}
		m_headSet = tmp->m_nextSet;
		tmp->m_nextSet = nullptr;
	}
	else
	{
		if (tmp->m_nextSet == nullptr)
		{
			tmp->m_prevSet->m_nextSet = nullptr;
			tmp->m_prevSet = nullptr;
		}
		else
		{
			tmp->m_prevSet->m_nextSet = tmp->m_nextSet;
			tmp->m_nextSet->m_prevSet = tmp->m_prevSet;
			tmp->m_nextSet = nullptr;
			tmp->m_prevSet = nullptr;
		}
	}

	delete tmp;

	return SUCCESS;
}

Sets* Set::getSet(std::string name)
{
	Sets* tmp = m_headSet;

	while (tmp != nullptr)
	{
		if (tmp->m_name == name)
		{
			break;
		}
		tmp = tmp->m_nextSet;
	}
	return tmp;
}

int Set::addInSet(std::string name, std::string elem)
{
	Sets* tmp = getSet(name);
	if (tmp == nullptr)
	{
		return NOT_FOUND;
	}
	return tmp->m_set.addInList(elem);
}

int Set::delFromSet(std::string name, std::string elem)
{
	Sets* tmp = getSet(name);
	if (tmp == nullptr)
	{
		return NOT_FOUND;
	}
	return tmp->m_set.removeNode(elem);
}

int Set::elemInSet(std::string name, std::string elem)
{
	Sets* tmp = getSet(name);
	if (tmp == nullptr)
	{
		return NOT_FOUND;
	}
	return tmp->m_set.elemExist(elem);
}

int Set::setCardinality(std::string name)
{
	Sets* tmp = getSet(name);
	if (tmp == nullptr)
	{
		return NOT_FOUND;
	}
	return tmp->m_set.getCardinality();
}

int Set::unionSets(Sets* resSet, Sets* set1, Sets* set2)
{
	Node* tmpSet1 = set1->m_set.m_head,
		* tmpSet2 = set2->m_set.m_head;
	int cmpElem = 0;
	while (tmpSet1 != nullptr || tmpSet2 != nullptr)
	{
		if (tmpSet1 == nullptr)
		{
			resSet->m_set.addInList(tmpSet2->m_elem);
			tmpSet2 = tmpSet2->m_next;
			continue;
		}
		if (tmpSet2 == nullptr)
		{
			resSet->m_set.addInList(tmpSet1->m_elem);
			tmpSet1 = tmpSet1->m_next;
			continue;
		}
		cmpElem = compareStr(tmpSet1->m_elem, tmpSet2->m_elem);
		if (cmpElem == 2)
		{
			resSet->m_set.addInList(tmpSet1->m_elem);
			tmpSet1 = tmpSet1->m_next;
		}
		else
		{
			if (cmpElem == 1)
			{
				resSet->m_set.addInList(tmpSet2->m_elem);
				tmpSet2 = tmpSet2->m_next;
			}
			else
			{
				resSet->m_set.addInList(tmpSet1->m_elem);
				tmpSet1 = tmpSet1->m_next;
				tmpSet2 = tmpSet2->m_next;
			}
		}
	}

	return SUCCESS;
}

int Set::intersectionSets(Sets* resSet, Sets* set1, Sets* set2)
{
	Node* tmpSet1 = set1->m_set.m_head,
		* tmpSet2 = set2->m_set.m_head;
	int cmpElem = 0;
	while (tmpSet1 != nullptr && tmpSet2 != nullptr)
	{
		cmpElem = compareStr(tmpSet1->m_elem, tmpSet2->m_elem);
		if (cmpElem == 2)
		{
			tmpSet1 = tmpSet1->m_next;
		}
		else
		{
			if (cmpElem == 1)
			{
				tmpSet2 = tmpSet2->m_next;
			}
			else
			{
				resSet->m_set.addInList(tmpSet1->m_elem);
				tmpSet1 = tmpSet1->m_next;
				tmpSet2 = tmpSet2->m_next;
			}
		}
	}

	return SUCCESS;
}

int Set::diffSets(Sets* resSet, Sets* set1, Sets* set2)
{
	Node* tmpSet1 = set1->m_set.m_head,
		* tmpSet2 = set2->m_set.m_head;
	int cmpElem = 0;
	while (tmpSet1 != nullptr || tmpSet2 != nullptr)
	{
		if (tmpSet1 == nullptr)
		{
			tmpSet2 = tmpSet2->m_next;
			continue;
		}
		if (tmpSet2 == nullptr)
		{
			resSet->m_set.addInList(tmpSet1->m_elem);
			tmpSet1 = tmpSet1->m_next;
			continue;
		}
		cmpElem = compareStr(tmpSet1->m_elem, tmpSet2->m_elem);
		if (cmpElem == 2)
		{
			resSet->m_set.addInList(tmpSet1->m_elem);
			tmpSet1 = tmpSet1->m_next;
		}
		else
		{
			if (cmpElem == 1)
			{
				tmpSet2 = tmpSet2->m_next;
			}
			else
			{
				tmpSet1 = tmpSet1->m_next;
				tmpSet2 = tmpSet2->m_next;
			}
		}
	}

	return SUCCESS;
}

int Set::symDiffSets(Sets* resSet, Sets* set1, Sets* set2)
{
	Node* tmpSet1 = set1->m_set.m_head,
		* tmpSet2 = set2->m_set.m_head;
	int cmpElem = 0;
	while (tmpSet1 != nullptr || tmpSet2 != nullptr)
	{
		if (tmpSet1 == nullptr)
		{
			resSet->m_set.addInList(tmpSet2->m_elem);
			tmpSet2 = tmpSet2->m_next;
			continue;
		}
		if (tmpSet2 == nullptr)
		{
			resSet->m_set.addInList(tmpSet1->m_elem);
			tmpSet1 = tmpSet1->m_next;
			continue;
		}
		cmpElem = compareStr(tmpSet1->m_elem, tmpSet2->m_elem);
		if (cmpElem == 2)
		{
			resSet->m_set.addInList(tmpSet1->m_elem);
			tmpSet1 = tmpSet1->m_next;
		}
		else
		{
			if (cmpElem == 1)
			{
				resSet->m_set.addInList(tmpSet2->m_elem);
				tmpSet2 = tmpSet2->m_next;
			}
			else
			{
				tmpSet1 = tmpSet1->m_next;
				tmpSet2 = tmpSet2->m_next;
			}
		}
	}

	return SUCCESS;
}

bool Set::inclusionCheck(Sets* set1, Sets* set2)
{
	Node* tmpSet1 = set1->m_set.m_head,
		* tmpSet2 = set2->m_set.m_head;
	int cmpElem = 0;
	while (tmpSet1 != nullptr && tmpSet2 != nullptr)
	{
		cmpElem = compareStr(tmpSet1->m_elem, tmpSet2->m_elem);
		if (cmpElem == 2)
		{
			return false;
		}
		else
		{
			if (cmpElem == 1)
			{
				tmpSet2 = tmpSet2->m_next;
			}
			else
			{
				tmpSet1 = tmpSet1->m_next;
				tmpSet2 = tmpSet2->m_next;
			}
		}
	}

	if (tmpSet1 == nullptr)
	{
		return true;
	}
	else
	{
		return false;
	}
}

int Set::printSet(std::string name)
{
	Sets* tmp = getSet(name);
	if (tmp == nullptr)
	{
		return NOT_FOUND;
	}
	Node* tmp1 = tmp->m_set.m_head;
	while (tmp1 != nullptr)
	{
		std::cout << tmp1->m_elem << std::endl;
		tmp1 = tmp1->m_next;
	}
}

void Set::printNameSets()
{
	Sets* tmp = m_headSet;
	while (tmp != nullptr)
	{
		std::cout << "\"" << tmp->m_name << "\"" << std::endl;
		tmp = tmp->m_nextSet;
	}
}