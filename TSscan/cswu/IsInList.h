#include <iostream>
#include <map>

using namespace std; 

class Str2BoolMap
{
	map <string, bool> themap;

public:
	void Add(const char *str);
	void AddIntoMap(const char *filename, int col = 0);
	inline void AddIntoMap(char *filename)	{	AddIntoMap(filename, 0);	}
	bool IsInMap(char *str);
};

class Str2IntMap
{
	map <string, int> themap;

public:
	void AddIntoMap(const char *filename, int col);
	inline void AddIntoMap(char *filename)	{	AddIntoMap(filename, 0);	}
	int IndexTheMap(char *str);
};
