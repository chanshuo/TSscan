#include <stdio.h>
#include <stdlib.h>

void PrintUsage()
{
	fprintf(stderr, "Usage:\n");
	fprintf(stderr, "TSscan4of4 [sam] [sam] [fasta] [Output]\n\n");

	fprintf(stderr, "[sam]       Short reads to junciton sequences mapping result in sam format.\n");
	fprintf(stderr, "[sam]       Short reads to reference sequences mapping result in sam format.\n");
	fprintf(stderr, "[fasta]     Your long reads in fasta format.\n");
	fprintf(stderr, "[Output]    File name of output.\n\n");
	
	fprintf(stderr, "Example:\n");
	fprintf(stderr, "TSscan3of4 setp8.out.sam Ref.sam sample.fa step9.out\n");
}

int main(int argc, char **argv)
{
	char str[1024];

	if(argc != 5)
	{ PrintUsage();	return 1; }

	sprintf(str, "cat %s | ./RmAmbiMapping %s > C4.sam", argv[1], argv[2]);	
	system(str);
	system("cat C4.sam | ./RmLowComplexReads 10 90 > C4.2.sam");

	sprintf(str, "cat C4.sam | ./RmLowComplexReads 10 90 > %s.sam", argv[4]);	
	system(str);

	sprintf(str, "cat %s | ./SeqOut %s.sam 3 > %s.fa", argv[3], argv[4], argv[4]);	
	system(str);

	return 0;
}
