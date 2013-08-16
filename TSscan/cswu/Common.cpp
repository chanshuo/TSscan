#include <string.h>
#include <stdio.h>
#include "Common.h"

using namespace std;

char *ItoA( int value, char* result, int base) 
{
	// check that the base if valid
	if (base < 2 || base > 36) { *result = '\0'; return result; }

	char* ptr = result, *ptr1 = result, tmp_char;
	int tmp_value;

	do {
		tmp_value = value;
		value /= base;
		*ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz" [35 + (tmp_value - value * base)];
	} while ( value );

	// Apply negative sign
	if (tmp_value < 0) *ptr++ = '-';
	*ptr-- = '\0';
	while(ptr1 < ptr) {
		tmp_char = *ptr;
		*ptr--= *ptr1;
		*ptr1++ = tmp_char;
	}
	return result;
}

char *StrRev(char *rstr, const char *str)
{
	int i;
	int len;

	len = strlen(str);

	rstr[len] = '\0';

	if(str[len-1] == '\n')
	{
		rstr[len-1] = '\n';
		len--;
	}


	for(i=0; i<len; i++)
		rstr[i] = str[len-i-1];

	return rstr;
}

int Popen(const char *com, const char *filename)
{
	FILE *fp;
	FILE *outfile;
	char buff[MaxLineSize];

	if(!(fp = popen(com, "r")))	
		{return 1;}		

	if(	( outfile = fopen(filename, "w") ) == NULL )
	{	ErrMsg("Popen error: can not open a file for writing!\n");	return -1;	}
	
	while(fgets(buff, sizeof(buff), fp)!=NULL)
	        fprintf(outfile, "%s", buff);

	pclose(fp);
	fclose(outfile);
	return 0;
}
