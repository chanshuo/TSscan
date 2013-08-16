#include <string.h>
#include "../cswu/Common.h"
#include "../cswu/Table.h"
#include "../cswu/Seq.h"
#include "../cswu/Map.h"

void PrintUsage();

int main(int argc, char **argv)
{
	Str2BoolMap theMap;
	FILE *infile, *outfile;

	if(argc == 5)	
	{
		if(	( infile = fopen(argv[1], "r") ) == NULL )
		{	PrintUsage();	return 1;	}	
		if(	( outfile = fopen(argv[4], "w") ) == NULL )
		{	PrintUsage();	return 1;	}	

		theMap.AddIntoMap( argv[2], atoi(argv[3])-1 );
	}	
	else if(argc == 3)
	{
		infile = stdin;
		outfile = stdout;
		theMap.AddIntoMap( argv[1], atoi(argv[2])-1 );
	}
	else
	{	PrintUsage();	return 1;	}	

	for( Sequence seq; seq.Get(infile); )
	{
		if( !theMap.IsInMap(seq.Name()) )
			seq.Print(outfile);
	}

	fclose(infile);
	fclose(outfile);
	return 0;
}

void PrintUsage()
{
	ErrMsg("Remove the listed sequences.\n\n");

	ErrMsg("SeqRm [List] [Key]\n");
	ErrMsg("SeqRm [Input] [List] [Key] [Output]\n\n");

	ErrMsg("[Input]         STRING      A FASTA format file.\n");
	ErrMsg("[List]          FILE        The filename of a table as the list.\n");
	ErrMsg("[Key]           INTEGER     The key column in the list.\n");
	ErrMsg("[Output]        STRING      \n\n");

	ErrMsg("Example:\n");
	ErrMsg("SeqRm list.txt 1 < est.fa > result.txt\n");
	ErrMsg("SeqRm est.fa list.txt 1 result.txt\n\n");
}
