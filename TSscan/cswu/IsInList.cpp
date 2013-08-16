#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <map>
#include "Common.h"
#include "Table.h"
#include "IsInList.h"

using namespace std;

void Str2BoolMap::Add(const char *str)
{
	if( themap.find(str) == themap.end() )
		themap[str] = true;
}

void Str2BoolMap::AddIntoMap(const char *filename, int col)
{
	FILE *fp;
	char str[MaxLineSize+1];

	if(	( fp = fopen(filename, "r") ) == NULL )	return;

	while(1)
	{
		TableRow theRow;
		if( theRow.Get(fp) == false )
			break;
		theRow.ColCopy(str, col);

		if( themap.find(str) == themap.end() )
			themap[str] = true;
	}	
}

bool Str2BoolMap::IsInMap(char *str)
{
	if( themap.find(str) != themap.end() )
		return true;
	return false;
}
