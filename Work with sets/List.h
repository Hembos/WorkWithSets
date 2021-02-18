#ifndef LIST_H
#define LIST_H

#include <iostream>
#include <string>

#define SUCCESS 1
#define NAME_ALREADY_EXISTS -1
#define NOT_FOUND -2

struct Node
{
	std::string m_elem;
	Node* m_next;
	Node* m_prev;
};

class List
{
	int cardinality;
public:
	Node* m_head;
public:
	List();
	~List();
	int addInList(std::string elem);
	int removeNode(std::string elem);
	bool elemExist(std::string elem);
	int getCardinality();
};

int compareStr(std::string str1, std::string str2);

#endif // !LIST_H
