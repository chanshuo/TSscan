#include <stdio.h>
#include <stdlib.h>

void PrintUsage()
{
	fprintf(stderr, "Usage:\n");
	fprintf(stderr, "TSscan3of4 [psl] [fasta] [Output]\n\n");

	fprintf(stderr, "[psl]       The output file of step 5.\n");
	fprintf(stderr, "[fasta]     Your long reads in fasta format.\n");
	fprintf(stderr, "[Output]    File name of output.\n\n");
	
	fprintf(stderr, "Example:\n");
	fprintf(stderr, "step5.out.psl longreads.fa step6.out.fa\n");
}

int main(int argc, char **argv)
{
	char str[1024];

	if(argc != 4)
	{ PrintUsage();	return 1; }

	sprintf(str, "cat %s | ./BlatCoverCut 50 > C1-C2.c50.blat", argv[1]);	
	system(str);
	system("cat C1.list | ./RemoveInList 1 C1-C2.c50.blat 10 > C2.list");

	sprintf(str, "cat %s | ./SeqOut C2.list 1 > C2.fa", argv[2]);	
	system(str);

	sprintf(str, "cat jsite.fa | ./SeqOut C2.list 1 > %s", argv[3]);	
	system(str);

	return 0;
}
