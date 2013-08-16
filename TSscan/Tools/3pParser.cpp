#include <string.h>
#include "../cswu/Common.h"
#include "../cswu/Table.h"

void PrintUsage();

int main(int argc, char **argv)
{
	int ChiStart, ChiEnd;
	int Acc;

	if( (argc < 4) )	{	PrintUsage();	return 1;	}

	for( TableRow theRow[3]; theRow[0].Get(); )
	{	
		theRow[1].Get();
		theRow[2].Get();

		Acc = 0;

		if( theRow[0].nColumns() <= 20 || theRow[1].nColumns() <= 20 || theRow[2].nColumns() <= 20 )
		{
			ErrMsg("Error: nColumns() <= 20\n");			
			break;
		}

		if( theRow[1].ColToI(11) < theRow[2].ColToI(11) )
			ChiStart = theRow[1].ColToI(11);
		else
			ChiStart = theRow[2].ColToI(11);

		if( theRow[1].ColToI(12) > theRow[2].ColToI(12) )
			ChiEnd = theRow[1].ColToI(12);
		else
			ChiEnd = theRow[2].ColToI(12);
		
		Acc = theRow[0].ColToI(11)-ChiStart;
		Acc += ChiEnd-theRow[0].ColToI(12);

		if( *theRow[1].Column(13) == 'M' && *theRow[2].Column(13) == 'M' )
			if( *theRow[1].Column(8) == *theRow[2].Column(8) )
				Acc = -1;

		if( Acc > atoi(argv[1]) )
		{
			int a1, a2;

			a1 = theRow[1].ColToI(12) - theRow[1].ColToI(11);
			a2 = theRow[2].ColToI(12) - theRow[2].ColToI(11);

			if( ((theRow[1].ColToI(0)*100)/a1) >= atoi(argv[2]) && ((theRow[2].ColToI(0)*100)/a2) >= atoi(argv[2]) )
			{
				if( theRow[1].ColToI(0) >= atoi(argv[3]) && theRow[2].ColToI(0) >= atoi(argv[3]) )
				{
					theRow[0].Print();
					theRow[1].Print();
					theRow[2].Print();
				}
			}
		}
	}

	return 0;
}

void PrintUsage()
{
	ErrMsg("\n");
	ErrMsg("3pParser [Cut] [Identity] [Score]\n\n");

	ErrMsg("[Cut]          INT      Cut-off. 'Chimera length' - 'longset co-liner length' > the cut value.\n");
	ErrMsg("[Identity]     INT      \n");
	ErrMsg("[Score]        INT      \n\n");

	ErrMsg("Example:\n");
	ErrMsg("cat Input.blat | ./3pParser 20 90 50 > Output.blat\n\n");
}
