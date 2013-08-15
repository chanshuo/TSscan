#ifndef _INC_bioinformatics
#define _INC_bioinformatics

#include <string>
#include <string.h>
#pragma warning(disable:4786)
#include <map>
using namespace std;

namespace bioinformatics
{
	class CCodon
	{
		private:
			map<string, char> Table;
			map<string, bool> Four_Fold;
			map<string, bool> Zero_Fold;

		public:
			CCodon()
			{
				Table["GCT"] = 'A';
				Table["GCC"] = 'A';
				Table["GCA"] = 'A';
				Table["GCG"] = 'A';
				Table["TGT"] = 'C';
				Table["TGC"] = 'C';
				Table["GAT"] = 'D';
				Table["GAC"] = 'D';
				Table["GAA"] = 'E';
				Table["GAG"] = 'E';
				Table["TTT"] = 'F';
				Table["TTC"] = 'F';
				Table["GGT"] = 'G';
				Table["GGC"] = 'G';
				Table["GGA"] = 'G';
				Table["GGG"] = 'G';
				Table["CAT"] = 'H';
				Table["CAC"] = 'H';
				Table["ATT"] = 'I';
				Table["ATC"] = 'I';
				Table["ATA"] = 'I';
				Table["AAA"] = 'K';
				Table["AAG"] = 'K';
				Table["CTT"] = 'L';
				Table["CTC"] = 'L';
				Table["CTA"] = 'L';
				Table["CTG"] = 'L';
				Table["TTA"] = 'L';
				Table["TTG"] = 'L';
				Table["ATG"] = 'M';
				Table["AAT"] = 'N';
				Table["AAC"] = 'N';
				Table["CCT"] = 'P';
				Table["CCC"] = 'P';
				Table["CCA"] = 'P';
				Table["CCG"] = 'P';
				Table["CAA"] = 'Q';
				Table["CAG"] = 'Q';
				Table["CGT"] = 'R';
				Table["CGC"] = 'R';
				Table["CGA"] = 'R';
				Table["CGG"] = 'R';
				Table["AGA"] = 'R';
				Table["AGG"] = 'R';
				Table["TCT"] = 'S';
				Table["TCC"] = 'S';
				Table["TCA"] = 'S';
				Table["TCG"] = 'S';
				Table["AGT"] = 'S';
				Table["AGC"] = 'S';
				Table["ACT"] = 'T';
				Table["ACC"] = 'T';
				Table["ACA"] = 'T';
				Table["ACG"] = 'T';
				Table["GTT"] = 'V';
				Table["GTC"] = 'V';
				Table["GTA"] = 'V';
				Table["GTG"] = 'V';
				Table["TGG"] = 'W';
				Table["TAT"] = 'Y';
				Table["TAC"] = 'Y';
				Table["TAA"] = '*';
				Table["TAG"] = '*';
				Table["TGA"] = '*';

				Four_Fold["TCN"] = true;
				Four_Fold["CTN"] = true;
				Four_Fold["CCN"] = true;
				Four_Fold["CGN"] = true;
				Four_Fold["ACN"] = true;
				Four_Fold["GTN"] = true;
				Four_Fold["GCN"] = true;
				Four_Fold["GGN"] = true;

				Zero_Fold["TCN"] = false;
				Zero_Fold["CTN"] = false;
				Zero_Fold["CCN"] = false;
				Zero_Fold["CGN"] = false;
				Zero_Fold["ACN"] = false;
				Zero_Fold["GTN"] = false;
				Zero_Fold["GCN"] = false;
				Zero_Fold["GGN"] = false;
				Zero_Fold["TNA"] = false;
				Zero_Fold["NTA"] = false;
				Zero_Fold["NTG"] = false;
				Zero_Fold["NGA"] = false;
				Zero_Fold["NGG"] = false;
			}
			char Aminoacid(char Codon1, char Codon2, char Codon3)
			{
				string Temp_nString;

				Temp_nString.assign(&Codon1, 1);
				Temp_nString.append(&Codon2, 1);
				Temp_nString.append(&Codon3, 1);

				if(Table.find(Temp_nString) != Table.end())
					return Table[Temp_nString];
				else
					return ' ';
			}
			bool is_Four_Fold_Generate_Site(char Codon1, char Codon2, char Codon3)
			{
				string Temp_nString;

				Temp_nString.assign(&Codon1, 1);
				Temp_nString.append(&Codon2, 1);
				Temp_nString.append(&Codon3, 1);

				if(Four_Fold.find(Temp_nString) != Four_Fold.end())
					return true;
				else
					return false;
			}
			bool is_Zero_Fold_Generate_Site(char Codon1, char Codon2, char Codon3)
			{
				string Temp_nString;

				Temp_nString.assign(&Codon1, 1);
				Temp_nString.append(&Codon2, 1);
				Temp_nString.append(&Codon3, 1);

				if(Zero_Fold.find(Temp_nString) != Zero_Fold.end())
					return false;
				else
					return true;
			}
	};

	class CSequence
	{
		private:
			CCodon Codon;

		public:
			bool Translate_Protein(string& Orignal_Sequence, string& Protein_Sequence)
			{
				int Orignal_Sequence_Length;
				string Temp_nString("0");
				int i;

				if((Orignal_Sequence.length()%3) != 0) return false;

				Protein_Sequence.assign("");
				Orignal_Sequence_Length = Orignal_Sequence.length();
				for(i=2; i<Orignal_Sequence_Length; i+=3)
				{
					Temp_nString[0] = Codon.Aminoacid(Orignal_Sequence[i-2], Orignal_Sequence[i-1], Orignal_Sequence[i]);
					Protein_Sequence.append(Temp_nString);
				}

				return true;
			}
	};
};

#endif