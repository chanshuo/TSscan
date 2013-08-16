#include <stdlib.h>
#include <string.h>
#include "../cswu/Common.h"
#include "../cswu/Sam.h"

void PrintUsage();

int main(int argc, char **argv)
{
	bool flag;
	int i, count;
	int length, identity;
	int Seqlen;

	if( argc < 3 ) {	PrintUsage();	return 1;	}

	length = atoi(argv[1]);
	identity = atoi(argv[2]);

	for( SamOutput theSam; theSam.Get(); )
	{
		flag = true;
		Seqlen = strlen( theSam.Seq );
		
		if(length > Seqlen)
			length = Seqlen;
		
		for( i = 0, count = 0; i < length; i++ )
		{
			if( theSam.Seq[i] == 'A' || theSam.Seq[i] == 'a' || theSam.Seq[i] == 'N' )
				count++;
		}
		if( ((count*100)/length) >= identity )
			flag = false; 

		for( i = 0, count = 0; i < length; i++ )
		{
			if( theSam.Seq[i] == 'G' || theSam.Seq[i] == 'g' || theSam.Seq[i] == 'N' )
				count++;
		}
		if( ((count*100)/length) >= identity )
			flag = false; 

		for( i = 0, count = 0; i < length; i++ )
		{
			if( theSam.Seq[i] == 'C' || theSam.Seq[i] == 'c' || theSam.Seq[i] == 'N' )
				count++;
		}
		if( ((count*100)/length) >= identity )
			flag = false; 

		for( i = 0, count = 0; i < length; i++ )
		{
			if( theSam.Seq[i] == 'T' || theSam.Seq[i] == 't' || theSam.Seq[i] == 'N' )
				count++;
		}
		if( ((count*100)/length) >= identity )
			flag = false; 

		for( i = (Seqlen-1), count = 0; i > (Seqlen-length-1); i-- )
		{
			if( theSam.Seq[i] == 'A' || theSam.Seq[i] == 'a' || theSam.Seq[i] == 'N' )
				count++;
		}
		if( ((count*100)/length) >= identity )
			flag = false; 

		for( i = (Seqlen-1), count = 0; i > (Seqlen-length-1); i-- )
		{
			if( theSam.Seq[i] == 'G' || theSam.Seq[i] == 'g' || theSam.Seq[i] == 'N' )
				count++;
		}
		if( ((count*100)/length) >= identity )
			flag = false; 

		for( i = (Seqlen-1), count = 0; i > (Seqlen-length-1); i-- )
		{
			if( theSam.Seq[i] == 'C' || theSam.Seq[i] == 'c' || theSam.Seq[i] == 'N' )
				count++;
		}
		if( ((count*100)/length) >= identity )
			flag = false; 

		for( i = (Seqlen-1), count = 0; i > (Seqlen-length-1); i-- )
		{
			if( theSam.Seq[i] == 'T' || theSam.Seq[i] == 't' || theSam.Seq[i] == 'N' )
				count++;
		}
		if( ((count*100)/length) >= identity )
			flag = false; 

		if(flag)
			theSam.Print();
	}

	return 0;
}

void PrintUsage()
{
	ErrMsg("\n");
	ErrMsg("RmLowComplexReads [Length] [Identity]\n\n");

	ErrMsg("[Lenght]        INT         The length in both ends.\n");
	ErrMsg("[Identity]      INT         A vaule between 0--100.\n\n");

	ErrMsg("Example:\n");
	ErrMsg("cat C3.sam | ./RmLowComplexReads 10 90 > result.sam\n\n");
}
