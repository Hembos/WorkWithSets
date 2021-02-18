#include "Set.h"

#define LONG_STRING -1
#define WRONG_SET_NAME_OR_ELEM -2

using namespace std;

struct Command
{
	string com;
	string str[3];
};

void help()
{
	cout << "Create set \"nameSet\"" << endl;
	cout << "Delete set \"nameSet\"" << endl;
	cout << "Add in \"nameSet\" \"element\"" << endl;
	cout << "Delete from \"nameSet\" \"element\"" << endl;
	cout << "Find in \"setName\" \"element\"" << endl;
	cout << "Cardinality \"setName\"" << endl;
	cout << "Print all sets" << endl;
	cout << "Print elements from \"setName\"" << endl;
	cout << "Union \"nameSet1\" \"nameSet2\" \"resultNameSet\"" << endl;
	cout << "Intersection \"nameSet1\" \"nameSet2\" \"resultNameSet\"" << endl;
	cout << "Differens \"nameSet1\" \"nameSet2\" \"resultNameSet\"" << endl;
	cout << "Symmetric differens \"nameSet1\" \"nameSet\" \"resultNameSet\"" << endl;
	cout << "Inclusion \"nameSet1\" \"nameSet2\"" << endl;
	cout << "End programm" << endl;
}

int getCommand(Command & command, string str)
{
	int index = 0;

	command.com = "";
	for (int i = 0; i < 3; i++)
	{
		command.str[i] = "";
	}

	while (str[index] != '"' && str[index] != '\0') 
	{
		command.com += str[index];
		index++;
	}

	if (str[index] == '\0')
	{
		return 0;
	}

	int indexStr = 0,
		numStr = 0;
	
	while (isspace(str[index]) || str[index] == '"')
	{
		index++;
	}
	while (str[index] != '\0')
	{
		indexStr = 0;
		while (str[index] != '"')
		{
			if (str[index] == '\0')
			{
				break;
			}
			if (indexStr > 80)
			{
				return LONG_STRING;
			}
			command.str[numStr] += str[index];
			index++;
			indexStr++;
		}
		numStr++;
		if (str[index] != '"')
		{
			return WRONG_SET_NAME_OR_ELEM;
		}
		while (isspace(str[index]) || str[index] == '"')
		{
			index++;
		}
	}
}

int main()
{
	setlocale(LC_ALL, "Russian");
	cout << "Enter help to get a list of commands" << endl;

	string str;
	Command comm;
	Set sets;
	int error;
	while (true)
	{
		getline(cin, str);		
		error = getCommand(comm, str);
		if (error == LONG_STRING)
		{
			cout << "The line is too long. Please enter a string less than 80" << endl;
			continue;
		}
		if (error == WRONG_SET_NAME_OR_ELEM)
		{
			cout << "The name or element was entered incorrectly. Name or element must be in quotes" << endl;
			continue;
		}
		if (compareStr(comm.com, "help") == 3)
		{
			help();
			continue;
		}
		if (compareStr(comm.com, "End programm") == 3)
		{
			break;
		}
		if (compareStr(comm.com, "Create set ") == 3)
		{
			error = sets.createSet(comm.str[0]);
			if (error == NAME_ALREADY_EXISTS)
			{
				cout << "The set was not created because this name is taken" << endl;
			}
			else
			{
				cout << "Set successfully created" << endl;
			}
			continue;
		}
		if (compareStr(comm.com, "Delete set ") == 3)
		{
			error = sets.delSet(comm.str[0]);
			if (error == NOT_FOUND)
			{
				cout << "The set was not found" << endl;
			}
			else
			{
				cout << "Set successfully deleted" << endl;
			}
			continue;
		}
		if (compareStr(comm.com, "Cardinality ") == 3)
		{
			error = sets.setCardinality(comm.str[0]);
			if (error == NOT_FOUND)
			{
				cout << "The set was not found" << endl;
			}
			else
			{
				cout << error << endl;
			}
			continue;
		}
		if (compareStr(comm.com, "Add in ") == 3)
		{
			error = sets.addInSet(comm.str[0], comm.str[1]);
			if (error == NOT_FOUND)
			{
				cout << "The set was not found" << endl;
			}
			else
			{
				if (error == NAME_ALREADY_EXISTS)
				{
					cout << "The element was not added because this element already exist" << endl;
					continue;
				}
				cout << "Element successfully added" << endl;
			}
			continue;
		}
		if (compareStr(comm.com, "Delete from ") == 3)
		{
			error = sets.delFromSet(comm.str[0], comm.str[1]);
			if (error == NOT_FOUND)
			{
				cout << "The set was not found" << endl;
			}
			else
			{
				cout << "Element successfully deleted" << endl;
			}
			continue;
		}
		if (compareStr(comm.com, "Find in ") == 3)
		{
			error = sets.elemInSet(comm.str[0], comm.str[1]);
			if (error == NOT_FOUND)
			{
				cout << "The set was not found" << endl;
			}
			else
			{
				if (error == false)
				{
					cout << "Element not exist" << endl;
				}
				else
				{
					cout << "Element exist" << endl;
				}
			}
			continue;
		}
		if (compareStr(comm.com, "Union ") == 3)
		{
			error = sets.unionSets(sets.getSet(comm.str[2]), sets.getSet(comm.str[0]), sets.getSet(comm.str[1]));
			cout << "Sets are combined successfully" << endl;
		}
		if (compareStr(comm.com, "Intersection ") == 3)
		{
			error = sets.intersectionSets(sets.getSet(comm.str[2]), sets.getSet(comm.str[0]), sets.getSet(comm.str[1]));
			cout << "Sets intersection successfully" << endl;
		}
		if (compareStr(comm.com, "Differens ") == 3)
		{
			error = sets.diffSets(sets.getSet(comm.str[2]), sets.getSet(comm.str[0]), sets.getSet(comm.str[1]));
			cout << "Sets are difference successfully" << endl;
		}
		if (compareStr(comm.com, "Symmetric differens ") == 3)
		{
			error = sets.symDiffSets(sets.getSet(comm.str[2]), sets.getSet(comm.str[0]), sets.getSet(comm.str[1]));
			cout << "Sets are symmetric difference successfully" << endl;
		}
		if (compareStr(comm.com, "Inclusion ") == 3)
		{
			error = sets.inclusionCheck(sets.getSet(comm.str[0]), sets.getSet(comm.str[1]));
			if (error == 0)
			{
				cout << "Set not included" << endl;
			}
			else
			{
				cout << "Set included" << endl;
			}
		}
		if (compareStr(comm.com, "Print all sets") == 3)
		{
			sets.printNameSets();
		}
		if (compareStr(comm.com, "Print elements from ") == 3)
		{
			sets.printSet(comm.str[0]);
		}
	}

	return 0;
}