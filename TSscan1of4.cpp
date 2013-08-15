#include <iostream>
#include <list>
#include <map>
#include <algorithm>
#include "Header_File/fstreamex.h"
#include "Header_File/bioinformatics.h"
#include <stdlib.h>
#include <omp.h>

using namespace std;
using namespace fstreamex;
using namespace stringex;

struct Block
{
	int Start;
	int End;
	bool Overlap;
	int Number;
};

bool Block_Compare(Block& A, Block& B)
{
	if(A.Start < B.Start) return true;
	else if(A.Start > B.Start) return false;
	else if(A.End < B.End) return true;
	else if(A.End > B.End) return false;
	else return false;
}

void Calculate_Total_Length(vector<string>& A, vector<string>& B, int& Total_Length, double& Identity)
{
	unsigned int Block_Size;
	vector<string> Block_Length, Block_qStart;
	Block Temp_Block;
	list<Block> Block_List;
	list<Block>::iterator it1, it2;
	int NonOverlap_Length[2];
	int Temp_Length;
	unsigned int i;

	stringex::StrSplit(A[18].c_str(), ',', Block_Length);
	stringex::StrSplit(A[19].c_str(), ',', Block_qStart);
	Block_Size = atoi(A[17].c_str());
	for(i=0; i<Block_Size; i++)
	{
		if(A[8] == "+")
		{
			Temp_Block.Start = atoi(Block_qStart[i].c_str());
			Temp_Block.End = Temp_Block.Start + atoi(Block_Length[i].c_str()) - 1;
		}
		else
		{
			Temp_Block.End = atoi(A[10].c_str()) - atoi(Block_qStart[i].c_str()) - 1;
			Temp_Block.Start = Temp_Block.End - atoi(Block_Length[i].c_str()) + 1;
		}
		Temp_Block.Overlap = false;
		Temp_Block.Number = 0;
		Block_List.push_back(Temp_Block);
	}

	stringex::StrSplit(B[18].c_str(), ',', Block_Length);
	stringex::StrSplit(B[19].c_str(), ',', Block_qStart);
	Block_Size = atoi(B[17].c_str());
	for(i=0; i<Block_Size; i++)
	{
		if(B[8] == "+")
		{
			Temp_Block.Start = atoi(Block_qStart[i].c_str());
			Temp_Block.End = Temp_Block.Start + atoi(Block_Length[i].c_str()) - 1;
		}
		else
		{
			Temp_Block.End = atoi(B[10].c_str()) - atoi(Block_qStart[i].c_str()) - 1;
			Temp_Block.Start = Temp_Block.End - atoi(Block_Length[i].c_str()) + 1;
		}
		Temp_Block.Overlap = false;
		Temp_Block.Number = 1;
		Block_List.push_back(Temp_Block);
	}

	Block_List.sort(Block_Compare);

	it1=Block_List.begin();
	it2 = it1;
	for(it2++; it2!=Block_List.end();)
	{
		if((*it2).Start <= (*it1).End)
		{
			if((*it1).End > (*it2).End)
			{
				swap((*it1).End, (*it2).End);
				(*it2).Number = ((*it2).Number == 0)? 1 : 0;
			}

			Temp_Block.Start = (*it2).Start;
			Temp_Block.End = (*it1).End;
			Temp_Block.Overlap = true;
			Temp_Block.Number = 2;

			(*it1).End = Temp_Block.Start-1;
			(*it2).Start = Temp_Block.End+1;

			Block_List.insert(it2, Temp_Block);

			it1 = it2;
			it2++;
		}
		else
		{
			it1 = it2;
			it2++;
		}
	}

	Total_Length = 0;
	NonOverlap_Length[0] = 0;
	NonOverlap_Length[1] = 0;
	for(it1=Block_List.begin(); it1!=Block_List.end(); it1++)
	{
		if((*it1).Start <= (*it1).End)
		{
			Temp_Length = (*it1).End - (*it1).Start + 1;
			Total_Length += Temp_Length;
			if(!(*it1).Overlap)
			{
				if(NonOverlap_Length[(*it1).Number] < Temp_Length)
					NonOverlap_Length[(*it1).Number] = Temp_Length;
			}
		}
	}

	if((NonOverlap_Length[0] < 50) || (NonOverlap_Length[1] < 50)) Total_Length = 0;

	Identity = atof(A[0].c_str()) + atof(B[0].c_str());
}

void Calculate_Length(vector<string>& A, int& Alignment_Length, double& Identity)
{
	unsigned int Block_Size;
	vector<string> Block_Length;
	unsigned int i;

	stringex::StrSplit(A[18].c_str(), ',', Block_Length);
	Alignment_Length = 0;

	Block_Size = atoi(A[17].c_str());
	for(i=0; i<Block_Size; i++)
		Alignment_Length += atoi(Block_Length[i].c_str());

	Identity = atof(A[0].c_str());
}

bool Find_Best_Score(vector< vector<string> >& List, vector<int>& Index)
{
	unsigned int List_Size;
	int Best_List[2];
	int One_Best_Length, Two_Best_Length;
	double One_Best_Identity, Two_Best_Identity;
	int Temp_Length;
	double Temp_Identity;
	int i, j;

	List_Size = List.size();
	vector<int> ().swap(Index);

	Best_List[0] = -1;
	Best_List[1] = -1;
	One_Best_Length = 0;
	for(i=0; i<List_Size; i++)
	{
		Calculate_Length(List[i], Temp_Length, Temp_Identity);
		if((Temp_Length > One_Best_Length)
		|| ((Temp_Length == One_Best_Length) && (Temp_Identity > One_Best_Identity)))
		{
			One_Best_Length = Temp_Length;
			One_Best_Identity = Temp_Identity;
			Best_List[0] = i;
		}
	}
	Index.push_back(Best_List[0]);

	//=============================================
	int Omp_Two_Best_Length[7], Omp_Temp_Length[7];
	double Omp_Two_Best_Identity[7], Omp_Temp_Identity[7];
	int Omp_Best_List[2][7];
	int Thread_Number = 7;

	Two_Best_Length = One_Best_Length;
	Two_Best_Identity = One_Best_Identity;

	for(i=0; i<List_Size; i++)
	{
		#pragma omp parallel for num_threads(Thread_Number) 
		for(j=0; j<Thread_Number; j++)
		{
			Omp_Two_Best_Length[j] = 0;
			Omp_Two_Best_Identity[j] = 0;
		}

		#pragma omp parallel for num_threads(Thread_Number) private(Temp_Length) private(Temp_Identity)
		for(j=i+1; j<List_Size; j++)
		{
			Calculate_Total_Length(List[i], List[j], Temp_Length, Temp_Identity);
			if((Temp_Length > Omp_Two_Best_Length[omp_get_thread_num()])
			|| ((Temp_Length == Omp_Two_Best_Length[omp_get_thread_num()]) && (Temp_Identity > Omp_Two_Best_Identity[omp_get_thread_num()])))
			{
				Omp_Two_Best_Length[omp_get_thread_num()] = Temp_Length;
				Omp_Two_Best_Identity[omp_get_thread_num()] = Temp_Identity;
				Omp_Best_List[0][omp_get_thread_num()] = i;
				Omp_Best_List[1][omp_get_thread_num()] = j;
			}
		}

		for(j=0; j<Thread_Number; j++)
		{
			if((Omp_Two_Best_Length[j] > Two_Best_Length)
			|| ((Omp_Two_Best_Length[j] == Two_Best_Length) && (Omp_Two_Best_Identity[j] > Two_Best_Identity)))
			{
				Two_Best_Length = Omp_Two_Best_Length[j];
				Two_Best_Identity = Omp_Two_Best_Identity[j];
				Best_List[0] = Omp_Best_List[0][j];
				Best_List[1] = Omp_Best_List[1][j];
			}
		}
	}

	if(Best_List[0] >= 0) Index.push_back(Best_List[0]);
	if(Best_List[1] >= 0) Index.push_back(Best_List[1]);

	List[Index[0]].push_back(itoaEx(One_Best_Length));
	List[Index[0]].push_back(itoaEx(Two_Best_Length));

	if(Index[1] != Index[0])
	{
		List[Index[1]].push_back(itoaEx(One_Best_Length));
		List[Index[1]].push_back(itoaEx(Two_Best_Length));
	}

	if(One_Best_Length != Two_Best_Length)
	{
		if(Index[2] != Index[0])
		{
			List[Index[2]].push_back(itoaEx(One_Best_Length));
			List[Index[2]].push_back(itoaEx(Two_Best_Length));
		}
	}

	return true;
}

void Stage2(string Input_File, const char *Output_File)
{
	RecordStream RS;
	string EST_ID;
	vector< vector<string> > List;
	vector<int> Index;
	FILE *Save;
	unsigned int Temp_Size;
	int Progress[2];
	unsigned int i, j;
	int count = 0;

	Progress[0] = -1;

	RS.open(Input_File.c_str());
//	Save = fopen(Output_File.c_str(), "w");

	Save = fopen(Output_File, "w");
	if(RS.next())
	{
		List.push_back(RS.Column);
		EST_ID = RS.Column[9];
		while((RS.next()) || (EST_ID != ""))
		{
			if((RS.Column.size() >  9) && (RS.Column[0][0] != 'm') && (RS.Column[9] == EST_ID))
			{
				List.push_back(RS.Column);
				continue;
			}

			if((List.size() > 0) && Find_Best_Score(List, Index))
			{
				for(i=0; i<Index.size(); i++)
				{
					Temp_Size = List[Index[i]].size()-1;
					for(j=0; j<Temp_Size; j++)
					{
						fputs(List[Index[i]][j].c_str(), Save);
						fputs("\t", Save);
					}
					fputs(List[Index[i]][j].c_str(), Save);
					fputs("\n", Save);
				}
			}

			Progress[1] = RS.Progress();
			if(Progress[0] < Progress[1])
			{
				Progress[0] = Progress[1];
				cout<<"\rProgress : "<<Progress[0]<<"%";
			}

			count++;
			cout<<"test("<<count<<")"<<endl;

			vector< vector<string> > ().swap(List);
			if((RS.Column.size() > 9) && (RS.Column[0][0] != 'm'))
			{
				List.push_back(RS.Column);
				EST_ID = RS.Column[9];
			}
			else
				EST_ID = "";
		}
	}
	fclose(Save);
	RS.close();

	cout<<"\rProgress : 100%\n";
}

struct Junction_Site_Record
{
	int Read_Start;
	int Read_End;
	string Genome_Start_Chr;
	int Genome_Start;
	string Genome_Start_Type;
	string Genome_End_Chr;
	int Genome_End;
	string Genome_End_Type;
	int Space_Or_Overlap;
};

void Load_Junction_Site(vector<string>& A, vector<string>& B, Junction_Site_Record& Junction_Site)
{
	int A_Read_Start, A_Read_End, B_Read_Start, B_Read_End;
	string A_Genome_Chr, B_Genome_Chr;
	int A_Genome_Start, A_Genome_End, B_Genome_Start, B_Genome_End;

	A_Read_Start = atoi(A[11].c_str());
	A_Read_End = atoi(A[12].c_str())-1;
	B_Read_Start = atoi(B[11].c_str());
	B_Read_End = atoi(B[12].c_str())-1;

	A_Genome_Chr = A[13];
	A_Genome_Start = atoi(A[15].c_str());
	A_Genome_End = atoi(A[16].c_str());
	B_Genome_Chr = B[13];
	B_Genome_Start = atoi(B[15].c_str());
	B_Genome_End = atoi(B[16].c_str());

	if(abs(A_Read_End - B_Read_Start) < abs(B_Read_End - A_Read_Start))
	{
		if(A_Read_End < B_Read_Start)
		{
			Junction_Site.Read_Start = A_Read_End;
			Junction_Site.Genome_Start_Chr = A_Genome_Chr;
			Junction_Site.Genome_Start = A_Genome_End;
			Junction_Site.Genome_Start_Type = "R";
			Junction_Site.Read_End = B_Read_Start;
			Junction_Site.Genome_End_Chr = B_Genome_Chr;
			Junction_Site.Genome_End = B_Genome_Start;
			Junction_Site.Genome_End_Type = "L";
		}
		else
		{
			Junction_Site.Read_Start = B_Read_Start;
			Junction_Site.Genome_Start_Chr = B_Genome_Chr;
			Junction_Site.Genome_Start = B_Genome_Start;
			Junction_Site.Genome_Start_Type = "L";
			Junction_Site.Read_End = A_Read_End;
			Junction_Site.Genome_End_Chr = A_Genome_Chr;
			Junction_Site.Genome_End = A_Genome_End;
			Junction_Site.Genome_End_Type = "R";
		}

		Junction_Site.Space_Or_Overlap = B_Read_Start - A_Read_End - 1;
	}
	else
	{
		if(B_Read_End < A_Read_Start)
		{
			Junction_Site.Read_Start = B_Read_End;
			Junction_Site.Genome_Start_Chr = B_Genome_Chr;
			Junction_Site.Genome_Start = B_Genome_End;
			Junction_Site.Genome_Start_Type = "R";
			Junction_Site.Read_End = A_Read_Start;
			Junction_Site.Genome_End_Chr = A_Genome_Chr;
			Junction_Site.Genome_End = A_Genome_Start;
			Junction_Site.Genome_End_Type = "L";
		}
		else
		{
			Junction_Site.Read_Start = A_Read_Start;
			Junction_Site.Genome_Start_Chr = A_Genome_Chr;
			Junction_Site.Genome_Start = A_Genome_Start;
			Junction_Site.Genome_Start_Type = "L";
			Junction_Site.Read_End = B_Read_End;
			Junction_Site.Genome_End_Chr = B_Genome_Chr;
			Junction_Site.Genome_End = B_Genome_End;
			Junction_Site.Genome_End_Type = "R";
		}

		Junction_Site.Space_Or_Overlap = A_Read_Start - B_Read_End - 1;
	}
}

void Load_Chimeric_Junction_Site_Form_Blat(string Input_File, map<string, Junction_Site_Record>& Junction_Site)
{
	RecordStream RS;
	string EST_ID;
	vector< vector<string> > List;
	Junction_Site_Record Temp_Junction_Site_Record;
	int Progress[2];

	Progress[0] = -1;

	RS.open(Input_File.c_str());
	if(RS.next())
	{
		List.push_back(RS.Column);
		EST_ID = RS.Column[9];
		while((RS.next()) || (EST_ID != ""))
		{
			if((RS.Column.size() >=  20) && (RS.Column[0][0] != 'm') && (RS.Column[9] == EST_ID))
			{
				List.push_back(RS.Column);
				continue;
			}

			if(List.size() == 3)
			{
				//printf("%s\n",RS.Column[9].c_str());
				Load_Junction_Site(List[1], List[2], Temp_Junction_Site_Record);
				Junction_Site[EST_ID] = Temp_Junction_Site_Record;
			}

			Progress[1] = RS.Progress();
			if(Progress[0] < Progress[1])
			{
				Progress[0] = Progress[1];
				cout<<"\rProgress : "<<Progress[0]<<"%";
			}

			vector< vector<string> > ().swap(List);
			if((RS.Column.size() >= 20) && (RS.Column[0][0] != 'm'))
			{
				List.push_back(RS.Column);
				EST_ID = RS.Column[9];
			}
			else
				EST_ID = "";
		}
	}
	RS.close();

	cout<<"\rProgress : 100%\n";
}

void Stage6(string Input_File1, string Input_File2, string Output_File1, string Output_File2)
{
	map<string, Junction_Site_Record> Junction_Site;

	Load_Chimeric_Junction_Site_Form_Blat(Input_File1, Junction_Site);

	//===========================================
	SequenceStream SS;
	ofstream Save1, Save2;
	vector<string> Column;
	int Shift_Base;
	int Progress[2];

	Progress[0] = -1;

	SS.open(Input_File2.c_str());
	Save1.open(Output_File1.c_str());
	Save2.open(Output_File2.c_str());
	while(SS.next())
	{
		StrSplit(SS.Title.c_str(), "> ", Column);

		if(Junction_Site.find(Column[1]) == Junction_Site.end())
			continue;

		Shift_Base = (100 - (abs(Junction_Site[Column[1]].Space_Or_Overlap) * 2)) / 2;

		if(Junction_Site[Column[1]].Space_Or_Overlap >= 0)
		{
			Junction_Site[Column[1]].Read_Start = Junction_Site[Column[1]].Read_Start - Shift_Base + 1;
			Junction_Site[Column[1]].Read_End = Junction_Site[Column[1]].Read_End + Shift_Base - 1;
		}
		else
		{
			Junction_Site[Column[1]].Read_Start = Junction_Site[Column[1]].Read_Start - Shift_Base;
			Junction_Site[Column[1]].Read_End = Junction_Site[Column[1]].Read_End + Shift_Base;
		}

		if((Shift_Base >= 0) && ((Junction_Site[Column[1]].Read_End - Junction_Site[Column[1]].Read_Start) >= 50))
		{
			Save1<<">"<<Column[1]<<"\n";
			Save1<<SS.Sequence.substr(Junction_Site[Column[1]].Read_Start, (Junction_Site[Column[1]].Read_End-Junction_Site[Column[1]].Read_Start)+1)<<"\n";

			Save2<<Column[1]<<"\t";
			Save2<<Junction_Site[Column[1]].Genome_Start_Chr<<"."<<Junction_Site[Column[1]].Genome_Start<<"."<<Junction_Site[Column[1]].Genome_Start_Type;
			Save2<<"-";
			Save2<<Junction_Site[Column[1]].Genome_End_Chr<<"."<<Junction_Site[Column[1]].Genome_End<<"."<<Junction_Site[Column[1]].Genome_End_Type;
			Save2<<"\n";
		}

		Progress[1] = SS.Progress();
		if(Progress[0] < Progress[1])
		{
			Progress[0] = Progress[1];
			cout<<"\rProgress : "<<Progress[0]<<"%";
		}
	}
	Save1.close();
	Save2.close();
	SS.close();

	cout<<"\rProgress : 100%\n";
}


void PrintUsage()
{
	fprintf(stderr, "Usage:\n");
	fprintf(stderr, "TSscan1of4 [psl] [fasta] [Output]\n\n");

	fprintf(stderr, "[psl]       The blat result of your long reads against reference genome.\n");
	fprintf(stderr, "[fasta]     Your long reads in fasta format.\n");
	fprintf(stderr, "[Output]    File name of output.\n\n");
	
	fprintf(stderr, "Example:\n");
	fprintf(stderr, "TSscan1of4 sample.blat sample.fa out.step2.fa\n");
	
}

int main(int argc, char **argv)
{
	char str[1024];

	if(argc != 4)
	{ PrintUsage();	return 1; }

	Stage2(argv[1], "2p3p.blat");

 	system("./CountName 2p3p.blat 10 > temp.txt");
 	system("grep -P \"^.*\\t3.*$\" temp.txt > 3p.list");
	system("cat 2p3p.blat | ./RetainInList 10 3p.list 1 > noncolinear.blat");

	sprintf(str, "cat %s | ./SeqOut 3p.list 1 > %s", argv[2], argv[3]);
	system(str);

	Stage6("2p3p.blat", argv[2], "jsite.fa", "jsite.Info");

	return 0;
}
