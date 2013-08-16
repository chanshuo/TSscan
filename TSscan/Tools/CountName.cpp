#include <string.h>
#include "../cswu/Common.h"
#include "../cswu/Table.h"

void PrintUsage();

int main(int argc, char **argv)
{
	FILE *fp;
	char str[MaxLineSize+1];
	char str1[MaxLineSize+1] = "", str2[MaxLineSize+1] = "";
	int count;

	if(argc < 3)	{	PrintUsage();	return 1;	}
	
	if( !IsSorted(argv[1], (atoi(argv[2])-1), 'S') )
	{
		SortTable(argv[1], atoi(argv[2]), 'S', "CountName.temp");
		if(	( fp = fopen("CountName.temp", "r") ) == NULL )	{	ErrMsg("Error: fopen failed.\n");	return false;	}
	}
	else
		if(	( fp = fopen(argv[1], "r") ) == NULL )	{	ErrMsg("Error: fopen failed.\n");	return false;	}

	count = 1;

	for( TableRow theRow; theRow.Get(fp); )
	{
		ColCpy( str2, theRow.Column(atoi(argv[2])-1) );

		if( strcmp(str2, "") == 0 )
			continue;

		if( strcmp(str1, str2) == 0 )
			count++;
		else if( strcmp(str1, "") != 0 )
		{
			printf("%s\t%d\n", str1, count );
			count = 1;
		}
		
		strcpy( str1, str2 );	
	}
	if( strcmp(str1, "") != 0 )
		printf("%s\t%d\n", str1, count );

	fclose(fp);
	remove("CountName.temp");

	return 0;
}

void PrintUsage()
{
	ErrMsg("\n");
	ErrMsg("CountName [Input] [Column]\n\n");

	ErrMsg("[Input]         STRING\n");
	ErrMsg("[Column]        INTEGER     The column to count.\n\n");

	ErrMsg("Example: Count the number of occurrences of each 'Subject id' in the blast result.\n");
	ErrMsg("CountName result.blast 2 > result.conut\n\n");
}
