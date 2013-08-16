#include <stdio.h>
#include <stdlib.h>

void PrintUsage()
{
	fprintf(stderr, "Usage:\n");
	fprintf(stderr, "TSscan2of4 [psl] [fasta] [Output]\n\n");

	fprintf(stderr, "[psl]       The output of step 3.\n");
	fprintf(stderr, "[fasta]     Your long reads in fasta format.\n");
	fprintf(stderr, "[Output]    File name of output.\n\n");
	
	fprintf(stderr, "Example:\n");
	fprintf(stderr, "TSscan2of4 RefRNA.blat sample.fa step4.out.fa\n");
}

int main(int argc, char **argv)
{
	char str[1024];

	if(argc != 4)
	{ PrintUsage();	return 1; }

	sprintf(str, "cat %s | ./BlatFindCoLinear 20 90 > C0.hg19.Linear.blat", argv[1]);	
	system(str);

	system("cat noncolinear.blat | ./3pParser 20 95 50 > temp.blat");
	system("cat temp.blat | ./RemoveInList 10 C0.hg19.Linear.blat 10 > Chi.blat");
	system("./CountName Chi.blat 10 > C1.list");

	sprintf(str, "cat %s | ./SeqOut C1.list 1 > %s", argv[2], argv[3]);	
	system(str);	

	return 0;
}
