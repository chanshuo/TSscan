#ifndef _INC_stringex
#define _INC_stringex

#include <iostream>
#include <algorithm>
#include <string>
#include <string.h>
#pragma warning(disable:4786)
#include <vector>
#include <list>
using namespace std;

namespace stringex
{
	string itoaEx(int Number)
	{
		string Temp_Str;
		bool Minus_Flag(false);

		if(Number < 0)
		{
			Minus_Flag = true;
			Number *= -1;
		}

		while(Number != 0 || Temp_Str == "")
		{
			Temp_Str = (char)((Number % 10) + 48) + Temp_Str;
			Number /= 10;
		}

		if(Minus_Flag)
			Temp_Str = "-" + Temp_Str;

		return Temp_Str;
	}

	void trim(const char *s, char *Result)
	{
		const char *Front, *Rear;

		Front = s;
		Rear = s+strlen(s)-1;

		while((*Front==' ') || (*Front=='\t') || (*Front=='\n') || (*Front=='\r'))
			Front++;

		while((*Rear==' ') || (*Rear=='\t') || (*Rear=='\n') || (*Rear=='\r'))
			Rear--;

		memcpy(Result, Front, (Rear-Front+1));
		Result[(Rear-Front+1)] = '\0';
	}
	void trim(const char *s, string& Result)
	{
		const char *Front, *Rear;
		const char *c;
		string Temp_nStr("");

		if(strlen(s) > 0)
		{
			Front = s;
			while((*Front==' ') || (*Front=='\t') || (*Front=='\n') || (*Front=='\r'))
				Front++;

			Rear = s+strlen(s)-1;
			while((*Rear==' ') || (*Rear=='\t') || (*Rear=='\n') || (*Rear=='\r'))
				Rear--;

			for(c = Front; c<=Rear; c++)
				Temp_nStr += *c;

			Result = Temp_nStr;
		}
		else
			Result = Temp_nStr;
	}

	int StrFind(string Str, char Target_Char, int Count, bool Reverse = false)
	{
		int n = -1;

		if(Reverse)
			reverse(Str.begin(), Str.end());

		for(int i = 0;i <= Count;i++)
			n = Str.find(Target_Char,n+1);

		if(n == -1)
			return Str.length()-1;

		return n;
	}

	string SubstrEx(string Str, char First_Char, int Frist_Count, char Second_Char, int Secord_Count, bool Reverse = false)
	{
		string Result("");
		int nString_Length;
		int i = 0;

		if(Reverse)
			reverse(Str.begin(), Str.end());

		nString_Length = Str.length();

		if(Frist_Count > 0)
		{
			for(; i<nString_Length; i++)
			{
				if(Str[i] == First_Char)
					Frist_Count--;
				else if(Frist_Count == 0)
					break;
			}
		}

		for(; i<nString_Length; i++)
		{
			if(Str[i] == Second_Char)
				Secord_Count--;

			if(Secord_Count == 0)
				break;

			Result += Str[i];
		}

		return Result;
	}

	string SubstrEx(string Str, char First_Char, int Frist_Count, char Second_Char, bool Reverse = false)
	{
		string Result("");
		int nString_Length;
		int i = 0;

		nString_Length = Str.length();

		if(Frist_Count > 0)
		{
			for(i=0; i<nString_Length; i++)
			{
				if(Str[i] == First_Char)
					Frist_Count--;
				else if(Frist_Count == 0)
					break;
			}
		}

		for(; i<nString_Length; i++)
		{
			if(Str[i] == Second_Char)
				break;

			Result += Str[i];
		}

		return Result;
	}

	string SubstrEx(string Str, char First_Char, int Frist_Count, int Length, bool Reverse = false)
	{
		if(Reverse)
			reverse(Str.begin(), Str.end());
		return Str.substr(StrFind(Str,First_Char,Frist_Count)+1,Length);
	}

	string SubstrEx(string Str, char First_Char, int Frist_Count, bool Reverse = false)
	{
		if(Reverse)
			reverse(Str.begin(), Str.end());
		return Str.substr(StrFind(Str,First_Char,Frist_Count)+1);
	}

	void StrSplit(const char* Str, char Pattern, vector<string>& Result)
	{
		int Str_Length;
		const char *Ptr_Start, *Ptr_End;
		string Temp_nString;
		int i;

		vector<string> ().swap(Result);

		Str_Length = strlen(Str);
		if(Str_Length > 0)
		{
			Ptr_Start = Ptr_End = Str;
			for(i=0; i<Str_Length; i++)
			{
				if(Str[i] == Pattern)
				{
					Temp_nString.assign(Ptr_Start, Ptr_End);
					Result.push_back(Temp_nString);
					Ptr_Start = (++Ptr_End);
				}
				else
					Ptr_End++;
			}
			Temp_nString.assign(Ptr_Start, Ptr_End);
			Result.push_back(Temp_nString);
		}
	}

	void StrSplit(const char* Str, string patten, vector<string>& Result)
	{
		int Str_Length;
		const char *Ptr_Start, *Ptr_End;
		bool Pattern_Match_Prev;
		int i;

		vector<string> ().swap(Result);
		Pattern_Match_Prev = false;

		Str_Length = strlen(Str);
		if(Str_Length > 0)
		{
			Result.push_back("");
			Ptr_Start = Ptr_End = Str;

			for(i=0; i<Str_Length; i++)
			{
				if(patten.find(Str[i]) < patten.size())
				{
					if(!Pattern_Match_Prev)
					{
						Result[Result.size()-1].assign(Ptr_Start, Ptr_End);
						Ptr_Start = (++Ptr_End);
						Result.push_back("");
						Pattern_Match_Prev = true;
					}
					else
						Ptr_Start = (++Ptr_End);
				}
				else
				{
					Ptr_End++;
					Pattern_Match_Prev = false;
				}
			}
			Result[Result.size()-1].assign(Ptr_Start, Ptr_End);
		}
	}
};

#endif
