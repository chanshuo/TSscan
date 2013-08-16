#include <iostream>
#include <map>

using namespace std; 

class Str2BoolMap
{
	map <string, bool> themap;

public:
	void Add(const char *str);
	void AddIntoMap(const char *filename, int col = 0);
	bool IsInMap(char *str);
};

class Str2IntMap
{
	map <string, int> themap;

public:
	int AddIntoMap(const char *filename, int col);
	int IndexTheMap(char *str);
};

class Str2StrMap
{
	map <string, string> themap;

public:
	int AddIntoMap(const char *filename, int key_col, int data_col);
	char* At(const char *str, char *buf);
};
