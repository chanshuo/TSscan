#ifndef _INC_fstreamex
#define _INC_fstreamex

#include <fstream>
#include <string>
#include <stdio.h>
#include <string.h>
#include "stringex.h"
using namespace std;
using namespace stringex;

namespace fstreamex
{
	bool File_Exist(string File_Name)
	{
		ifstream Load;

		Load.open(File_Name.c_str());
		if(!Load) return false;
		else return true;
	}

	long long int File_Length(string File_Name)
	{
		ifstream Load;
		long long int Length = 0;

		Load.open(File_Name.c_str());
		Load.seekg(0, ios::end);
		Length = Load.tellg();
		Load.seekg(0, ios::beg);
		Load.close();

		return Length;
	}

	class SequenceStream
	{
		private:
			FILE *File;
			unsigned int File_Size;
			bool Line_Char_Contain;
			char Temp_oString[100000];

		public:
			string Title;
			string Sequence;

		public:
			bool open(const char* Filename, bool Line_Char_Contain = false)
			{
				File = fopen(Filename, "r");
				if(File != NULL)
				{
					File_Size = File_Length(Filename);
					this->Line_Char_Contain = Line_Char_Contain;

					while(!feof(File))
					{
						fgets(Temp_oString, sizeof(Temp_oString), File);
						if((strlen(Temp_oString) == 0) || ((strlen(Temp_oString) == 1) && (Temp_oString[0] == '\n')))
							continue;
						
						if(Temp_oString[0] == '>')
						{
							if(Temp_oString[strlen(Temp_oString)-1] == '\n')
							{
								if(Temp_oString[strlen(Temp_oString)-2] == 13)
									Temp_oString[strlen(Temp_oString)-2] = '\0';
								else
									Temp_oString[strlen(Temp_oString)-1] = '\0';
							}
							break;
						}
					}

					return true;
				}
				else
					return false;
			}
			bool next()
			{
				Title.assign("");
				Sequence.assign("");

				while(!feof(File))
				{
					if((strlen(Temp_oString) == 0) || ((strlen(Temp_oString) == 1) && (Temp_oString[0] == '\n')))
					{
						Temp_oString[0] = '\0';
						fgets(Temp_oString, sizeof(Temp_oString), File);
						continue;
					}
					else if(Temp_oString[strlen(Temp_oString)-1] == '\n')
					{
						if(Temp_oString[strlen(Temp_oString)-2] == 13)
							Temp_oString[strlen(Temp_oString)-2] = '\0';
						else
							Temp_oString[strlen(Temp_oString)-1] = '\0';
					}

					Title.assign(Temp_oString);
					
					Temp_oString[0] = '\0';
					fgets(Temp_oString, sizeof(Temp_oString), File);
					if((strlen(Temp_oString) == 0) || ((strlen(Temp_oString) == 1) && (Temp_oString[0] == '\n')))
						break;
					else if(Temp_oString[strlen(Temp_oString)-1] == '\n')
					{
						if(Temp_oString[strlen(Temp_oString)-2] == 13)
							Temp_oString[strlen(Temp_oString)-2] = '\0';
						else
							Temp_oString[strlen(Temp_oString)-1] = '\0';
					}

					while(strlen(Temp_oString) > 0)
					{
						Sequence.append(Temp_oString);
						if(Line_Char_Contain) Sequence.append("\n");

						Temp_oString[0] = '\0';
						fgets(Temp_oString, sizeof(Temp_oString), File);
						if((strlen(Temp_oString) == 0) || ((strlen(Temp_oString) == 1) && (Temp_oString[0] == '\n')))
							break;
						else if(Temp_oString[strlen(Temp_oString)-1] == '\n')
						{
							if(Temp_oString[strlen(Temp_oString)-2] == 13)
								Temp_oString[strlen(Temp_oString)-2] = '\0';
							else
								Temp_oString[strlen(Temp_oString)-1] = '\0';
						}

						if(Temp_oString[0] == '>')
							break;
					}

					break;
				}

				if((Title == "") && (Sequence == ""))
					return false;

				return true;
			}
			int Progress()
			{
				return int((double(ftell(File))/File_Size)*100);
			}
			void close()
			{
				if(File != NULL) fclose(File);
			}
	};
	class RecordStream
	{
		private:
			FILE *File;
			long long int File_Size;
			char Temp_oString[100000];

		public:
			vector<string> Column;

		public:
			bool open(const char* Filename)
			{
				File = fopen(Filename, "r");
				if(File != NULL)
				{
					File_Size = File_Length(Filename);
					return true;
				}

				return false;
			}
			bool next()
			{
				vector<string> ().swap(Column);
				while(!feof(File))
				{
					Temp_oString[0] = '\0';
					fgets(Temp_oString, sizeof(Temp_oString), File);
					if((strlen(Temp_oString) == 0) || ((strlen(Temp_oString) == 1) && (Temp_oString[0] == '\n')))
						continue;

					if(Temp_oString[strlen(Temp_oString)-1] == '\n')
					{
						if(Temp_oString[strlen(Temp_oString)-2] == 13)
							Temp_oString[strlen(Temp_oString)-2] = '\0';
						else
							Temp_oString[strlen(Temp_oString)-1] = '\0';
					}

					StrSplit(Temp_oString, '\t', Column);

					break;
				}

				if(Column.size() > 0)
					return true;
				else
					return false;
			}
			int Progress()
			{
				return int((double(ftell(File))/File_Size)*100);
			}
			void close()
			{
				if(File != NULL) fclose(File);
			}
	};
};

#endif