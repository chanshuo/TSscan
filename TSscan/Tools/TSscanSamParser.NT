#include <string.h>
#include "../cswu/Common.h"
#include "../cswu/Table.h"
#include "../cswu/IsInList.h"
#include "../cswu/Seq.h"
#include "../cswu/Sam.h"

#define LenCut		10
#define IdentityCut	95

void PrintUsage();

int main(int argc, char **argv)
{
	SeqPool seqpool;
	bool cs;

	if( argc < 2 ) {	PrintUsage();	return 1;	}	

	seqpool.Add(argv[1]);

	for( SamOutput theSam; theSam.Get(); )
	{
		char str[81];
		char seq[4096];
		char csseq[4096];	
		int qLen, rLen;
		int numErr, numLErr, numRErr;	
		int leftLen, rightLen;
		int i;
		int Pos;
		int identity;
		
		qLen = strlen(theSam.Qual);
		identity = IdentityCut;

		if( theSam.AS < (50*qLen-200) )
			continue;
	
		if( strncmp( theSam.CIGAR, ItoA(qLen, str, 10), strlen(ItoA(qLen, str, 10)) ) != 0 )
			continue;

		strcpy(seq, seqpool.GiveMe(theSam.rName)->c_str());

		numErr=0;
		numLErr = 0;
		numRErr = 0;
		leftLen = 0;
		rightLen = 0;
		rLen = strlen(seq);

		Pos = theSam.Pos-1;

		for(i=0; i<qLen; i++)
		{
			if( (i+Pos) < 0 )
				continue;
			if( seq[i+Pos] != theSam.Seq[i] )
			{
				numErr++;
				if( (i+Pos) < (rLen-40) )
					numLErr++;
				if( (i+Pos) >= 40 )
					numRErr++;
			}

			if( (i+Pos) < (rLen-40) )
				leftLen++;
			if( (i+Pos) >= 40 )
				rightLen++;
		}
			

		if( numErr > 1 )
		{
			fprintf(stderr, "AS: %d\tPos: %d\t%s\%s\n", theSam.AS, Pos, seq, theSam.Seq);
			ErrMsg("numErr.\n");
			continue;
		}
		if( leftLen < LenCut )
			continue;
		if( rightLen < LenCut )
			continue;

		if( leftLen < 20 )	
			if( numLErr > 1 )
				continue;
			
		if( rightLen < 20 )
			if( numRErr > 1 )
				continue;

		theSam.Print();
	}

	return 0;
}

void PrintUsage()
{
	ErrMsg("\n");
	ErrMsg("ChimeraParser.NT [Junction Site]\n\n");

	ErrMsg("Only for NT sequences.\n");
	ErrMsg("[Junction Site] FILE        A fasta format sequences of junction sites.\n\n");

	ErrMsg("Example:\n");
	ErrMsg("cat Reads_vs_JS.sam | ./ChimeraParser.NT JS.fa > result.sam\n\n");
}
