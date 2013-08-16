#include <string.h>
#include "../cswu/Common.h"
#include "../cswu/Table.h"

void PrintUsage();

int main(int argc, char **argv)
{
	if( (argc < 3) )	{	PrintUsage();	return 1;	}

	for( TableRow theRow; theRow.Get(); )
	{
		if( theRow.nColumns() >= 21 && atoi(theRow.Column(10)) > 0 )
			if( ( theRow.ColToI(11) < atoi(argv[1]) ) && ( ( theRow.ColToI(10) - theRow.ColToI(12) ) <= atoi(argv[1]) ) )
				if( ( (theRow.ColToI(0)*100)/theRow.ColToI(10) ) >= atoi(argv[2]) )
					theRow.Print();	
	}

	return 0;
}

void PrintUsage()
{
	ErrMsg("\n");
	ErrMsg("BlatFindCoLinear [Cut] [Identity]\n\n");

	ErrMsg("[Cut]          INT      Cut-off.\n");
	ErrMsg("[Identity]     INT      \n\n");

	ErrMsg("Example: Report the entries which the non-cover regions are < 20bp in both ends.\n");
	ErrMsg("cat Input.blat | ./BlatFindCoLinear 20 90 > Output.blat\n\n");
}
