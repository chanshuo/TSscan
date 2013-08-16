#include <string.h>
#include "../cswu/Common.h"
#include "../cswu/Table.h"

void PrintUsage();

int main(int argc, char **argv)
{
	if( (argc < 2) )	{	PrintUsage();	return 1;	}

	for( TableRow theRow; theRow.Get(); )
	{
		if( theRow.nColumns() >= 21 && atoi(theRow.Column(10)) > 0 )
			if( ( (theRow.ColToI(0) * 100 )/theRow.ColToI(10) ) >= atoi(argv[1]) )
				theRow.Print();	
	}

	return 0;
}

void PrintUsage()
{
	ErrMsg("\n");
	ErrMsg("BlatCoverCut [Cut]\n\n");

	ErrMsg("[Cut]          INT      Cut-off.\n\n");

	ErrMsg("Example: Retain only the row when (match/Q size) > 50\% from a blat result.\n");
	ErrMsg("cat a.blat | BlatCoverCut > Output\n\n");
}
