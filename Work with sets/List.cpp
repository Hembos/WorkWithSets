#include "List.h"

//Сравнение строк(1 - больше первая, 2 - больше вторая, 3 - идентичные)
int compareStr(std::string str1, std::string str2)
{
	int length,
		itLarge = 0;
		
	if (str1.size() < str2.size())
	{
		length = str2.size();
		itLarge = 1;
	}
	else
	{
		length = str1.size();
		itLarge = 2;
		if (str1.size() == str2.size())
		{
			itLarge = 3;
		}
	}
			
	for (int i = 0; i < length; i++)
	{
		if (str1[i] < str2[i])
		{
			itLarge = 1;
			break;
		}
		else
		{
			if (str1[i] > str2[i])
			{
				itLarge = 2;
				break;
			}
		}
	}
		
	return itLarge;
}

List::List()
{
	m_head = nullptr;
	cardinality = 0;
}

List::~List()
{
	Node* tmp = m_head, *tmp1;
	while (tmp != nullptr)
	{
		tmp1 = tmp;
		tmp = tmp->m_next;
		delete tmp1;
	}
}

int List::addInList(std::string elem)
{
	Node* newNode;

	newNode = new Node;
	newNode->m_elem = elem;
	newNode->m_next = nullptr;
	newNode->m_prev = nullptr;

	Node* tmp = m_head;

	if (tmp == nullptr)
	{
		cardinality++;
		m_head = newNode;
		return SUCCESS;
	}
	
	int cmpStrRes;
	while (tmp != nullptr)
	{
		cmpStrRes = compareStr(elem, tmp->m_elem);
		if (cmpStrRes == 2)
		{
			if (tmp->m_prev == nullptr)
			{
				newNode->m_next = tmp;
				tmp->m_prev = newNode;
				m_head = newNode;
				break;
			}
			tmp->m_prev->m_next = newNode;
			newNode->m_prev = tmp->m_prev;
			newNode->m_next = tmp;
			tmp->m_prev = newNode;
			break;
		}
		else
		{
			if (cmpStrRes == 3)
			{
				return NAME_ALREADY_EXISTS;
			}
			if (cmpStrRes == 1 && tmp->m_next == nullptr)
			{
				tmp->m_next = newNode;
				newNode->m_prev = tmp;
				break;
			}
		}
		tmp = tmp->m_next;
	}

	cardinality++;
	return SUCCESS;
}

int List::removeNode(std::string elem)
{
	Node* tmp = m_head;

	while (tmp != nullptr)
	{
		if (tmp->m_elem == elem)
		{
			break;
		}
		tmp = tmp->m_next;
	}

	if (tmp == NULL)
	{
		return NOT_FOUND;
	}
	if (tmp->m_prev == nullptr)
	{
		tmp->m_next->m_prev = nullptr;
		m_head = tmp->m_next;
		tmp->m_next = nullptr;
	}
	else
	{
		if (tmp->m_next == nullptr)
		{
			tmp->m_prev->m_next = nullptr;
			tmp->m_prev = nullptr;
		}
		else
		{
			tmp->m_prev->m_next = tmp->m_next;
			tmp->m_next->m_prev = tmp->m_prev;
			tmp->m_next = nullptr;
			tmp->m_prev = nullptr;
		}
	}
	
	delete tmp;
	cardinality--;

	return SUCCESS;
}

bool List::elemExist(std::string elem)
{
	Node* tmp = m_head;
	bool itExist = false;

	while (tmp != nullptr)
	{
		if (tmp->m_elem == elem)
		{
			itExist = true;
			break;
		}
		tmp = tmp->m_next;
	}

	return itExist;
}

int List::getCardinality()
{
	return cardinality;
}