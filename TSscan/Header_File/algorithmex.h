#ifndef _INC_algorithmex
#define _INC_algorithmex

#include <iostream>
#include <string>
#include <string.h>
#pragma warning(disable:4786)
#include <vector>
using namespace std;

namespace algorithmex
{
	void Combination_Str(vector<string>& Element, vector<string>& Result)
	{
		static bool Initail(false);
		static vector<int> Temp;
		static unsigned int Temp_position;
		unsigned int Element_Size;
		string Temp_nString;
		unsigned int i, j;

		if(!Initail)
		{
			vector<string> ().swap(Result);
			vector<int> ().swap(Temp);
			Temp_position = 1;
			Initail = true;
		}

		Element_Size = Element.size();
		for(i=0; i<Element_Size; i++)
		{
			if(find(Temp.begin(), Temp.end(), i) == Temp.end())
			{
				if(Temp_position < Element_Size)
				{
					Temp.push_back(i);
					Temp_position++;

					Combination_Str(Element, Result);

					Temp.pop_back();
					Temp_position--;
				}

				if(Temp_position == Element_Size)
				{
					for(j=0; j<Temp.size(); j++)
					{
						Temp_nString.append(Element[Temp[j]]);
						Temp_nString.append("_");
					}
					Temp_nString.append(Element[i]);
					Result.push_back(Temp_nString);
				}
			}
		}
	}
};

#endif