#include <stdlib.h>
#include "../cswu/Common.h"
#include "../cswu/Map.h"
#include "../cswu/Sam.h"

#define ArrSize	16*1024*1024

void PrintUsage();

int main(int argc, char **argv)
{
	int *IntArr;
	FILE *infile = NULL;
	int i;
	int cut;

	if( argc < 2 ) {	PrintUsage();	return 1;	}

	if( argc > 2 )
		cut = atoi(argv[2]);

	if(	( infile = fopen(argv[1], "r") ) == NULL ){	ErrMsg("Error: fopen failed.\n");	return 1;	}

	IntArr = new int [ArrSize];

	for(i=0; i<ArrSize; i++)
		IntArr[i] = -1;
	
	Str2IntMap themap;
	themap.AddIntoMap(argv[1], 0);

	for( SamOutput theSam; theSam.Get(infile); )
	{
		if( ( i = themap.IndexTheMap(theSam.qName) ) >= 0 )
			if(IntArr[i] < theSam.AS)
				IntArr[i] = theSam.AS;
	}

	for( SamOutput theSam; theSam.Get(); )
	{
		if( ( i = themap.IndexTheMap(theSam.qName) ) >= 0 )
			if(IntArr[i] >= (theSam.AS - cut) )
				continue;

		theSam.Print();
	}

	delete [] IntArr;
	
	if( infile != NULL )
		fclose(infile);

	return 0;
}

void PrintUsage()
{
	ErrMsg("\n");
	ErrMsg("RmAmbiMapping [SAM] [Cut]\n\n");

	ErrMsg("[SAM]           FILE        A SAM file.\n\n");
	ErrMsg("[Cut]           INT         Chimera AS - co-linear AS > cut.\n\n");

	ErrMsg("Example:\n");
	ErrMsg("cat C3.sam | ./RmAmbiMapping C3.ref.sam > result.sam\n\n");
}
